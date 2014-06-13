<?php

$page_title = 'Mon panier';

require('includes/header.php');

function get_total($articles)
{
	$total = array(
		'price'		=> 0,
		'count'		=> 0
	);
	foreach ($articles as $key => $value) {
		$total['count'] += $value['quantity'];
		$total['price'] += ($value['price'] * $value['quantity']);
	}
	return $total;
}

if (isset($_GET['del']) && is_numeric($_GET['del']))
{
	$error		= '';
	$success	= '';
	$del_id	= htmlspecialchars(addslashes($_GET['del']));
	if ($del_id == -1)
	{
		$_SESSION['cart'] = array();
		$success = 'Votre panier est désormais vide.';
	}
	else
	{
		if (isset($_SESSION['cart'][$del_id]))
		{
			unset($_SESSION['cart'][$del_id]);
			$success = 'L\'article a bien été supprimé de votre panier.';
		}
		else
			$error = 'Cet article n\'est pas dans votre panier.';
	}
}
else if (isset($_GET['add']) && is_numeric($_GET['add']))
{
	$error	= '';
	$add_id	= htmlspecialchars(addslashes($_GET['add']));
	if (isset($_SESSION['cart'][$add_id]))
	{
		if ($_SESSION['cart'][$add_id] > 98)
			$error = 'Vous ne pouvez pas ajouter plus à la quantité actuelle.';
		else
			$_SESSION['cart'][$add_id]++;
	}
	else
		$error = 'Cet article n\'est pas dans votre panier.';
}
else if (isset($_GET['remove']) && is_numeric($_GET['remove']))
{
	$error	= '';
	$remove_id	= htmlspecialchars(addslashes($_GET['remove']));
	if (isset($_SESSION['cart'][$remove_id]))
	{
		if ($_SESSION['cart'][$remove_id] < 2)
			$error = 'Vous ne pouvez pas retirer plus à la quantité actuelle.';
		else
			$_SESSION['cart'][$remove_id]--;
	}
	else
		$error = 'Cet article n\'est pas dans votre panier.';
}

$cart = $_SESSION['cart'];
$articles = array();
if (count($cart) > 0)
{
	$entries = '';
	foreach ($cart as $key => $value) {
		$entries .= "`articles`.`id` = '" . $key . "' OR ";
	}
	$entries = substr($entries, 0, -4);
	$query = mysqli_query($db, "SELECT `articles`.`id`, `articles`.`name`, `articles`.`price` FROM `articles` WHERE " . $entries);
	while ($result = mysqli_fetch_assoc($query))
	{
		$articles[] = array(
			'id'		=> $result['id'],
			'name'		=> $result['name'],
			'price'		=> $result['price'],
			'quantity'	=> $cart[$result['id']]
		);
	}
}
$total	= get_total($articles);
$i 		= 1;

?>
<h1>Mon panier <span>En plastique recyclé</span></h1>
<?php if (count($cart) > 0): ?>
<p>
	Il y a <?= count($cart) ?> <?= count($cart) <= 1 ? 'article' : 'articles' ?> dans votre panier.
</p>
<?php endif ?>
<?php if (!empty($error)): ?>
<p class="error">
	<?= $error ?>
</p>
<?php elseif (!empty($success)): ?>
<p class="success">
	<?= $success ?>
</p>
<?php endif ?>
<?php if (count($cart) > 0): ?>
<table class="articles">
	<thead>
		<tr>
			<th>&nbsp;</th>
			<th>Nom</th>
			<th>Prix</th>
			<th>Quantité</th>
			<th>Action</th>
		</tr>
	</thead>
	<tbody>
	<?php foreach ($articles as $key => $article): ?>
		<tr>
			<td class="nb"><?= $i ?>.</td>
			<td>
				<a href="view_article.php?id=<?= $article['id'] ?>"><?= $article['name'] ?></a>
			</td>
			<td>
				<?= $article['price'] ?> €
			</td>
			<td>
				<?= $article['quantity'] ?>
			</td>
			<td class="actions">
				<a href="?add=<?= $article['id'] ?>" class="plus" title="Ajouter 1 à la quantité">+</a>
				<a href="?remove=<?= $article['id'] ?>" class="minus" title="Retirer 1 à la quantité">-</a>
				<a href="?del=<?= $article['id'] ?>">Supprimer</a>
			</td>
		</tr>
		<?php $i++ ?>
	<?php endforeach ?>
	</tbody>
</table>
<p class="right">
	<a href="?del=-1">Vider mon panier</a>
</p>
<h2>Total</h2>
<p>
	Vous avec <?= $total['count'] ?> <?= $total['count'] <= 1 ? 'article' : 'articles' ?> dans votre panier, pour un total de	<?= $total['price'] ?> €.
</p>
<p class="right">
	<a href="checkout.php">Passer commande</a>
</p>
<?php else: ?>
<p class="error">
	Vous n'avez aucun produit dans votre panier.<br>
	Allez donc vous balader un peu !
</p>
<?php endif ?>
<?php

require('includes/footer.php');

?>