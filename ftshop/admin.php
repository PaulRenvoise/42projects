<?php

$page_title = 'Administration';

require('includes/header.php');

?>
<h1>Administration <span>Level over 9000</span></h1>

<?php if (empty($_SESSION) || $_SESSION['user_level'] < 4) :?>
<p class="error">
	Cette page n'est accessible qu'aux administrateurs du site.<br>
	Cliquez <a href="index.php">ici</a> pour retourner a l'accueil.
</p>
<?php else : ?>
<?php

$_SESSION['mod_user_id'] = NULL;
$_SESSION['mod_user_name'] = NULL;
$_SESSION['mod_art_id'] = NULL;
$_SESSION['mod_art_name'] = NULL;
?>
<h2>Commandes</h2>
<ul class="spaced">
	<li>
		<a href="admin_checkouts.php">Gérer les commandes.</a>
	</li>
</ul>
<h2>Articles</h2>
<ul class="spaced">
	<li>
		<a href="admin_add_article.php">Ajouter un article à la base de données.</a>
	</li>
	<li>
		<a href="admin_upd_article.php">Modifier un article dans la base de données.</a>
	</li>
	<li>
		<a href="admin_del_article.php">Supprimer un article de la base de données.</a>
	</li>
</ul>
<h2>Catégories</h2>
<ul class="spaced">
	<li>
		<a href="admin_add_category.php">Ajouter une catégorie à la base de données.</a>
	</li>
	<li>
		<a href="admin_upd_category.php">Modifier une catégorie dans la base de données.</a>
	</li>
	<li>
		<a href="admin_del_category.php">Supprimer une catégorie de la base de données.</a>
	</li>
</ul>
<h2>Utilisateurs</h2>
<ul class="spaced">
	<li>
		<a href="admin_add_user.php">Ajouter un utilisateur à la base de données.</a>
	</li>
	<li>
		<a href="admin_upd_user.php">Modifier un utilisateur dans la base de données.</a>
	</li>
	<li>
		<a href="admin_del_user.php">Supprimer un utilisateur de la base de données.</a>
	</li>
</ul>
<?php endif; ?>
<?php

require('includes/footer.php');

?>
