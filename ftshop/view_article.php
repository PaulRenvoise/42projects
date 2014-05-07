<?php

$page_title = 'Voir un article';

require('includes/header.php');

function fetch_article($db, $id)
{
	$statement	= "SELECT `articles`.`id`, `articles`.`name`, `articles`.`image`, `articles`.`price`, `articles`.`description`, `articles`.`views`, `categories`.`id` AS `category_id`, `categories`.`name` AS `category_name` FROM `articles`
		LEFT JOIN `articles_categories` ON `articles_categories`.`article_id` = `articles`.`id`
		LEFT JOIN `categories` ON `categories`.`id` = `articles_categories`.`category_id`
		WHERE `articles`.`id` = '$id'";
	$query 		= mysqli_query($db, $statement);
	$article	= array();
	while ($result = mysqli_fetch_assoc($query))
	{
		$article['id']			= $result['id'];
		$article['name']		= $result['name'];
		$article['image']		= $result['image'];
		$article['price']		= $result['price'];
		$article['description']	= $result['description'];
		$article['views']		= $result['views'];
		if (!isset($article['categories']))
			$article['categories'] = array();
		$article['categories'][$result['category_id']] = $result['category_name'];
	}
	return (count($article) > 0 ? $article : false);
}

function increment_views($db, $id, $views)
{
	$query = mysqli_query($db, "UPDATE `articles` SET `views` = '$views' WHERE `id` = '$id'");
}

if (isset($_GET['id']) && is_numeric($_GET['id']))
{
	$id			= htmlspecialchars(addslashes($_GET['id']));
	$article	= fetch_article($db, $id);
	$span		= '';
	$article['views']++;
	increment_views($db, $id, $article['views']);
	foreach ($article['categories'] as $category_id => $name) {
		$span .= '<a href="view_category?id=' . $category_id . '" title="Aller voir la catégorie ' . $name . '">' . $name . '</a>, ';
	}
	$span = substr($span, 0, -2);
}

if (!empty($_POST['submit']) && $_POST['submit'] == 'Ajouter au panier')
{
	$error = '';
	if (!empty($id) && !empty($_POST['quantity']) && is_numeric($_POST['quantity']))
	{
		$quantity = htmlspecialchars(addslashes($_POST['quantity']));
		if (($quantity >= 1 && $quantity <= 99))
		{
			if (isset($_SESSION['cart'][$id]))
			{
				if (($_SESSION['cart'][$id] + $quantity) <= 99)
					$_SESSION['cart'][$id] += $quantity;
				else
					$error = 'Vous ne pouvez pas ajouter une telle quantité.';
			}
			else
				$_SESSION['cart'][$id] = $quantity;
		}
		else
			$error = 'Vous ne pouvez pas ajouter une telle quantité.';
	}
	else
		$error = 'Impossible d\'ajouter au panier.';
}

?>
<h1><?= !empty($article['name']) ? $article['name'] . ' <span>' . $span . '</span>' : 'Voir un article' ?></h1>
<?php if (!empty($error)): ?>
<p class="error">
	<?= $error ?>
</p>
<?php elseif (isset($error)): ?>
<p class="success">
	L'article '<?= $article['name'] ?>'x<?= $quantity ?> a bien été ajouté au panier.
</p>
<?php endif ?>
<?php if (isset($_GET['id']) && is_numeric($_GET['id']) && $article !== false): ?>
<div class="article">
	<div class="img">
		<img src="<?= $article['image'] ?>" alt="<?= $article['name'] ?>" title="<?= $article['name'] ?>">
	</div>
	<aside class="infos">
		<h2>Informations</h2>
		<p class="price">
			<?= $article['price'] ?><span>€</span>
		</p>
		<h2 class="margin">Ajouter au panier</h2>
		<form action="" method="POST" class="addtocart">
			<p>
				<input type="number" name="quantity" min="1" max="99" value="1">
				<input type="submit" name="submit" value="Ajouter au panier">
			</p>
		</form>
	</aside>
	<div class="clear"></div>
	<h2>Description</h2>
	<p>
		<?= nl2br($article['description']) ?>
	</p>
	<h2>Statistiques</h2>
	<p>
		Cet article a été consulté <?= $article['views'] ?> fois.
	</p>
</div>
<?php else: ?>
<p class="error">
	Il n'y a aucun article à afficher.
</p>
<?php endif ?>
<?php

require('includes/footer.php');

?>
