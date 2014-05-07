<?php

$page_title = 'Articles';

require('includes/header.php');

function fetch_articles($db, &$count)
{
	$statement	= "SELECT `articles`.`id`, `articles`.`name`, `articles`.`price`, `categories`.`id` AS `category_id`, `categories`.`name` AS `category_name` FROM `articles`
		LEFT JOIN `articles_categories` ON `articles_categories`.`article_id` = `articles`.`id`
		LEFT JOIN `categories` ON `categories`.`id` = `articles_categories`.`category_id`";
	$query 		= mysqli_query($db, $statement);
	$articles	= array();
	$count		= 0;
	while ($result = mysqli_fetch_assoc($query))
	{
		$count++;
		$articles[$result['category_id']]['category_name'] = $result['category_name'];
		$articles[$result['category_id']]['articles'][] = array(
			'id'		=> $result['id'],
			'name'		=> $result['name'],
			'price'		=> $result['price']
		);
	}
	return ($articles);
}

$count		= 0;
$articles	= fetch_articles($db, $count);

?>
<h1>Voir les articles <span><?= isset($count) ? ($count . ($count <= 1 ? ' article' : ' articles')) : '' ?></span></h1>
<?php if ($count === 0): ?>
<p class="error">
	Aucun article à afficher.
</p>
<?php else: ?>
<?php
foreach ($articles as $category_id => $category):
$i = 1;
?>
<h2>
	<a href="view_category.php?id=<?= $category_id ?>" title="Voir la catégorie <?= $category['category_name'] ?>"><?= $category['category_name'] ?></a>
</h2>
<table class="articles">
	<thead>
		<tr>
			<th>&nbsp;</th>
			<th>Nom</th>
			<th>Prix</th>
		</tr>
	</thead>
	<tbody>
	<?php foreach ($category['articles'] as $article): ?>
		<tr>
			<td class="nb"><?= $i ?>.</td>
			<td>
				<a href="view_article.php?id=<?= $article['id'] ?>"><?= $article['name'] ?></a>
			</td>
			<td>
				<?= $article['price'] ?> €
			</td>
		</tr>
		<?php $i++ ?>
	<?php endforeach ?>
	</tbody>
</table>
<?php endforeach ?>
<?php endif ?>
<?php

require('includes/footer.php');

?>
