<?php

$page_title = "Ajouter une catégorie";

require('includes/header.php');

if (!empty($_POST['submit']) && $_POST['submit'] == "Ajouter la catégorie")
{
	$error 	= '';
	$name 	= htmlspecialchars(addslashes($_POST['name']));
	$query 	= mysqli_query($db, "SELECT `id` FROM `categories` WHERE `name` = '$name'");
	$result = mysqli_fetch_assoc($query);
	if (count($result) > 0)
		$error = 'Une catégorie porte déjà ce nom.';
	else
	{
		$query = mysqli_query($db, "INSERT INTO `categories` (`name`) VALUES ('$name')");
		if (mysqli_affected_rows($db) == 0)
		{
			$error = "Erreur lors de l'ajout de la catégorie.";
		}
	}
}

?>
<h1>Ajouter une catégorie</h1>
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
		La catégorie a été ajoutée.
	</p>
	<?php endif ?>
<form action="" method="POST">
	<p>
		<label for="name">Nom de la catégorie :</label>
		<input type="text" name="name" id="name" size="40">
	</p>
	<p>
		<input type="submit" name="submit" value="Ajouter la catégorie">
		<a href="admin.php">Retour à l'administration</a>
	</p>
</form>
<?php endif; ?>
<?php

require('includes/footer.php');

?>
