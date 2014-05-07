<?php

$page_title = "Modifier un utilisateur";

require('includes/header.php');

?>

<?php

if (!empty($_POST) && $_POST['submit'] == "Acceder au panel de modification")
{
	$id = htmlspecialchars(addslashes($_POST['username']));
	$error = '';

	$query = mysqli_query($db, "SELECT `id`, `username`, `level` FROM `users` WHERE `username` = '$id'");
	$result = mysqli_fetch_assoc($query);
	if (count($result) == 0)
		$error = "Cet utilisateur n'existe pas.";
	else
	{
		$_SESSION['mod_user_id'] = $result['id'];
		$_SESSION['mod_user_name'] = $result['username'];
	}
}
if (!empty($_POST) && $_POST['submit'] == "Modifier l'utilisateur")
{
	$error = "";
	$id = $_SESSION['mod_user_id'];

	if ($_POST['username'])
	{
		$username = htmlspecialchars(addslashes($_POST['username']));

		mysqli_query($db, "UPDATE `users` SET `username` = '$username' WHERE `id` = '$id'");
		if (mysqli_affected_rows($db) == 0)
			$error = "Erreur lors de la mise à jour de l'utilisateur.1";
		else
			$_SESSION['mod_user_name'] = $username;
	}
	if ($_POST['password'])
	{
		$newpassword = hash("whirlpool", htmlspecialchars(addslashes($_POST['password'])));

		mysqli_query($db, "UPDATE `users` SET `password` = '$newpassword' WHERE `id` = '$id'");
		if (mysqli_affected_rows($db) == 0)
			$error = "Erreur lors de la mise à jour de l'utilisateur.2";
	}
	if ($_POST['level'])
	{
		$level = htmlspecialchars(addslashes($_POST['level']));
		mysqli_query($db, "UPDATE `users` SET `level` = '$level' WHERE `id` = '$id'");
		if (mysqli_affected_rows($db) == 0)
			$error = "Erreur lors de la mise à jour de l'utilisateur.3";
	}
}

?>

<h1>Modification des informations d'un utilisateur<?= isset($_SESSION['mod_user_name']) ? ' <span>' . $_SESSION['mod_user_name'] . '</span>' : '' ?></h1>

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
	<?php elseif(isset($error) && $_POST['submit'] == "Modifier l'utilisateur"): ?>
	<p class="success">
		Les informations de l'utilisateur ont ete mises a jour.
	</p>
	<?php endif ?>
	<?php if (!empty($_SESSION['mod_user_id'])): ?>
	<p class="tip">
		Laissez les champs vides pour ne pas modifier la base de donnee.
	</p>
	<form action="" method="POST">
		<p>
			<label for="username">Nouvel identifiant :</label>
			<input type="text" name="username" id="username" size="40">
		</p>
		<p>
			<label for="password">Nouveau mot de passe :</label>
			<input type="password" name="password" id="password" size="40">
		</p>
		<p>
			<label for="level" title="1-2-3: Utilisateur, 4: Admin, 5:Super-admin"> Nouveau niveau de privilege :</label>
			<input type="number" name="level" id="level" min="1" max="<?= $_SESSION['user_level'] ?>">
		</p>
		<p>
			<input type="submit" name="submit" value="Modifier l'utilisateur">
			<a href="admin.php">Retour à l'administration</a>
		</p>
	</form>
	<?php else: ?>
	<form action="" method="POST">
		<p>
			<label for="username">Identifiant de l'utilisateur :</label>
			<input type="text" name="username" id="username" size="40">
		</p>
		<p>
			<input type="submit" name="submit" value="Acceder au panel de modification">
			<a href="admin.php">Retour à l'administration</a>
		</p>
	</form>
	<?php endif; ?>
<?php endif; ?>
<?php

require('includes/footer.php');

?>
