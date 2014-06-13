<?php

$page_title = 'Catégories';

require('includes/header.php');

function fetch_categories($db)
{
	$statement	= "SELECT `categories`.`id`, `categories`.`name` AS `category_name`, `articles_categories`.`article_id`, `articles`.`image` AS `article_image` FROM `categories`
		LEFT JOIN `articles_categories` ON `articles_categories`.`category_id` = `categories`.`id`
		LEFT JOIN `articles` ON `articles`.`id` = `articles_categories`.`article_id`";
	$query 		= mysqli_query($db, $statement);
	$categories = array();
	while ($result = mysqli_fetch_assoc($query))
	{
		if (array_key_exists($result['id'], $categories))
		{
			$categories[$result['id']]['count']++;
			if ($categories[$result['id']]['image'] == NULL && $result['article_image'] !== NULL)
			{
				$categories[$result['id']]['image'] = $result['article_image'];
			}
		}
		else
		{
			$categories[$result['id']]['name'] 	= $result['category_name'];
			$categories[$result['id']]['image'] = $result['article_image'];
			$categories[$result['id']]['count'] = (($result['article_id'] == NULL) ? 0 : 1);
		}
	}
	return (count($categories) > 0 ? $categories : array());
}

$categories = fetch_categories($db);

?>
<h1>Liste des catégories <span>Such choice</span></h1>
<?php if (count($categories) > 0): ?>
<div class="categories">
	<?php foreach ($categories as $id => $category): ?>
	<a href="view_category.php?id=<?= $id ?>" class="category" title="<?= $category['name'] ?>">
		<h1><?= $category['name'] ?></h1>
		<?php if ($category['image'] !== NULL): ?>
			<img src="<?= $category['image'] ?>" alt="<?= $category['name'] ?>" title="<?= $category['name'] ?>">
		<?php else: ?>
			<span class="noimg">?</span>
		<?php endif ?>
		<span class="count"><?= $category['count'] ?> <?= $category['count'] <= 1 ? 'article' : 'articles' ?></span>
	</a>
	<?php endforeach ?>
</div>
<?php else: ?>
<p class="error">
	Aucune catégorie à afficher.
</p>
<?php endif ?>
<?php

require('includes/footer.php');

?>