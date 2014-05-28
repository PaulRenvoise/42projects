<?php

namespace Site\ActivityBundle\Controller;

use Symfony\Bundle\FrameworkBundle\Controller\Controller;
use Site\ActivityBundle\Entity\Module;
use Site\ActivityBundle\Entity\Activity;
use Site\ActivityBundle\Entity\ActivityGroup;
use Site\ActivityBundle\Form\ActivityGroupType;
use Site\IntraBundle\Entity\Event;
use Symfony\Component\Security\Core\Exception\AccessDeniedException;

class ActivityController extends Controller
{
	public function indexAction()
	{
		$data = array();

		$modules = $this->getDoctrine()->getManager()->getRepository("SiteActivityBundle:Module")->findAll();

		$data['modules'] = $modules;
		$data['activity'] = null;
		$data['module'] = null;

		return $this->render('SiteActivityBundle:Activities:index.html.twig', $data);
	}

	public function moduleAction(Module $module)
	{
		$data = array();

		$modules = $this->getDoctrine()->getManager()->getRepository("SiteActivityBundle:Module")->findAll();

		$data['modules'] = $modules;
		$data['module'] = $module;
		$data['activity'] = null;

		return $this->render('SiteActivityBundle:Activities:module.html.twig', $data);
	}

	public function moduleRegistrationAction(Module $module)
	{
		$now = new \Datetime("NOW");
		$user = $this->container->get("security.context")->getToken()->getUser();
		$event = new Event();
		$event->setUser($user);
		$event->setInfo($module->getName());

		if ($now > $module->getEndRegistration() || $now < $module->getStartRegistration())
			throw new AccessDeniedException("You can't register for this activity now.");

		if ($module->getStudents()->count() >= $module->getPlaces())
			throw new AccessDeniedException("No more places for this module.");

		$em = $this->getDoctrine()->getManager();
		if ($module->getStudents()->contains($user))
		{
			$module->removeStudent($user);
			$activities = $module->getActivities();
			foreach ($activities as $a)
			{
				$a->removeStudent($user);
				$em->persist($a);
			}
			$event->setDate($now);
			$event->setType("deregistration");
			$event->setDescription("FEED_UNREGISTRATION_MODULE");
		}
		else
		{
			$module->addStudent($user);

			$event->setDate($now);
			$event->setType("registration");
			$event->setDescription("FEED_REGISTRATION_MODULE");
		}

		$em->persist($event);
		$em->persist($module);
		$em->flush();

		return $this->redirect($this->generateUrl('site_activities_module', array('id' => $module->getId())));
	}

	public function activityAction(Activity $activity)
	{
		$data = array();

		$user = $this->container->get("security.context")->getToken()->getUser();

		$modules = $this->getDoctrine()->getManager()->getRepository("SiteActivityBundle:Module")->findAll();

		$data['modules'] = $modules;
		$data['activity'] = $activity;
		$data['module'] = $activity->getModule();

		$groups = $this->getDoctrine()->getManager()->getRepository("SiteActivityBundle:ActivityGroup")->findBy(array('activity' => $activity));
		foreach ($groups as $group)
		{
			if ($group->getStudents()->contains($user))
				$data['group'] = $group;
		}

		$user = $this->container->get("security.context")->getToken()->getUser();
		$students = $activity->getModule()->getStudents();
		if ($students->contains($user))
		{
			$students->removeElement($user);
			$data['form'] = $this->createForm(new ActivityGroupType($students->toArray(), $activity))->createView();
			$students->add($user);
		}
		else
			$data['form'] = $this->createForm(new ActivityGroupType($students->toArray(), $activity))->createView();

		return $this->render('SiteActivityBundle:Activities:activity.html.twig', $data);
	}

	public function activityRegistrationAction(Activity $activity)
	{
		$now = new \Datetime("NOW");
		$user = $this->container->get("security.context")->getToken()->getUser();

		if ($now > $activity->getEndRegistration() || $now < $activity->getStartRegistration())
			throw new AccessDeniedException("You can't register for this activity now.");

		if (!$activity->getModule()->getStudents()->contains($user))
			throw new AccessDeniedException("You can't register for this activity before register to module.");

		if ($activity->getStudents()->count() >= $activity->getPlaces())
			throw new AccessDeniedException("No more places left for this activity.");

		$em = $this->getDoctrine()->getManager();

		if ($activity->getSizeMax() > 1)
		{
			if ($activity->getStudents()->contains($user))
			{
				$groups = $this->getDoctrine()->getManager()->getRepository("SiteActivityBundle:ActivityGroup")->findBy(array('activity' => $activity));

				foreach ($groups as $group)
				{
					if ($group->getStudents()->contains($user))
					{
						foreach ($group->getStudents() as $student)
						{
							$activity->removeStudent($student);
							$event = new Event();
							$event->setInfo($activity->getName());
							$event->setUser($student);
							$event->setDate($now);
							$event->setType("deregistration");
							if ($user == $student)
								$event->setDescription("FEED_UNREGISTRATION_ACTIVITY_GROUP_OWNER");
							else
								$event->setDescription("FEED_UNREGISTRATION_ACTIVITY_GROUP");
							$em->persist($event);
						}
						$em->remove($group);
					}
				}
			}
			else
			{
				$form = $this->createForm(new ActivityGroupType($activity->getModule()->getStudents()->toArray(), $activity));
				$request = $this->getRequest();
				if ($request->isMethod("POST"))
				{
					$form->bind($request);
					$group = $form->getData();
					$group->addStudent($user);
					if ($form->isValid() && $group->getStudents()->count() >= $activity->getSizeMin() && $group->getStudents()->count() <= $activity->getSizeMax())
					{
						$group = $form->getData();
						$group->setActivity($activity);
						foreach ($group->getStudents() as $student)
						{
							$activity->addStudent($student);
							$event = new Event();
							$event->setInfo($activity->getName());
							$event->setUser($student);
							$event->setDate($now);
							$event->setType("registration");
							if ($user == $student)
								$event->setDescription("FEED_REGISTRATION_ACTIVITY_GROUP_OWNER");
							else
								$event->setDescription("FEED_REGISTRATION_ACTIVITY_GROUP");
							$em->persist($event);
						}
						$em->persist($group);
					}
				}
			}
			$em->persist($activity);
			$em->flush();
		}
		else
		{
			$event = new Event();
			$event->setDate($now);
			$event->setInfo($activity->getName());
			if ($activity->getStudents()->contains($user))
			{
				$group = $em->createQuery('
					SELECT g, a, u FROM SiteActivityBundle:ActivityGroup g
					JOIN g.activity a
					JOIN g.students u
					WHERE u.id = :user_id AND a.id = :a_id
					')->setParameters(array('user_id' => $user->getId(), 'a_id' => $activity->getId()))->getResult();
				$activity->removeStudent($user);
				$em->remove($group[0]);
				$event->setType("deregistration");
				$event->setDescription("FEED_UNREGISTRATION_ACTIVITY_ONE");
			}
			else
			{
				$group = new ActivityGroup();
				$group->setName($user->getUsername());
				$group->setActivity($activity);
				$group->addStudent($user);
				$group->setName($user->getUsername()."_".$activity->getName());
				$activity->addStudent($user);
				$em->persist($group);
				$event->setType("registration");
				$event->setDescription("FEED_REGISTRATION_ACTIVITY_ONE");
			}
			$em->persist($event);
			$em->persist($activity);
			$em->flush();
		}

		return $this->redirect($this->generateUrl('site_activities_activity', array('id' => $activity->getId())));
	}
}
