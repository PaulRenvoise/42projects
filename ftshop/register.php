<?php

$page_title = 'Inscription';

require('includes/header.php');

if (empty($_SESSION['user_username']))
{
	$error = "";
	if (!empty($_POST) && $_POST['submit'] == "Inscription")
	{
		if (!empty($_POST['username']))
			$username = htmlspecialchars(addslashes($_POST['username']));
		if (!empty($_POST['password']))
			$password = htmlspecialchars(addslashes($_POST['password']));
		if (!empty($_POST['confirm']))
			$confirm = htmlspecialchars(addslashes($_POST['confirm']));

		if (!empty($username) && !empty($password) && !empty($confirm))
		{
			if ($password == $confirm)
			{
				$query 	= mysqli_query($db, "SELECT `id` FROM `users` WHERE `username` = '$username'");
				$result = mysqli_fetch_assoc($query);
				if (count($result) > 0)
					$error = 'Un compte existe déjà avec ce nom d\'utilisateur.';
				else
				{
					$password = hash('whirlpool', $password);
					$query = mysqli_query($db, "INSERT INTO `users` (`username`, `password`) VALUES ('$username', '$password')");
					if ($query === false)
						$error = 'Erreur lors de la création du compte, veuillez réessayer.';
					else
					{
						$_SESSION['user_id']		= mysqli_insert_id($db);
						$_SESSION['user_username']	= $username;
						$_SESSION['user_level']		= 1;
						if (!isset($_SESSION['cart']))
							$_SESSION['cart'] = array();
						unset($username);
						unset($password);
						unset($confirm);
					}
				}
			}
			else
				$error = "Les deux mots de passe ne correspondent pas.";
		}
		else
			$error = "Tous les champs ne sont pas remplis.";
	}
}
else
	$error = "Veuillez vous deconnecter pour creer un nouveau compte.";

?>
<h1>Inscription <span>Allez viens, on est bien !</span></h1>
<?php if (empty($error) && !empty($_POST)) : ?>
<p class="success">
	Votre compte a été créé avec succès !<br>
	Rechargez la page et vous serez connecté.
</p>
<?php elseif (!empty($error)) : ?>
<p class="error">
	<?= $error ?>
</p>
<?php endif; ?>
<?php if ($error != "Veuillez vous deconnecter pour creer un nouveau compte."): ?>
	<p>
		Créez votre compte en quelques secondes !
	</p>
	<form action="" method="POST">
		<p>
			<label for="username">Nom d'utilisateur :</label>
			<input type="text" name="username" id="username" value="<?= !empty($username) ? $username : '' ?>" size="40">
		</p>
		<p>
			<label for="password">Mot de passe :</label>
			<input type="password" name="password" id="password" value="<?= !empty($password) ? $password : '' ?>" size="40">
		</p>
		<p>
			<label for="confirm">Confirmez :</label>
			<input type="password" name="confirm" id="confirm" value="<?= !empty($confirm) ? $confirm : '' ?>" size="40">
		</p>
		<p>
			<input type="submit" name="submit" value="Inscription">
			<a href="auth.php">Vous avez déjà un compte ?</a>
		</p>
	</form>
<?php endif ;?>
<?php

require('includes/footer.php');

?>
