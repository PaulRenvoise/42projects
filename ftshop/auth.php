<?php

$page_title = 'Connexion';

require('includes/header.php');

if ($_POST['submit'] == "Connexion")
{
	$error = '';

	if (!empty($_POST['username']) && !empty($_POST['password']))
	{
		$id = htmlspecialchars(addslashes($_POST['username']));
		$pw = hash("whirlpool", htmlspecialchars(addslashes($_POST['password'])));
		if (($query = mysqli_query($db, "SELECT `id`, `username`, `level` FROM `users` WHERE `username` = '$id' AND `password` = '$pw'")) != FALSE)
		{
			if ($user = mysqli_fetch_assoc($query))
			{
				$_SESSION['user_id']		= $user['id'];
				$_SESSION['user_username']	= $user['username'];
				$_SESSION['user_level']		= $user['level'];
				if (!isset($_SESSION['cart']))
					$_SESSION['cart']			= array();
				$error = '';
			}
			else
				$error = "Identifiant ou mot de passe invalide.";
		}
		else
			$error = "Identifiant ou mot de passe invalide.";
	}
	else
		$error = "Champ identifiant ou mot de passe vide.";
}

?>
	<h1>Connexion <span>56k</span></h1>
	<?php if (!empty($error)) : ?>
	<p class="error">
		<?= $error ?>
	</p>
	<?php elseif (isset($error)) : ?>
	<p class="success">
		Bienvenue <?= $_SESSION['user_username'] ?> ! Vous êtes désormais connecté !
	</p>
	<?php elseif (!empty($_SESSION['user_id'])) : ?>
	<p class="error">
		Vous êtes déjà connecté.
	</p>
	<?php endif; ?>
	<?php if (!isset($_SESSION['user_id'])) : ?>
	<form action="" method="POST">
		<p>
			<label for="username">Nom d'utilisateur :</label>
			<input type="text" name="username" id="username" size="40">
		</p>
		<p>
			<label for="password">Mot de passe :</label>
			<input type="password" name="password" id="password" size="40">
		</p>
		<p>
			<input type="submit" name="submit" value="Connexion">
			<a href="register.php">Vous n'avez pas encore de compte ?</a>
		</p>
	</form>
	<?php endif; ?>
<?php

require('includes/footer.php');

?>