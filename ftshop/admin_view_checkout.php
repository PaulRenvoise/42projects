<?php

$page_title = 'Voir une commande';

require('includes/header.php');

function fetch_checkout($db, $id)
{
	$statement	= "SELECT `checkouts`.*, `checkouts_articles`.`id` AS `article_id`, `checkouts_articles`.`price` AS `article_price`, `checkouts_articles`.`quantity` AS `article_quantity`, `articles`.`name` AS `article_name`, `users`.`username` AS `user_name` FROM `checkouts`
		LEFT JOIN `checkouts_articles` ON `checkouts_articles`.`checkout_id` = `checkouts`.`id`
		LEFT JOIN `articles` ON `articles`.`id` = `checkouts_articles`.`article_id`
		LEFT JOIN `users` ON `users`.`id` = `checkouts`.`user_id`
		WHERE `checkouts`.`id` = '$id'";
	$query					= mysqli_query($db, $statement);
	$checkout				= array();
	$checkout['articles']	= array();
	if ($query)
	{
		while ($result = mysqli_fetch_assoc($query))
		{
			if (!isset($checkout['id']))
			{
				$checkout['id']					= $result['id'];
				$checkout['user_id']			= $result['user_id'];
				$checkout['user_name']			= $result['user_name'];
				$checkout['ref']				= $result['ref'];
				$checkout['handling_charge']	= $result['handling_charge'];
				$checkout['ht']					= $result['ht'];
				$checkout['tva']				= $result['tva'];
				$checkout['ttc']				= $result['ttc'];
				$checkout['last_name']			= $result['last_name'];
				$checkout['name']				= $result['name'];
				$checkout['address']			= $result['address'];
				$checkout['postal_code']		= $result['postal_code'];
				$checkout['city']				= $result['city'];
				$checkout['phone']				= $result['phone'];
				$checkout['timestamp']			= strftime("%A %d %B à %H:%M", strtotime($result['timestamp']));
				$checkout['done']				= $result['done'];
			}
			$checkout['articles'][] = array(
				'article_id'		=> $result['article_id'],
				'article_price'		=> $result['article_price'],
				'article_quantity'	=> $result['article_quantity'],
				'article_name'		=> $result['article_name']
			);
		}
	}
	return $checkout;
}

if (!empty($_SESSION['user_id']) && $_SESSION['user_level'] >= 4 && is_numeric($_GET['id']))
{
	$error				= '';
	$id					= intval($_GET['id']);
	$checkout			= fetch_checkout($db, $id);
	$checkout['status']	= '';
	if (count($checkout['articles']) > 0)
	{
		if ($checkout['user_id'] !== $_SESSION['user_id'])
			$error = 'Cette commande ne vous appartient pas.';
		if ($checkout['done'] == '0')
			$checkout['status'] = 'En cours';
		else if ($checkout['done'] == '1')
			$checkout['status'] = 'Passée';
		else if ($checkout['done'] == '-1')
			$checkout['status'] = 'Annulée';
	}
	else
		$error = 'Cette commande m\'existe pas.';
}

?>
<h1>
	Voir une commande <span><?= isset($checkout['ref']) ? $checkout['ref'] : '' ?><?= !empty($checkout['status']) ? ' - ' . $checkout['status'] : '' ?></span>
</h1>
<?php if (empty($_SESSION['user_id']) || $_SESSION['user_level'] < 4) : ?>
<p class="error">
	Cette page n'est accessible qu'aux administrateurs.
</p>
<?php endif ?>
<?php if (!empty($error)): ?>
<p class="error">
	<?= $error ?>
</p>
<?php endif ?>
<?php if (isset($error) && empty($error)): ?>
<p>
	Voici les informations concernant la commande <?= $checkout['ref'] ?> du <?= $checkout['timestamp'] ?>.
</p>
<h2>Informations sur la commande</h2>
<p class="checkout_infos">
	<span>Référence : </span><?= $checkout['ref'] ?><br>
	<span>Statut : </span><?= $checkout['status'] ?><br>
	<span>Utilisateur : </span><?= $checkout['user_name'] ?><br><br>
	<span>Frais de port : </span><?= $checkout['handling_charge'] ?> €<br>
	<span>Base HT : </span><?= $checkout['ht'] ?> €<br>
	<span>TVA : </span><?= $checkout['tva'] ?> €<br>
	<span>Total TTC : </span><?= $checkout['ttc'] ?> €<br><br>
	<span>Nom : </span><?= $checkout['last_name'] ?> <br>
	<span>Prénom : </span><?= $checkout['name'] ?> <br>
	<span>Adresse : </span><?= $checkout['address'] ?> <br>
	<span>Code postal : </span><?= $checkout['postal_code'] ?> <br>
	<span>Ville : </span><?= $checkout['city'] ?> <br>
	<span>Téléphone : </span><?= $checkout['phone'] ?> <br><br>
	<span>Date : </span><?= $checkout['timestamp'] ?> <br>
</p>
<h2>Contenu du colis</h2>
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
	<?php foreach ($checkout['articles'] as $key => $article): ?>
		<tr>
			<td class="nb"><?= $i ?>.</td>
			<td>
				<a href="view_article.php?id=<?= $article['article_id'] ?>"><?= $article['article_name'] ?></a>
			</td>
			<td>
				<?= $article['article_price'] ?> €
			</td>
			<td>
				<?= $article['article_quantity'] ?>
			</td>
		</tr>
		<?php $i++ ?>
	<?php endforeach ?>
	</tbody>
</table>
<p class="right">
	<a href="admin_checkouts.php">Retour aux commandes</a>
</p>
<?php endif ?>
<?php

require('includes/footer.php');

?>
