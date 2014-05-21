<?php

namespace Site\ActivityBundle\Controller;

use Symfony\Bundle\FrameworkBundle\Controller\Controller;
use Site\ActivityBundle\Entity\Module;
use Site\ActivityBundle\Entity\Activity;
use Site\ActivityBundle\Entity\ActivityGroup;
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
		// if is too early or late to registratration
		if ($now > $module->getEndRegistration() || $now < $module->getStartRegistration())
			throw new AccessDeniedException("You can't register for this activity now.");

		if ($module->getStudents()->contains($user))
			$module->removeStudent($user);
		else
			$module->addStudent($user);

		$em = $this->getDoctrine()->getManager();
		$em->persist($module);
		$em->flush();

		return $this->redirect($this->generateUrl('site_activities_module', array('id' => $module->getId())));
	}

	public function activityAction(Activity $activity)
	{
		$data = array();

		$modules = $this->getDoctrine()->getManager()->getRepository("SiteActivityBundle:Module")->findAll();

		$data['modules'] = $modules;
		$data['activity'] = $activity;
		$data['module'] = $activity->getModule();

		return $this->render('SiteActivityBundle:Activities:activity.html.twig', $data);
	}

	public function activityRegistrationAction(Activity $activity)
	{
		$now = new \Datetime("NOW");
		$user = $this->container->get("security.context")->getToken()->getUser();
		// if is too early or late to registratration
		if ($now > $activity->getEndRegistration() || $now < $activity->getStartRegistration())
			throw new AccessDeniedException("You can't register for this activity now.");

		if (!$activity->getModule()->getStudents()->contains($user))
			throw new AccessDeniedException("You can't register for this activity before register module");

		$em = $this->getDoctrine()->getManager();

		if ($activity->getSizeMax() > 1)
 		{
 			$form = $this->creatForm(new ActivityGroupType());
 			$request = $this->getRequest();
 			if ($request->isMethod("POST"))
 			{
 				$form->bind($request);
 				if ($form->isValid() && $group->getStudents()->size() > $activity->getSizeMin() && $group->getStudents()->size() < $activity->getSizeMax())
 				{
 					$group = $form->getData();
					$group->setActivity($activity);

					if ($activity->getStudents()->contains($user))
					{
						$activity->removeStudent($user);
						$em->remove($group);
					}
					else
					{
						$activity->addStudent($user);
						$em->persist($group);
					}
					$em->persist($activity);
					$em->flush();
 				}
 			}
 		}
 		else
 		{
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
 			}
			else
			{
				$group = new ActivityGroup();
	 			$group->setName($user->getUsername());
	 			$group->setActivity($activity);
	 			$group->addStudent($user);
	 			$group->setName($user->getUsername());
				$activity->addStudent($user);
				$em->persist($group);
			}
			$em->persist($activity);
 			$em->flush();
 		}

		return $this->redirect($this->generateUrl('site_activities_activity', array('id' => $activity->getId())));
	}
}
