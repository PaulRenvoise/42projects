<?php

$page_title = 'Gérer les commandes';

require('includes/header.php');

function fetch_checkouts($db)
{
	$user_id	= $_SESSION['user_id'];
	$statement	= "SELECT `checkouts`.`id`, `checkouts`.`ref`, `checkouts`.`ttc`, `checkouts`.`timestamp`, `checkouts`.`done`, `checkouts_articles`.`id` AS `article_id`, `users`.`username` AS `user_name` FROM `checkouts`
		LEFT JOIN `checkouts_articles` ON `checkouts_articles`.`checkout_id` = `checkouts`.`id`
		LEFT JOIN `users` ON `users`.`id` = `checkouts`.`user_id`";
	$query					= mysqli_query($db, $statement);
	$checkouts				= array();
	$checkouts['done']		= array();
	$checkouts['pending']	= array();
	$checkouts['canceled']	= array();
	if ($query)
	{
		while ($result = mysqli_fetch_assoc($query))
		{
			if ($result['done'] == '1')
				$array = &$checkouts['done'];
			elseif ($result['done'] == '0')
				$array = &$checkouts['pending'];
			elseif ($result['done'] == '-1' || $result['done'] == '-2')
				$array = &$checkouts['canceled'];
			if (!array_key_exists($result['id'], $array))
			{
				$array[$result['id']] = array();
				$array[$result['id']]['user_name']	= $result['user_name'];
				$array[$result['id']]['ref']		= $result['ref'];
				$array[$result['id']]['ttc']		= $result['ttc'];
				$array[$result['id']]['timestamp']	= strftime("%A %d %B à %H:%M", strtotime($result['timestamp']));
				if ($result['done'] == '1')
					$array[$result['id']]['status']	= 'Passée';
				else if ($result['done'] == '0')
					$array[$result['id']]['status']	= 'En cours';
				else if ($result['done'] == '-1')
					$array[$result['id']]['status']	= 'Annulée par l\'utilisateur';
				else
					$array[$result['id']]['status']	= 'Annulée par l\'administrateur';
			}
			else
			{
				if (!isset($array[$result['id']]['articles_count']))
					$array[$result['id']]['articles_count'] = 1;
				else
					$array[$result['id']]['articles_count']++;
			}
		}
	}
	return $checkouts;
}

if (!empty($_SESSION['user_id']) && $_SESSION['user_level'] >= 4 && !empty($_GET['del']))
{
	$del_id	= intval(htmlspecialchars(addslashes($_GET['del'])));
	$query	= mysqli_query($db, "UPDATE `checkouts` SET `done` = '-2' WHERE `id` = '$del_id' AND `done` = '0'");
	if ($query && mysqli_affected_rows($db) > 0)
		$success = 'La commande a bien été annulée.';
	else
		$error = 'Erreur lors de l\'annulation de la commande.';
}
else if (!empty($_SESSION['user_id']) && $_SESSION['user_level'] >= 4 && !empty($_GET['recover']))
{
	$recover_id	= intval(htmlspecialchars(addslashes($_GET['recover'])));
	$query		= mysqli_query($db, "UPDATE `checkouts` SET `done` = '0' WHERE `id` = '$recover_id' AND `done` != '0'");
	if ($query && mysqli_affected_rows($db) > 0)
		$success = 'La commande a bien été remise en file d\'attente.';
	else
		$error = 'Erreur lors de la remise en file d\'attente de la commande.';
}
else if (!empty($_SESSION['user_id']) && $_SESSION['user_level'] >= 4 && !empty($_GET['validate']))
{
	$validate_id	= intval(htmlspecialchars(addslashes($_GET['validate'])));
	$query			= mysqli_query($db, "UPDATE `checkouts` SET `done` = '1' WHERE `id` = '$validate_id' AND `done` != '1'");
	if ($query && mysqli_affected_rows($db) > 0)
		$success = 'La commande a bien été validée.';
	else
		$error = 'Erreur lors de la validation de la commande.';
}

if (!empty($_SESSION['user_id']) && $_SESSION['user_level'] >= 4)
{
	$checkouts = fetch_checkouts($db);
}

?>
<h1>
	Gérer les commandes <span>All your checkouts are belong to us</span>
</h1>
<?php if (empty($_SESSION['user_id']) || $_SESSION['user_level'] < 4) : ?>
<p class="error">
	Cette page n'est accessible qu'aux administrateurs.
</p>
<?php else : ?>
<p>
	Vous pouvez gérer les commandes depuis cette page.
</p>
<?php if (!empty($error)): ?>
<p class="error">
	<?= $error ?>
</p>
<?php elseif(!empty($success)) : ?>
<p class="success">
	<?= $success ?>
</p>
<?php endif ?>
<h2>Les commandes en cours</h2>
<?php if (count($checkouts['pending']) > 0): ?>
<?php $i = 1; ?>
<table class="articles">
	<thead>
		<tr>
			<th>&nbsp;</th>
			<th>Utilisateur</th>
			<th>Référence</th>
			<th>Nbre d'articles</th>
			<th>Date</th>
			<th>Statut</th>
			<th>Actions</th>
		</tr>
	</thead>
	<tbody>
	<?php foreach ($checkouts['pending'] as $key => $checkout): ?>
		<tr>
			<td class="nb"><?= $i ?>.</td>
			<td>
				<?= $checkout['user_name'] ?>
			</td>
			<td>
				<a href="admin_view_checkout.php?id=<?= $key ?>"><?= $checkout['ref'] ?></a>
			</td>
			<td>
				<?= $checkout['articles_count'] ?> <?= $checkout['articles_count'] <= 1 ? 'article' : 'articles' ?>
			</td>
			<td>
				<?= $checkout['timestamp'] ?>
			</td>
			<td>
				<?= $checkout['status'] ?>
			</td>
			<td>
				<a href="?validate=<?= $key ?>" title="Valider la commande <?= $checkout['ref'] ?>">Valider</a> -
				<a href="?del=<?= $key ?>" title="Annuler la commande <?= $checkout['ref'] ?>">Annuler</a>
			</td>
		</tr>
		<?php $i++ ?>
	<?php endforeach ?>
	</tbody>
</table>
<?php else: ?>
<p class="error">
	Aucune commande en cours.
</p>
<?php endif ?>
<h2>Les commandes passées</h2>
<?php if (count($checkouts['done']) > 0): ?>
<?php $i = 1; ?>
<table class="articles">
	<thead>
		<tr>
			<th>&nbsp;</th>
			<th>Utilisateur</th>
			<th>Référence</th>
			<th>Nbre d'articles</th>
			<th>Date</th>
			<th>Statut</th>
			<th>Actions</th>
		</tr>
	</thead>
	<tbody>
	<?php foreach ($checkouts['done'] as $key => $checkout): ?>
		<tr>
			<td class="nb"><?= $i ?>.</td>
			<td>
				<?= $checkout['user_name'] ?>
			</td>
			<td>
				<a href="admin_view_checkout.php?id=<?= $key ?>"><?= $checkout['ref'] ?></a>
			</td>
			<td>
				<?= $checkout['articles_count'] ?> <?= $checkout['articles_count'] <= 1 ? 'article' : 'articles' ?>
			</td>
			<td>
				<?= $checkout['timestamp'] ?>
			</td>
			<td>
				<?= $checkout['status'] ?>
			</td>
			<td>
				<a href="?recover=<?= $key ?>" title="Remettre la commande <?= $checkout['ref'] ?> dans la file d'attente">Remettre en file d'attente</a>
			</td>
		</tr>
		<?php $i++ ?>
	<?php endforeach ?>
	</tbody>
</table>
<?php else: ?>
<p class="error">
	Aucune commande passée.
</p>
<?php endif ?>
<h2>Les commandes annulées</h2>
<?php if (count($checkouts['canceled']) > 0): ?>
<?php $i = 1; ?>
<table class="articles">
	<thead>
		<tr>
			<th>&nbsp;</th>
			<th>Utilisateur</th>
			<th>Référence</th>
			<th>Nbre d'articles</th>
			<th>Date</th>
			<th>Statut</th>
			<th>Actions</th>
		</tr>
	</thead>
	<tbody>
	<?php foreach ($checkouts['canceled'] as $key => $checkout): ?>
		<tr>
			<td class="nb"><?= $i ?>.</td>
			<td>
				<?= $checkout['user_name'] ?>
			</td>
			<td>
				<a href="admin_view_checkout.php?id=<?= $key ?>"><?= $checkout['ref'] ?></a>
			</td>
			<td>
				<?= $checkout['articles_count'] ?> <?= $checkout['articles_count'] <= 1 ? 'article' : 'articles' ?>
			</td>
			<td>
				<?= $checkout['timestamp'] ?>
			</td>
			<td>
				<?= $checkout['status'] ?>
			</td>
			<td>
				<a href="?recover=<?= $key ?>" title="Remettre la commande <?= $checkout['ref'] ?> dans la file d'attente">Remettre en file d'attente</a>
			</td>
		</tr>
		<?php $i++ ?>
	<?php endforeach ?>
	</tbody>
</table>
<?php else: ?>
<p class="error">
	Aucune commande annulée.
</p>
<?php endif ?>
<?php
endif;

require('includes/footer.php');

?>
