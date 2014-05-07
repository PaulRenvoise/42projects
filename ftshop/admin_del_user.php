<?php

$page_title = "Supprimer un utilisateur";

require('includes/header.php');

?>

<?php

if (!empty($_POST) && $_POST['submit'] == "Supprimer l'utilisateur")
{
	$error = '';
	if ($_POST['username'] != NULL)
	{
		$id = htmlspecialchars(addslashes($_POST['username']));

		if (($query = mysqli_query($db, "SELECT `level` FROM `users` WHERE `username` = '$id'")) != FALSE)
		{
			if ($user = mysqli_fetch_assoc($query))
			{
				if ($_SESSION['user_level'] < 5)
				{
					if ($user['level'] <= $_SESSION['user_level'])
						mysqli_query($db, "DELETE FROM `users` WHERE `username` = '$id'");
					else
						$error = "Vous ne pouvez pas supprimer d'utilisateur ayant des privileges plus eleves que les votres.";
				}
				else
					mysqli_query($db, "DELETE FROM `users` WHERE `username` = '$id'");
			}
			else
				$error = "Identifiant utilisateur inconnu.";
		}
		else
			$error = "Echec de la requete SQL.";
	}
	else
		$error = "Champ identifiant utilisateur vide.";
}

?>

<h1>Suppression d'utilisateur</h1>

<?php if (empty($_SESSION) || $_SESSION['user_level'] < 4) :?>
<p class="error">
Cette page n'est accessible qu'aux administrateurs du site.
<br \>
Cliquez <a href="index.php">ici</a> pour retourner a l'accueil.
</p>
<?php else : ?>
	<?php if (!empty($error)) : ?>
	<p class="error">
		<?= $error ?>
	</p>
	<?php elseif (isset($error)) : ?>
	<p class="success">
		Compte utilisateur supprime !
	</p>
	<?php endif ; ?>
<p class="tip">
	Supprimer un utilisateur effacera egalement tout son historique de commande de la base de donnees.
</p>
<form action="" method="POST">
	<p>
		<label for="username">Identifiant de l'utilisateur :</label>
		<input type="text" name="username" id="username" size="40">
	</p>
	<p>
		<input type="submit" name="submit" value="Supprimer l'utilisateur">
		<a href="admin.php">Retour à l'administration</a>
	</p>
</form>
<?php endif; ?>

<?php

require('includes/footer.php');

?>
