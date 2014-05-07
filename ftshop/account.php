<?php

$page_title = 'Mon compte';

require('includes/header.php');

function fetch_checkouts($db)
{
	$user_id	= $_SESSION['user_id'];
	$statement	= "SELECT `checkouts`.`id`, `checkouts`.`ref`, `checkouts`.`ttc`, `checkouts`.`timestamp`, `checkouts`.`done`, `checkouts_articles`.`id` AS `article_id` FROM `checkouts`
		LEFT JOIN `checkouts_articles` ON `checkouts_articles`.`checkout_id` = `checkouts`.`id`
		WHERE `checkouts`.`user_id` = '$user_id'";
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

if (!empty($_SESSION['user_id']) && isset($_POST['delete']))
{
	$error = '';
	$success = '';
	$query = mysqli_query($db, "DELETE FROM `users` WHERE `id` = '" . $_SESSION['user_id'] . "'");
	if (mysqli_affected_rows($db) > 0)
	{
		$_SESSION['user_id'] = 'deleted';
		$success = 'Votre compte a été supprimé avec succès. Rechargez la page pour être complètement déconnecté.';
	}
	else
		$error = 'Erreur lors de la suppression de votre compte.';
}
else if (!empty($_SESSION['user_id']) && isset($_POST['submit']) && $_POST['submit'] = 'Changer mon mot de passe')
{
	if (!empty($_POST['old_password']) && !empty($_POST['new_password']) && !empty($_POST['confirm_password']))
	{
		$old_password 		= hash('whirlpool', htmlspecialchars(addslashes($_POST['old_password'])));
		$new_password 		= hash('whirlpool', htmlspecialchars(addslashes($_POST['new_password'])));
		$confirm_password 	= hash('whirlpool', htmlspecialchars(addslashes($_POST['confirm_password'])));
		if ($new_password == $confirm_password)
		{
			$query 	= mysqli_query($db, "SELECT `password` FROM `users` WHERE `id` = '" . $_SESSION['user_id'] . "'");
			$result = mysqli_fetch_assoc($query);
			if ($result['password'] == $old_password)
			{
				$query = mysqli_query($db, "UPDATE `users` SET `password` = '$new_password' WHERE `id` = '" . $_SESSION['user_id'] . "'");
				if (mysqli_affected_rows($db) > 0)
				{
					$success = 'Votre mot de passe a bien été modifié.<br>Il prendra effet lors de votre prochaine connexion.';
				}
				else
					$error = 'Erreur lors du changement de votre mot de passe.';
			}
			else
				$error = 'Votre ancien mot de passe ne correspond pas.';
		}
		else
			$error = 'Les deux mots de passe ne correspondent pas.';

	}
	else
		$error = 'Tous les champs ne sont pas remplis';
}
else if (!empty($_SESSION['user_id']) && !empty($_GET['del']))
{
	$del_id	= intval(htmlspecialchars(addslashes($_GET['del'])));
	$query	= mysqli_query($db, "UPDATE `checkouts` SET `done` = '-1' WHERE `id` = '$del_id' AND `done` = '0'");
	if ($query && mysqli_affected_rows($db) > 0)
		$success = 'La commande a bien été annulée.';
	else
		$error = 'Erreur lors de l\'annulation de la commande.';
}

if (!empty($_SESSION['user_id']))
{
	$checkouts = fetch_checkouts($db);
}

?>
<h1>
	Panneau utilisateur <span><?= isset($_SESSION['user_username']) ? $_SESSION['user_username'] : '' ?></span>
</h1>
<?php if (empty($_SESSION['user_id'])) : ?>
<p class="error">
	Cette page n'est accessible qu'aux utilisateurs connectés.
</p>
<?php else : ?>
<p>
	Vous pouvez gérer votre compte depuis cette page.
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
<h2>Vos commandes en cours</h2>
<?php if (count($checkouts['pending']) > 0): ?>
<?php $i = 1; ?>
<table class="articles">
	<thead>
		<tr>
			<th>&nbsp;</th>
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
				<a href="view_checkout.php?id=<?= $key ?>"><?= $checkout['ref'] ?></a>
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
<h2>Vos commandes passées</h2>
<?php if (count($checkouts['done']) > 0): ?>
<?php $i = 1; ?>
<table class="articles">
	<thead>
		<tr>
			<th>&nbsp;</th>
			<th>Référence</th>
			<th>Nbre d'articles</th>
			<th>Date</th>
			<th>Statut</th>
		</tr>
	</thead>
	<tbody>
	<?php foreach ($checkouts['done'] as $key => $checkout): ?>
		<tr>
			<td class="nb"><?= $i ?>.</td>
			<td>
				<a href="view_checkout.php?id=<?= $key ?>"><?= $checkout['ref'] ?></a>
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
<h2>Vos commandes annulées</h2>
<?php if (count($checkouts['canceled']) > 0): ?>
<?php $i = 1; ?>
<table class="articles">
	<thead>
		<tr>
			<th>&nbsp;</th>
			<th>Référence</th>
			<th>Nbre d'articles</th>
			<th>Date</th>
			<th>Statut</th>
		</tr>
	</thead>
	<tbody>
	<?php foreach ($checkouts['canceled'] as $key => $checkout): ?>
		<tr>
			<td class="nb"><?= $i ?>.</td>
			<td>
				<a href="view_checkout.php?id=<?= $key ?>"><?= $checkout['ref'] ?></a>
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
<h2>Changement de mot de passe</h2>
<form action="" method="POST">
	<p>
		<label for="old_password">Ancien mot de passe :</label>
		<input type="password" name="old_password" id="old_password" size="40">
	</p>
	<p>
		<label for="new_password">Nouveau mot de passe :</label>
		<input type="password" name="new_password" id="new_password" size="40">
	</p>
	<p>
		<label for="confirm_password">Confirmez :</label>
		<input type="password" name="confirm_password" id="confirm_password" size="40">
	</p>
	<p>
		<input type="submit" name="submit" value="Changer mon mot de passe">
	</p>
</form>
<h2>Suppression du compte</h2>
<p>
	<form action="" method="POST">
		<p>
			<button type="submit" name="delete">Supprimer mon compte</button>
		</p>
	</form>
</p>
<?php
endif;

require('includes/footer.php');

?>
