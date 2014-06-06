<?php

namespace Site\ActivityBundle\Controller;

use Sonata\AdminBundle\Controller\CRUDController;
use Site\ForumBundle\Entity\ForumSubboard;
use Site\ActivityBundle\Entity\ActivityGroup;
use Site\IntraBundle\Entity\Event;
use Site\ActivityBundle\Form\AdminUploadType;

class ActivityAdminController extends CRUDController
{
	/**
	 * return the Response object associated to the create action
	 *
	 * @throws \Symfony\Component\Security\Core\Exception\AccessDeniedException
	 * @return Response
	 */
	public function createAction()
	{
		// the key used to lookup the template
		$templateKey = 'edit';

		if (false === $this->admin->isGranted('CREATE')) {
			throw new AccessDeniedException();
		}

		$object = $this->admin->getNewInstance();

		$this->admin->setSubject($object);

		/** @var $form \Symfony\Component\Form\Form */
		$form = $this->admin->getForm();
		$form->setData($object);

		if ($this->getRestMethod() == 'POST') {
			$form->submit($this->get('request'));

			$isFormValid = $form->isValid();

			// persist if the form was valid and if in preview mode the preview was approved
			if ($isFormValid && (!$this->isInPreviewMode() || $this->isPreviewApproved())) {

				if (false === $this->admin->isGranted('CREATE', $object)) {
					throw new AccessDeniedException();
				}

				$this->admin->create($object);

				// create ForumBoard for Module
				$em = $this->getDoctrine()->getManager();
				$board = $em->getRepository("SiteForumBundle:ForumBoard")->findOneBy(array("title" => $object->getModule()->getName()));

				$subboard = new ForumSubboard();
				$subboard->setTitle($object->getName());
				$subboard->setBoard($board);

				if ($object->getRandomGroups() == true)
				{
					$users = $object->getModule()->getStudents()->toArray();
					while (count($users))
					{
						if ($object->getSizeMax() > count($users))
							$keys = array_keys($users);
						else
							$keys = array_rand($users, $object->getSizeMax());
						if ($keys)
						{
							$group = new ActivityGroup();
							$group->setName($users[$keys[0]]->getUsername(). "_" .$object->getName());
							$group->setActivity($object);
							foreach($keys as $key)
							{
								$object->addStudent($users[$key]);
								$event = new Event();
								$event->setInfo($object->getName());
								$event->setUser($users[$key]);
								$event->setDate(new \Datetime());
								$event->setType("registration");
								$event->setDescription("FEED_REGISTRATION_ACTIVITY_GROUP_RANDOM");
								$em->persist($event);
								$group->addStudent($users[$key]);
								unset($users[$key]);
							}
							$group->peers = 0;
							$em->persist($object);
							$em->persist($group);
						}
					}
				}
				$em->persist($subboard);
				$em->flush();

				if ($this->isXmlHttpRequest()) {
					return $this->renderJson(array(
						'result' => 'ok',
						'objectId' => $this->admin->getNormalizedIdentifier($object)
					));
				}

				$this->addFlash('sonata_flash_success', $this->admin->trans('flash_create_success', array('%name%' => $this->admin->toString($object)), 'SonataAdminBundle'));

				// redirect to edit mode
				return $this->redirectTo($object);
			}

			// show an error message if the form failed validation
			if (!$isFormValid) {
				if (!$this->isXmlHttpRequest()) {
					$this->addFlash('sonata_flash_error', $this->admin->trans('flash_create_error', array('%name%' => $this->admin->toString($object)), 'SonataAdminBundle'));
				}
			} elseif ($this->isPreviewRequested()) {
				// pick the preview template if the form was valid and preview was requested
				$templateKey = 'preview';
				$this->admin->getShow();
			}
		}

		$view = $form->createView();

		// set the theme for the current Admin Form
		$this->get('twig')->getExtension('form')->renderer->setTheme($view, $this->admin->getFormTheme());

		return $this->render($this->admin->getTemplate($templateKey), array(
			'action' => 'create',
			'form'   => $view,
			'object' => $object,
		));
	}

	public function noteAction()
	{
		$data = array();
		$id = $this->get('request')->get($this->admin->getIdParameter());

		$object = $this->admin->getObject($id);
		$form = $this->createForm(new AdminUploadType());
		$data['form'] = $form->createView();
		if (!$object)
			throw new NotFoundHttpException(sprintf('unable to find the object with id : %s', $id));

		$request = $this->getRequest();
		if ($request->isMethod("POST"))
		{
			$form->bind($request);
			if ($form->isValid())
			{
				$date = new \Datetime();
				$filename = "notes_" .$date->format("d_m_Y_H_i_s"). ".csv";
				$formData = $form->getData();
				$formData['Correction']->move("./", $filename);
				$row = 1;
				if (($handle = fopen($filename, "r")))
				{
					while (($content = fgetcsv($handle, 1000, ",")))
					{
/*						$correction = new \ScaleGroup();
						$correction->setScale();
						$correction->setNote($content[2]);
						$correction->setGroup();
						$correction->setRater();
						$correction->setActivity();
						$correction->setDone(true);*/
					}
					fclose($handle);
				}
			}
		}
	}
}
