<?php

$page_title = "Modifier un article";

require('includes/header.php');

?>

<?php

function	is_in_category($db, $category_id)
{
	$id = $_SESSION['mod_art_id'];

	if (($query = mysqli_query($db, "SELECT `category_id` FROM `articles_categories` WHERE `article_id` = '$id' AND `category_id` = '$category_id'")) != FALSE)
	{
		$result = mysqli_fetch_assoc($query);
		if (count($result) == 0)
			return (0);
		else
			return ($result['category_id']);
	}
}

function	is_selected($category, $categories_select)
{
	foreach($categories_select as $elem)
	{
		if ($category == $elem)
			return (1);
	}
	return (0);
}

$categories = array();
if (($query = mysqli_query($db, "SELECT * FROM `categories`")) != FALSE)
{
	while ($result = mysqli_fetch_assoc($query))
		$categories[] = $result;
}

if (!empty($_POST) && $_POST['submit'] == "Acceder au panel de modification")
{
	if (!empty($_POST['id']) && !empty($_POST['name']))
	{
		$id = htmlspecialchars(addslashes($_POST['id']));
		$name = htmlspecialchars(addslashes($_POST['name']));
		$error = "";

		if (($query = mysqli_query($db, "SELECT `id`, `name` FROM `articles` WHERE `id` = '$id' AND `name` = '$name'")) == FALSE)
			$error = "Erreur lors de la modification d'article.";
		else
		{
			$result = mysqli_fetch_assoc($query);
			if (count($result) == 0)
				$error = "Coupe id/nom de l'article errone.";
			else
			{
				$_SESSION['mod_art_id'] = $result['id'];
				$_SESSION['mod_art_name'] = $result['name'];
			}
		}
	}
	else if (!empty($_POST['id']))
	{
		$id = htmlspecialchars(addslashes($_POST['id']));
		$error = "";

		if (($query = mysqli_query($db, "SELECT `id`, `name` FROM `articles` WHERE `id` = '$id'")) == FALSE)
			$error = "Erreur lors de la modification d'article.1";
		else
		{
			$result = mysqli_fetch_assoc($query);
			if (count($result) == 0)
				$error = "Cet article n'existe pas.";
			else
			{
				$_SESSION['mod_art_id'] = $result['id'];
				$_SESSION['mod_art_name'] = $result['name'];
			}
		}
	}
	else if (!empty($_POST['name']))
	{
		$name = htmlspecialchars(addslashes($_POST['name']));
		$error = "";

		if (($query = mysqli_query($db, "SELECT `id`, `name` FROM `articles` WHERE `name` = '$name'")) == FALSE)
			$error = "Erreur lors de la modification d'article.";
		else
		{
			$result = mysqli_fetch_assoc($query);
			if (count($result) == 0)
				$error = "Cet article n'existe pas.";
			else
			{
				$_SESSION['mod_art_id'] = $result['id'];
				$_SESSION['mod_art_name'] = $result['name'];
			}
		}
	}
	else
		$error = "Veuillez renseigner au moins un des deux champs.";
}
if (!empty($_POST) && $_POST['submit'] == "Modifier l'article")
{
	$error = "";
	$id = $_SESSION['mod_art_id'];

	if ($_POST['name'])
	{
		$name = htmlspecialchars(addslashes($_POST['name']));

		mysqli_query($db, "UPDATE `articles` SET `name` = '$name' WHERE `id` = '$id'");
		if (mysqli_affected_rows($db) == 0)
			$error = "Erreur lors de la mise à jour de l'article.";
		else
		{
			$_SESSION['mod_art_name'] = $name;
		}
	}
	if ($_POST['image'])
	{
		$image = htmlspecialchars(addslashes($_POST['image']));

		mysqli_query($db, "UPDATE `articles` SET `image` = '$image' WHERE `id` = '$id'");
		if (mysqli_affected_rows($db) == 0)
			$error = "Erreur lors de la mise à jour de l'article.";
	}
	if (is_numeric($_POST['price']))
	{
		$price = htmlspecialchars(addslashes($_POST['price']));

		mysqli_query($db, "UPDATE `articles` SET `price` = '$price' WHERE `id` = '$id'");
		if (mysqli_affected_rows($db) == 0)
			$error = "Erreur lors de la mise à jour de l'article.";
	}
	if ($_POST['description'])
	{
		$description = htmlspecialchars(addslashes($_POST['description']));

		mysqli_query($db, "UPDATE `articles` SET `description` = '$description' WHERE `id` = '$id'");
		if (mysqli_affected_rows($db) == 0)
			$error = "Erreur lors de la mise à jour de l'article.";
	}
	if (isset($_POST['categories']))
	{
		foreach ($_POST['categories'] as $id_category)
		{
			if ($id_category != is_in_category($db, $id_category))
			{
				if (($query = mysqli_query($db, "INSERT INTO `articles_categories` (`article_id`, `category_id`) VALUES ('$id', '$id_category')")) == FALSE)
					$error = "Erreur lors de la modification de l'article.";
			}
			$categories_select[] = $id_category;
		}
		foreach ($categories as $value)
		{
			$sub_val = $value['id'];
			if (!is_selected($sub_val, $categories_select))
			{
				if (($query = mysqli_query($db, "SELECT * FROM `articles_categories` WHERE `article_id` = '$id' AND `category_id` = '$sub_val'")) != FALSE)
				{
					$result = mysqli_fetch_assoc($query);
					if (count($result) != 0)
					{
						if (($query = mysqli_query($db, "DELETE FROM `articles_categories` WHERE `article_id` = '$id' AND `category_id` = '$sub_val'")) == FALSE)
							$error = "Erreur lors de la modification de l'article.";
					}
				}
			}
		}
	}
}


?>
<h1>Modification d'article<?= isset($_SESSION['mod_art_name']) ? ' <span>' . $_SESSION['mod_art_name'] . '</span>' : '' ?></h1>

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
	<?php elseif (isset($error) && $_POST['submit'] == "Modifier l'article") : ?>
	<p class="success">
		Article modifie !
	</p>
	<?php endif ; ?>
	<?php if (!empty($_SESSION['mod_art_id'])): ?>
	<p class="tip">
		Laissez les champs vides pour ne pas modifier la base de donnee.
	</p>
	<form action="" method="POST">
		<p>
			<label for="name">Nouveau nom de l'article :</label>
			<input type="text" name="name" id="name" size="40">
		</p>
		<p>
			<label for="image">Nouvelle URL de l'image :</label>
			<input type="text" name="image" id="image" size="40">
		</p>
		<p>
			<label for="price">Nouveau prix de l'article :</label>
			<input type="number" name="price" id="price" min="0.0">
		</p>
		<p>
			<label for="description" >Nouvelle description de l'article :</label>
			<textarea cols="70" rows="12" name="description" id="description"></textarea>
		</p>
		<p>
			<label for="categories" >Nouvelle(s) categorie(s) :</label>
			<select name="categories[]" id="categories" multiple>
			<?php foreach ($categories as $value): ?>
			<option value="<?= $value['id'] ?>" <?= (is_in_category($db, $value['id']) == 0) ? "" : "selected" ?>><?= $value['name'] ?></option>
			<?php endforeach ?>
			</select>
		</p>
		<p>
			<input type="submit" name="submit" value="Modifier l'article">
			<a href="admin.php">Retour à l'administration</a>
		</p>
	</form>
	<?php else: ?>
	<p class="tip">
		Vous pouvez ne renseigner qu'un des deux champs entre l'id et le nom de l'article.
	</p>
	<form action="" method="POST">
		<p>
			<label for="id">Id de l'article :</label>
			<input type="number" min="1" name="id" id="id">
		</p>
		<p>
			<label for="name">Nom de l'article :</label>
			<input type="text" name="name" id="name" size="40">
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
