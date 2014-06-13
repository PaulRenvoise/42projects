<?php

$page_title = "Supprimer une catégorie";

require('includes/header.php');

function fetch_categories($db)
{
	$categories = array();
	$query = mysqli_query($db, "SELECT * FROM `categories`");
	while ($result = mysqli_fetch_assoc($query))
		$categories[] = $result;
	return (count($categories) > 0 ? $categories : array());
}

if (!empty($_GET['id']))
{
	$id 	= htmlspecialchars(addslashes($_GET['id']));
	$name 	= '';
	$error	= '';

	$query 	= mysqli_query($db, "DELETE FROM `categories` WHERE `id` = '$id'");
	if (mysqli_affected_rows($db) == 0)
	{
		$error = 'Cette catégorie n\'existe pas.';
		$categories = fetch_categories($db);
	}
}

$categories = fetch_categories($db);

?>
<h1>Supprimer une catégorie</h1>
<?php if (empty($_SESSION) || $_SESSION['user_level'] < 4) :?>
<p class="error">
Cette page n'est accessible qu'aux administrateurs du site.
<br \>
Cliquez <a href="index.php">ici</a> pour retourner a l'accueil.
</p>
<?php else : ?>
	<?php if (!empty($error)): ?>
	<p class="error">
		<?= $error ?>
	</p>
	<?php elseif(isset($error)) : ?>
	<p class="success">
		La catégorie a été supprimée.
	</p>
	<?php endif ?>
	<?php if (count($categories) > 0) : ?>
	<p>
		Quelle catégorie voulez-vous supprimer ?
	</p>
	<ul class="spaced">
	<?php foreach ($categories as $key => $value): ?>
		<li>
			<a href="?id=<?= $value['id'] ?>"><?= $value['name'] ?></a>
		</li>
	<?php endforeach ?>
	</ul>
	<?php else : ?>
	<p class="error">
		Aucune catégorie à supprimer.
	</p>
	<?php endif ?>
<p class="right">
	<a href="admin.php">Retour à l'administration</a>
</p>
<?php endif; ?>
<?php

require('includes/footer.php');

?>
