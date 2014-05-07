<?php

$page_title = 'Voir une catégorie';

require('includes/header.php');

function fetch_articles($db, $id)
{
	$articles	= array();
	$statement	= "SELECT `articles`.`id`, `articles`.`name`, `articles`.`price`, `categories`.`name` AS `category_name` FROM `articles`
		LEFT JOIN `articles_categories` ON `articles_categories`.`article_id` = `articles`.`id`
		LEFT JOIN `categories` ON `categories`.`id` = `articles_categories`.`category_id`
		WHERE `articles_categories`.`category_id` = '$id'";
	if (($query = mysqli_query($db, $statement)) != FALSE)
	{
		while ($result = mysqli_fetch_assoc($query))
			$articles[] = $result;
		return (count($articles) > 0 ? $articles : array());
	}
}

if (isset($_GET['id']) && is_numeric($_GET['id']))
{
	$id			= htmlspecialchars(addslashes($_GET['id']));
	$articles	= fetch_articles($db, $id);
	$name		= '';
	$i			= 1;
	if (count($articles) > 0)
		$name = $articles[0]['category_name'];
}

?>
<h1>Voir une catégorie <span><?= !empty($name) ? $name : '' ?></span></h1>
<?php if (isset($_GET['id']) && is_numeric($_GET['id']) && count($articles) > 0): ?>
<p>
	Voici tous les articles appartenant à la catégorie <?= !empty($name) ? $name : '' ?>.
</p>
<table class="articles">
	<thead>
		<tr>
			<th>&nbsp;</th>
			<th>Nom</th>
			<th>Prix</th>
		</tr>
	</thead>
	<tbody>
	<?php foreach ($articles as $id => $article): ?>
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
<?php else: ?>
<p class="error">
	Il n'y a aucun article à afficher.
</p>
<?php endif ?>
<?php

require('includes/footer.php');

?>
