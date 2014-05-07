<?php

session_start();

require('constants.php');
require('database.php');

if ($db === false)
{
	header("Location: install.php");
	exit;
}

if (!empty($_SESSION['user_id']) && $_SESSION['user_id'] == 'deleted')
{
	session_destroy();
	setcookie(session_name(), "", (time() - 3600), "/");
	header("Location: index.php");
	exit;
}

date_default_timezone_set('Europe/Paris');
setlocale(LC_TIME, 'fr_FR');

?>
<!DOCTYPE html>
<html>
<head>
	<meta charset="utf-8">
	<title><?php if (!empty($page_title)) { echo $page_title . ' - '; } ?>Rushop</title>
	<link rel="stylesheet" href="style/style.css">
</head>
<body>
	<header>
		<h1 class="sitename">
			<a href="http://<?= BASE_URL ?>" title="Accueil">Rushop</a>
		</h1>
		<nav>
			<ul>
				<li>
					<a href="articles.php">Articles</a>
				</li>
				<li>
					<a href="categories.php">Catégories</a>
				</li>
			</ul>
		</nav>
		<nav class="right">
			<ul>
				<?php if (!empty($_SESSION['user_id'])) : ?>
				<li>
					<a href="account.php">
						Bonjour, <?= $_SESSION['user_username'] ?> !
					</a>
				</li>
				<li>
					<a href="cart.php" class="cart-link" title="Panier">
						Panier
					</a>
				</li>
				<li>
					<a href="logout.php">
						Logout
					</a>
				</li>
				<?php else : ?>
				<li>
					<a href="register.php">Inscription</a>
				</li>
				<li>
					<a href="cart.php" class="cart-link" title="Panier">
						Panier
					</a>
				</li>
				<?php endif; ?>
			</ul>
		</nav>
		<?php if (empty($_SESSION['user_id'])) : ?>
		<form action="auth.php" method="POST" class="login">
			<p>
				<input type="text" name="username" placeholder="Nom d'utilisateur">
				<input type="password" name="password" placeholder="Mot de passe">
			</p>
			<p class="submit">
				<input type="submit" name="submit" value="Connexion">
			</p>
		</form>
		<?php endif; ?>
	</header>
	<div class="container">
		<div class="content">
