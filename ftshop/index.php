<?php

$page_title = 'Accueil';

require('includes/header.php');

function article_exists($articles, $result)
{
	if (count($articles) >= 8)
		return true;
	foreach ($articles as $key => $value) {
		if ($value['id'] == $result['id'])
			return true;
	}
	return false;
}

function fetch_articles($db, &$count, &$views)
{
	$articles = array();
	$count = 0;
	$statement = "SELECT `articles`.`id`, `articles`.`name`, `articles`.`image`, `articles`.`views`, `categories`.`id` AS `category_id`, `categories`.`name` AS `category_name` FROM `articles`
		LEFT JOIN `articles_categories` ON `articles_categories`.`article_id` = `articles`.`id`
		LEFT JOIN `categories` ON `categories`.`id` = `articles_categories`.`category_id`
		ORDER BY `articles`.`views` DESC";
	if (($query = mysqli_query($db, $statement)) != FALSE)
	{
		while ($result = mysqli_fetch_assoc($query))
		{
			if (!article_exists($articles, $result))
			{
				$count++;
				$views += $result['views'];
				$articles[] = $result;
			}
		}
	}
	return ($articles);
}

$count = 0;
$views = 0;
$articles = fetch_articles($db, $count, $views);

?>
<h1>Accueil <span>Home, sweet home...</span></h1>
<p>
	Voici notre sélection des 8 articles les plus vus, toutes catégories confondues.
</p>
<?php if ($count === 0): ?>
<p class="error">
	Aucun article à afficher.
</p>
<?php else: ?>
<div class="categories">
	<?php foreach ($articles as $article): ?>
	<a href="view_article.php?id=<?= $article['id'] ?>" class="category" title="<?= $article['name'] ?>">
		<h1 class="tiny"><?= $article['name'] ?></h1>
		<?php if ($article['image'] !== NULL): ?>
			<img src="<?= $article['image'] ?>" alt="<?= $article['name'] ?>" title="<?= $article['name'] ?>">
		<?php else: ?>
			<span class="noimg">?</span>
		<?php endif ?>
		<span class="count"><?= $article['views'] ?> <?= $article['views'] <= 1 ? 'vue' : 'vues' ?></span>
	</a>
	<?php endforeach ?>
</div>
<h2>Statistiques</h2>
<p>
	Il y a eu <?= $views ?> <?= $views <= 1 ? 'consultation' : 'consultations' ?> d'articles jusqu'à présent.
</p>
<?php endif ?>
<?php

require('includes/footer.php');

?>
