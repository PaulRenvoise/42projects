<?php

namespace Site\ForumBundle\Form;

use Symfony\Component\Form\AbstractType;
use Symfony\Component\Form\FormBuilderInterface;
use Symfony\Component\OptionsResolver\OptionsResolverInterface;
use Symfony\Component\Validator\Constraints\Email;
use Symfony\Component\Validator\Constraints\Length;
use Symfony\Component\Validator\Constraints\NotSite;
use Symfony\Component\Validator\Constraints\Collection;

class CommentType extends AbstractType
{
	public function buildForm(FormBuilderInterface $builder, array $options)
	{
		$builder
			->add('content', 'text');
	}

	public function setDefaultOptions(OptionsResolverInterface $resolver)
	{
		$collectionConstraint = new Collection(array(
			'content' => array(new NotSite(array('message' => 'Message should not be site.')),new Length(array('min' => 1)))));
		$resolver->setDefaults(array('constraints' => $collectionConstraint));
	}

	public function getName()
	{
		return ("site_forumbundle_commenttype");
	}
}
