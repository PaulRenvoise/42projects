<?php

session_start();

if (!empty($_SESSION['user_id']))
{
	session_destroy();
	setcookie(session_name(), "", (time() - 3600), "/");
}
header("Location: index.php");
exit;

?>