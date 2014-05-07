<?php

$page_title = "Ajouter un utilisateur";

require('includes/header.php');

if (!empty($_POST) && $_POST['submit'] == "Ajouter l'utilisateur")
{
	$error = '';
	if ($_POST['username'] != NULL && $_POST['password'] != NULL)
	{
		$id = htmlspecialchars(addslashes($_POST['username']));
		$pw = hash("whirlpool", htmlspecialchars(addslashes($_POST['password'])));
		$level = (empty($_POST['level'])) ? 1 : $_POST['level'];

		if (is_numeric($level))
		{
			if ($_SESSION['user_level'] < 5)
			{
				if ($level < 5 && $level >= 0)
				{
					if (($query = mysqli_query($db, "SELECT `id`, `username`, `level` FROM `users` WHERE `username` = '$id' AND `password` = '$pw'")) != FALSE)
					{
						if ($user = mysqli_fetch_assoc($query))
							$error = "Utilisateur deja en base de donne.";
						else
							mysqli_query($db, "INSERT INTO `users` (`username`, `password`, `level`) VALUES ('$id', '$pw', '$level')");
					}
					else
						$error = "Echec de la requete SQL.";
				}
				else if ($level > $_SESSION['user_level'])
					$error = "Vous ne pouvez pas creer de compte utilisateur ayant des privileges plus eleves que les votres.";
				else if ($level < 0)
					$error = "Vous ne pouvez pas creer de compte utilisateur ayant des privileges inferieurs a 0.";
			}
			else
			{
				if ($level <= 5 && $level >= 0)
				{
					if (($query = mysqli_query($db, "SELECT `id`, `username`, `level` FROM `users` WHERE `username` = '$id' AND `password` = '$pw'")) != FALSE)
					{
						if ($user = mysqli_fetch_assoc($query))
							$error = "Utilisateur deja en base de donne.";
						else
							mysqli_query($db, "INSERT INTO `users` (`username`, `password`, `level`) VALUES ('$id', '$pw', '$level')");
					}
					else
						$error = "Echec de la requete SQL.";
				}
				else if ($level > $_SESSION['user_level'])
					$error = "Vous ne pouvez pas creer de compte utilisateur ayant des privileges plus eleves que les votres.";
				else if ($level < 0)
					$error = "Vous ne pouvez pas creer de compte utilisateur ayant des privileges inferieurs a 0.";
			}
		}
		else
			$error = "Niveau de privilege errone.";
	}
	else
		$error = "Champ identifiant ou mot de passe vide.";
}

?>

<h1>Ajout d'utilisateur</h1>

<?php if (empty($_SESSION) || $_SESSION['user_level'] < 4) :?>
<p class="error">
	Cette page n'est accessible qu'aux administrateurs du site.<br \>
	Cliquez <a href="index.php">ici</a> pour retourner a l'accueil.
</p>
<?php else : ?>
	<?php if (!empty($error)) : ?>
	<p class="error">
		<?= $error ?>
	</p>
	<?php elseif (isset($error)) : ?>
	<p class="success">
		Compte utilisateur cree !
	</p>
	<?php endif ; ?>
<p class="tip">
	Privileges:
	<br />
	1-2-3 : Utilisateur. 4: Admin. 5: Super-admin.
</p>
<form action="" method="POST">
	<p>
		<label for="username">Identifiant de l'utilisateur :</label>
		<input type="text" name="username" id="username" size="40">
	</p>
	<p>
		<label for="password">Mot de passe de l'utilisateur :</label>
		<input type="password" name="password" id="password" size="40">
	</p>
	<p>
		<label for="level">Niveau de privilege :</label>
		<input type="number" name="level" id="level" min="1" max="5" value="1">
	</p>
	<p>
		<input type="submit" name="submit" value="Ajouter l'utilisateur">
		<a href="admin.php">Retour à l'administration</a>
	</p>
</form>
<?php endif; ?>

<?php

require('includes/footer.php');

?>
