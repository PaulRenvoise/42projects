<?php

$page_title = "Modifier une catégorie";

require('includes/header.php');

function fetch_categories($db)
{
	$categories = array();
	$query 	= mysqli_query($db, "SELECT * FROM `categories`");
	while ($result = mysqli_fetch_assoc($query))
		$categories[] = $result;
	return (count($categories) > 0 ? $categories : array());
}

if (!isset($_GET['id']))
	$categories = fetch_categories($db);
else if (!empty($_GET['id']) && !isset($_POST['submit']))
{
	$id 	= htmlspecialchars(addslashes($_GET['id']));
	$name 	= '';

	$query 	= mysqli_query($db, "SELECT `name` FROM `categories` WHERE `id` = '$id'");
	$result = mysqli_fetch_assoc($query);
	if (count($result) == 0)
	{
		$error = 'Cette catégorie n\'existe pas.';
		$categories = fetch_categories($db);
	}
	else
		$name = $result['name'];
}
else if (!empty($_POST['submit']) && $_POST['submit'] == "Modifier la catégorie")
{
	$error 	= '';
	$id 	= htmlspecialchars(addslashes($_POST['id']));
	$name 	= htmlspecialchars(addslashes($_POST['name']));

	$query 	= mysqli_query($db, "SELECT `id` FROM `categories` WHERE `name` = '$name'");
	$result = mysqli_fetch_assoc($query);
	if (count($result) > 0)
	{
		if ($result['id'] == $id)
			$error = 'Cette catégorie porte déjà ce nom.';
		else
			$error = 'Une catégorie porte déjà ce nom.';
	}
	else
	{
		$query = mysqli_query($db, "UPDATE `categories` SET `name` = '$name' WHERE `id` = '$id'");
		if (mysqli_affected_rows($db) == 0)
		{
			$error = 'Erreur lors de la mise à jour de la catégorie.';
		}
	}
}

?>
<h1>Modifier une catégorie<?= isset($name) ? ' <span>' . $name . '</span>' : '' ?></h1>
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
		La catégorie a été mise à jour.
	</p>
	<?php endif; ?>
	<?php if (!isset($_GET['id']) || empty($name)): ?>
		<?php if (count($categories) > 0): ?>
		<p>
			Quelle catégorie voulez-vous modifier ?
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
			Aucune catégorie à modifier.
		</p>
		<?php endif; ?>
	<p class="right">
		<a href="admin.php">Retour à l'administration</a>
	</p>
	<?php else : ?>
	<form action="" method="POST">
		<input type="hidden" name="id" value="<?= $id ?>">
		<p>
			<label for="name">Nom de la catégorie :</label>
			<input type="text" name="name" id="name" size="40" value="<?= $name ?>">
		</p>
		<p>
			<input type="submit" name="submit" value="Modifier la catégorie">
			<a href="admin.php">Retour à l'administration</a>
		</p>
	</form>
	<?php endif; ?>
<?php endif; ?>
<?php

require('includes/footer.php');

?>
