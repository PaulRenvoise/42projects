<?php

$page_title = "Supprimer un article";

require('includes/header.php');

if (!empty($_POST) && $_POST['submit'] == "Supprimer l'article")
{
	$error = "";
	if (!empty($_POST['id']) && !empty($_POST['name']))
	{
		$id = htmlspecialchars(addslashes($_POST['id']));
		$name = htmlspecialchars(addslashes($_POST['name']));

		if (($query = mysqli_query($db, "SELECT * FROM `articles` WHERE `id` = '$id' AND `name` = '$name'")) == FALSE)
			$error = "Erreur lors de la suppression de l'article.";
		else
		{
			if (mysqli_affected_rows($db) > 0)
			{
				if (($query = mysqli_query($db, "DELETE FROM `articles` WHERE `id` = '$id'")) == FALSE)
					$error = "Erreur lors de la suppression de l'article.";
				else
				{
					if (mysqli_affected_rows($db) > 0)
					{
						if (($query = mysqli_query($db, "DELETE FROM `articles_categories` WHERE `article_id` = '$id'")) == FALSE)
							$error = "Erreur lors de la suppression de l'article";
					}
					else
						$error = "Cet article n'existe pas.";
				}
			}
			else
				$error = "Couple id/nom de l'article errone.";
		}
	}
	else if (!empty($_POST['id']))
	{
		$id = htmlspecialchars(addslashes($_POST['id']));

		if (($query = mysqli_query($db, "DELETE FROM `articles` WHERE `id` = '$id'")) == FALSE)
			$error = "Erreur lors de la suppression de l'article.";
		else
		{
			if (mysqli_affected_rows($db) > 0)
			{
				if (($query = mysqli_query($db, "DELETE FROM `articles_categories` WHERE `article_id` = '$id'")) == FALSE)
					$error = "Erreur lors de la suppression de l'article";
			}
			else
				$error = "Cet article n'existe pas.";
		}
	}
	else if (!empty($_POST['name']))
	{
		$name = htmlspecialchars(addslashes($_POST['name']));

		if (($query = mysqli_query($db, "SELECT `id` FROM `articles` WHERE `name` = '$name'")) == FALSE)
			$error = "Erreur lors de la suppresion de l'article.";
		else
		{
			if (mysqli_affected_rows($db) != 0)
			{
				$result = mysqli_fetch_assoc($query);
				$id_article = $result['id'];
				if (($query = mysqli_query($db, "DELETE FROM `articles` WHERE `name` = '$name'")) == FALSE)
					$error = "Erreur lors de la suppression de l'article";
				else
				{
					if (($query = mysqli_query($db, "DELETE FROM `articles_categories` WHERE `article_id` = '$id_article'")) == FALSE)
						$error = "Erreur lors de la suppression de l'article";
				}
			}
			else
				$error = "Cet article n'existe pas.";
		}
	}
	else
		$error = "Veuillez renseigner au moins un des deux champs.";
}

?>

<h1>Suppression d'articles</h1>

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
		Article supprime !
	</p>
	<?php endif ; ?>
<p class="tip">
	Vous pouvez ne renseigner qu'un des deux champs.
</p>
<form action="" method="POST">
	<p>
		<label for="id">Id de l'article :</label>
		<input type="number" name="id" id="id" min="1">
	</p>
	<p>
		<label for="name">Nom de l'article :</label>
		<input type="text" name="name" id="name" size="40">
	</p>
	<p>
		<input type="submit" name="submit" value="Supprimer l'article">
		<a href="admin.php">Retour à l'administration</a>
	</p>
</form>
<?php endif; ?>

<?php

require('includes/footer.php');

?>
