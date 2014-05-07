<?php

$page_title = "Ajouter un article";

require('includes/header.php');

$categories = array();
if (($query = mysqli_query($db, "SELECT * FROM `categories`")) != FALSE)
{
	while ($result = mysqli_fetch_assoc($query))
		$categories[] = $result;
}

if (!empty($categories))
{
	$error = "";
	if (!empty($_POST) && $_POST['submit'] == "Ajouter l'article")
	{
		if (!empty($_POST['name']))
		{
			$name = htmlspecialchars(addslashes($_POST['name']));
			if (!empty($_POST['image']))
			{
				$image = htmlspecialchars(addslashes($_POST['image']));
				if (!empty($_POST['price']))
				{
					$price = htmlspecialchars(addslashes($_POST['price']));
					if (!empty($_POST['description']))
					{
						$description = htmlspecialchars(addslashes($_POST['description']));
						if (!empty($_POST['categories']))
						{
							if (($query = mysqli_query($db, "INSERT INTO `articles` (`name`, `image`, `price`, `description`) VALUES ('$name', '$image', '$price', '$description')")) == FALSE)
								$error = "Erreur lors de l'ajout de l'article.";
							else
								$id_article = mysqli_insert_id($db);
							foreach ($_POST['categories'] as $id_category)
							{
								if (($query = mysqli_query($db, "INSERT INTO `articles_categories` (`article_id`, `category_id`) VALUES ('$id_article', '$id_category')")) == FALSE)
									$error = "Erreur lors de l'ajout de l'article.";
							}
						}
						else
							$error = "Champ 'Categorie(s)' vide.";
					}
					else
						$error = "Champ 'Description de l'article' vide.";
				}
				else
					$error = "Champ 'Prix de l'article' vide.";
			}
			else
				$error = "Champ 'Image de l'article' vide.";
		}
		else
			$error = "Champ 'Nom de l'article' vide.";
	}
}
else
	$error = "Veuillez creer une categorie avant d'y ajouter un article.";

?>

<h1>Ajout d'articles</h1>

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
	<?php elseif ($error == NULL && !empty($_POST)) : ?>
	<p class="success">
		Article ajoute !
	</p>
	<?php endif ; ?>
	<?php if ($error != "Veuillez creer une categorie avant d'y ajouter un article.") : ?>
	<form action="" method="POST">
		<p>
			<label for="name">Nom de l'article :</label>
			<input type="text" name="name" id="name" size="40">
		</p>
		<p>
			<label for="image">URL de l'image de l'article :</label>
			<input type="text" name="image" id="image" size="40">
		</p>
		<p>
			<label for="price">Prix de l'article :</label>
			<input type="number" name="price" id="price" min="0.0">
		</p>
		<p>
			<label for="description" >Description de l'article :</label>
			<textarea cols="70" rows="12" name="description" id="description"></textarea>
		</p>
		<p>
			<label for="categories" >Categorie(s) :</label>
			<select name="categories[]" id="categories" multiple>
			<?php foreach ($categories as $value): ?>
			<option value="<?= $value['id'] ?>"><?= $value['name'] ?></option>
			<?php endforeach ?>
			</select>
		</p>
		<p>
			<input type="submit" name="submit" value="Ajouter l'article">
			<a href="admin.php">Retour à l'administration</a>
		</p>
	</form>
	<?php endif; ?>
<?php endif; ?>

<?php

require('includes/footer.php');

?>
