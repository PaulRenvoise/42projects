<?php

$page_title = 'Passer commande';

require('includes/header.php');

function get_total($articles)
{
	$total = array(
		'ht'		=> 0,
		'count'		=> 0
	);
	foreach ($articles as $key => $value) {
		$total['count'] += $value['quantity'];
		$total['ht'] += ($value['price'] * $value['quantity']);
	}
	$total['ht'] += 6;
	$total['tva'] = round((($total['ht'] / 100) * 19.6), 2);
	$total['ttc'] = ($total['ht'] + $total['tva']);
	return $total;
}

function get_cart($db)
{
	$cart = $_SESSION['cart'];
	$articles = array();
	if (count($cart) > 0)
	{
		$entries = '';
		foreach ($cart as $key => $value) {
			$entries .= "`articles`.`id` = '" . $key . "' OR ";
		}
		$entries = substr($entries, 0, -4);
		$query = mysqli_query($db, "SELECT `articles`.`id`, `articles`.`name`, `articles`.`price` FROM `articles` WHERE " . $entries);
		while ($result = mysqli_fetch_assoc($query))
		{
			$articles[] = array(
				'id'		=> $result['id'],
				'name'		=> $result['name'],
				'price'		=> $result['price'],
				'quantity'	=> $cart[$result['id']]
			);
		}
	}
	return $articles;
}

function get_values($checkout_id, $articles)
{
	$values		= '';
	foreach ($articles as $key => $value) {
		$values .= "('$checkout_id', '" . $value['id'] . "', '" . $value['price'] . "', '" . $value['quantity'] . "'), ";
	}
	$values = substr($values, 0, -2);
	return $values;
}

if (!empty($_SESSION['user_id']))
{
	$success	= '';
	$articles	= get_cart($db);
	if (count($articles) > 0)
		$total		= get_total($articles);
	else
		$error = 'Votre panier est vide.';
	if (!empty($_POST['submit']) && $_POST['submit'] == 'Passer commande')
	{
		$user_id			= $_SESSION['user_id'];
		$ref				= uniqid();
		$handling_charge	= 6;
		$ht					= $total['ht'];
		$tva				= $total['tva'];
		$ttc				= $total['ttc'];
		$last_name			= htmlspecialchars(addslashes($_POST['last_name']));
		$name				= htmlspecialchars(addslashes($_POST['name']));
		$address			= htmlspecialchars(addslashes($_POST['address']));
		$postal_code		= htmlspecialchars(addslashes($_POST['postal_code']));
		$city				= htmlspecialchars(addslashes($_POST['city']));
		$phone				= htmlspecialchars(addslashes($_POST['phone']));
		if (!empty($last_name) && !empty($name) && !empty($address) && !empty($postal_code) && !empty($city) && !empty($phone))
		{
			if (preg_match('/[0-9]{5}/', $postal_code))
			{
				if (preg_match('/[0-9]{10}/', $phone))
				{
					$statement	= "INSERT INTO `checkouts` (`user_id`, `ref`, `handling_charge`, `ht`, `tva`, `ttc`, `last_name`, `name`, `address`, `postal_code`, `city`, `phone`)
						VALUE ('$user_id', '$ref', '$handling_charge', '$ht', '$tva', '$ttc', '$last_name', '$name', '$address', '$postal_code', '$city', '$phone')";
					$query		= mysqli_query($db, $statement);
					if (mysqli_affected_rows($db) > 0)
					{
						$checkout_id	= mysqli_insert_id($db);
						$values			= get_values($checkout_id, $articles);
						$statement		= "INSERT INTO `checkouts_articles` (`checkout_id`, `article_id`, `price`, `quantity`)
							VALUES " . $values;
						$query			= mysqli_query($db, $statement);
						if (mysqli_affected_rows($db) > 0)
						{
							$_SESSION['cart']	= array();
							$success			= 'Votre commande a bien été validée. Vous pouvez la retrouver dans votre <a href="account.php">panneau utilisateur</a>.';
						}
						else
							$error = 'Une erreur s\'est produite lors de la validation de la commande.';
					}
					else
						$error = 'Une erreur s\'est produite lors de la validation de la commande.';
				}
				else
					$error = 'Votre numéro de téléphone n\'est pas valide.';
			}
			else
				$error = 'Votre code postal n\'est pas valide.';
		}
		else
			$error = 'Tous les champs ne sont pas remplis.';
	}
}
else
{
	$error = 'Vous devez ėtre connecté pour pouvoir passer commande.<br>
		<a href="auth.php">Connectez-vous</a> ou <a href="register.php">créez un compte</a><br>
		Votre panier sera conservé.';
}

?>
<h1>Passer commande <span>Livraison estimée à hier</span></h1>
<?php if (!empty($error) && !isset($_POST['submit'])): ?>
<p class="error">
	<?= $error ?>
</p>
<?php elseif(!empty($success)): ?>
<p class="success">
	<?= $success ?>
</p>
<?php endif ?>
<?php if(isset($articles) && isset($total) && empty($success)): ?>
<p>
	Voici un récapitulatif de votre commande.
</p>
<?php $i = 1; ?>
<table class="articles">
	<thead>
		<tr>
			<th>&nbsp;</th>
			<th>Nom</th>
			<th>Prix</th>
			<th>Quantité</th>
		</tr>
	</thead>
	<tbody>
	<?php foreach ($articles as $key => $article): ?>
		<tr>
			<td class="nb"><?= $i ?>.</td>
			<td>
				<a href="view_article.php?id=<?= $article['id'] ?>"><?= $article['name'] ?></a>
			</td>
			<td>
				<?= $article['price'] ?> €
			</td>
			<td>
				<?= $article['quantity'] ?>
			</td>
		</tr>
		<?php $i++ ?>
	<?php endforeach ?>
	</tbody>
</table>
<h2>Total</h2>
<p class="right total">
	Frais de port : <span>6 €</span><br><br>

	Base HT : <span><?= $total['ht'] ?> €</span><br>
	TVA 19,6% : <span><?= $total['tva'] ?> €</span><br>
	Total TTC : <span><?= $total['ttc'] ?> €</span>
</p>
<h2>Finaliser la commande</h2>
<?php if (!empty($error) && !empty($_POST['submit'])): ?>
<p class="error">
	<?= $error ?>
</p>
<?php endif ?>
<form action="" method="POST">
	<p>
		<label for="last_name">Nom :</label>
		<input type="text" name="last_name" id="last_name" size="40" placeholder="Douglas" value="<?= !empty($last_name) ? $last_name : '' ?>">
	</p>
	<p>
		<label for="name">Prénom :</label>
		<input type="text" name="name" id="name" size="40" placeholder="Adams" value="<?= !empty($name) ? $name : '' ?>">
	</p>
	<p>
		<label for="address">Adresse :</label>
		<input type="text" name="address" id="address" size="40" placeholder="42, Allée Edward Snowden" value="<?= !empty($address) ? $address : '' ?>">
	</p>
	<p>
		<label for="postal_code">Code postal :</label>
		<input type="text" name="postal_code" id="postal_code" size="5" placeholder="42000" value="<?= !empty($postal_code) ? $postal_code : '' ?>">
	</p>
	<p>
		<label for="city">Ville :</label>
		<input type="text" name="city" id="city" size="40" placeholder="Forty-Two" value="<?= !empty($city) ? $city : '' ?>">
	</p>
	<p>
		<label for="phone">Numéro de téléphone :</label>
		<input type="text" name="phone" id="phone" size="11" placeholder="0613374269" value="<?= !empty($phone) ? $phone : '' ?>">
	</p>
	<p>
		<input type="submit" name="submit" value="Passer commande">
		<a href="cart.php">Annuler la commande</a>
	</p>
</form>
<?php endif ?>
<?php

require('includes/footer.php');

?>