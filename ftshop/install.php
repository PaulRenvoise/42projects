<?php

function update_constants($db_host, $username, $password)
{
	if (!($content = file_get_contents('includes/constants.php')))
		return false;
	if (!strpos($content, 'localhost')
		|| !strpos($content, 'root')
		|| !strpos($content, 'toor'))
		return false;
	$content = str_replace('localhost', $db_host, $content);
	$content = str_replace('root', $username, $content);
	$content = str_replace('toor', $password, $content);
	file_put_contents('includes/constants.php', $content);
	return true;
}

if (isset($_POST['db_host']) && isset($_POST['username']) && isset($_POST['password']))
{
	$messages = array();
	$error = '';

	if (!empty($_POST['username']) && !empty($_POST['password']))
	{
		$db_host = htmlspecialchars(addslashes($_POST['db_host']));
		$username = htmlspecialchars(addslashes($_POST['username']));
		$password = htmlspecialchars(addslashes($_POST['password']));
		$hashpass = hash("whirlpool", htmlspecialchars(addslashes($_POST['password'])));

		$db = @mysqli_connect($db_host, $username, $password);
		if ($db === false)
			$error = 'Impossible de se connecter a la base de données.';
		else
		{
			$messages[] = 'Connexion a la base de données';
			if (!update_constants($db_host, $username, $password))
				$error = 'Impossible de modifier les identifiants dans le fichier de configuration.';
			else
			{
				$messages[] = 'Modification des identifiants dans le fichier de configuration';
				if (!mysqli_query($db, "CREATE DATABASE IF NOT EXISTS `rushop`"))
					$error = 'Impossible de créer la base de données.';
				else
				{
					$messages[] = 'Création de la base de données';
					if (!mysqli_select_db($db, 'rushop'))
						$error = 'Impossible de sélectionner la base de données.';
					else
					{
						$messages[] = 'Sélection de la base de données';
						$queries = ["CREATE TABLE IF NOT EXISTS `articles` (
							`id` int(11) NOT NULL AUTO_INCREMENT,
							`name` varchar(255) NOT NULL,
							`image` varchar(255) NOT NULL,
							`price` float NOT NULL,
							`description` text NOT NULL,
							`views` int(11) NOT NULL DEFAULT '0',
							PRIMARY KEY (`id`)
						)",
						"CREATE TABLE IF NOT EXISTS `articles_categories` (
							`id` int(11) NOT NULL AUTO_INCREMENT,
							`article_id` int(11) NOT NULL,
							`category_id` int(11) NOT NULL,
							PRIMARY KEY (`id`)
						)",
						"CREATE TABLE IF NOT EXISTS `categories` (
							`id` int(11) NOT NULL AUTO_INCREMENT,
							`name` varchar(255) NOT NULL,
							PRIMARY KEY (`id`)
						)",
						"CREATE TABLE IF NOT EXISTS `checkouts` (
							`id` int(11) NOT NULL AUTO_INCREMENT,
							`user_id` int(11) NOT NULL,
							`ref` varchar(255) NOT NULL,
							`handling_charge` float NOT NULL,
							`ht` float NOT NULL,
							`tva` float NOT NULL,
							`ttc` float NOT NULL,
							`last_name` varchar(255) NOT NULL,
							`name` varchar(255) NOT NULL,
							`address` varchar(255) NOT NULL,
							`postal_code` varchar(5) NOT NULL,
							`city` varchar(255) NOT NULL,
							`phone` varchar(10) NOT NULL,
							`timestamp` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
							`done` int(11) NOT NULL DEFAULT '0',
							PRIMARY KEY (`id`)
						)",
						"CREATE TABLE IF NOT EXISTS `checkouts_articles` (
							`id` int(11) NOT NULL AUTO_INCREMENT,
							`checkout_id` int(11) NOT NULL,
							`article_id` int(11) NOT NULL,
							`price` float NOT NULL,
							`quantity` int(11) NOT NULL,
							PRIMARY KEY (`id`)
						)",
						"CREATE TABLE IF NOT EXISTS `users` (
							`id` int(11) NOT NULL AUTO_INCREMENT,
							`username` varchar(255) NOT NULL,
							`password` varchar(255) NOT NULL,
							`level` int(1) NOT NULL DEFAULT '1',
							PRIMARY KEY (`id`)
						)"];
						foreach ($queries as $query)
						{
							if (!mysqli_query($db, $query))
								$error = 'Impossible de créer les tables : ' . $query . ' : ' . mysqli_error($db);
						}
						if (empty($error))
						{
							$messages[] = 'Création des tables';
							$queries = ["INSERT INTO `articles` (`id`, `name`, `image`, `price`, `description`, `views`) VALUES
								(1, 'Logitech G500 Gaming Mouse', 'http://media.materiel.net/live/212544.jpg', 65.95, 'Succéder à la célèbre G5, un enjeu de taille pour la G500 dont on aurait pu penser qu''elle peinerait à relever le défi... Il n''en est rien ! C''est sans complexe que cette souris laser passe désormais à une résolution maximale de 5700 dpi, modifiable à la volée, via un bouton dédié. Que les habitués se rassurent, elle garde sa forme ronde et confortable, et se pare désormais d''une belle robe mouchetée.\r\n\r\nPersonnalisez votre souris comme bon vous semble ! Sa molette peut au choix, rester libre ou devenir crantée, ce qui vous permet en une seconde de réaliser des mouvements précis ou ultra-rapides. Ses 10 boutons programmables vous permettent de positionner vos macros préférées, et sa mémoire embarquée est l''atout maitre pour stocker vos profils. Utilisez à bon escient ses 27g de poids et ses pieds en polytetrafluoroethylène qui lui assurent une glisse sans faille : la G500 va devenir une évidence pour tous ceux en manque de confort et de précision !', 45),
								(2, 'Razer DeathAdder 2013', 'http://media.materiel.net/live/198851.jpg', 69.95, 'Depuis sa sortie en 2006, la souris DeathAdder a laissé bon nombre de victimes derrière elle, fait preuve d''endurance pendant des Lan''s interminables et subi les coups de folie (et de génie souvent...!) de nombreux joueurs à travers le monde... Cette souris revient dans une version 2013 qui revoit ses performances à la hausse !\r\n\r\nDeathAdder 2013 : Un capteur optique 4G de 6400 dpi !\r\n\r\nLa souris Razer DeathAdder 2013 se veut encore plus performante, pour cela elle embarque désormais un capteur optique infra-rouge 4G de 6400 DPI pour montrer sa différence et vous prouver que la précision a tout son intérêt ! Rapide, cette souris est capable de subir des accélérations de 50g et elle exécute vos actions avec un temps de réponse de seulement 1ms. Autre changement, cette souris pour droitiers adopte un nouveau design plus ergonomique avec des grips antidérapants sur les cotés pour une meilleure prise en main.\r\n\r\nUn rétroéclairage vert intense !\r\n\r\nQue les fans se rassurent, la DeathAdder a été améliorée mais a su garder ses valeurs. Elle conserve bien entendu ses 5 boutons Hyperesponse entièrement programmables, sa molette crantée, ainsi que son câble tressé. Son rétroéclairage en revanche fait peau neuve pour pulser à présent en vert au niveau de la molette et de l''emblématique logo Razer. Compatible avec le logiciel Razer Synapse 2.0, vos paramètres, macros et profils sont stockés en ligne pour pouvoir y accéder de n''importe où !\r\n\r\nPas de doute, vous avez bien une DeathAdder devant vous... Mais qui a gagné en maturité !', 2),
								(3, 'Logitech G105 Gaming Keyboard', 'http://media.materiel.net/live/215051.png', 49.99, 'Logitech dévoile sa nouvelle gamme de produits pour joueurs avec pour seule ligne de conduite La science au service de votre jeu (Science wins). Pour la marque, aucune place pour l''à-peu-près ni l’improvisation, votre gameplay doit révéler votre talent ! Tous les périphériques de jeu de la gamme G bénéficient donc d''une conception réfléchie, pensée et conçue pour la performance... Pour VOTRE performance !\r\n\r\nNe vous arrêtez pas de jouer... même la nuit !\r\n\r\nA l''instar de ses prédécesseurs, le clavier gaming Logitech G105 prend place dans le monde téméraire des périphériques de jeu et il compte bien se faire un nom !\r\n\r\nObjectif facilement atteignable puisque ce clavier est l''exemple parfait du bon compromis ! Il répond présent à la moindre occasion de combat, que ce soit la journée ou même la nuit... grâce à son rétroéclairage à LED bleu réglable sur 2 niveaux d''intensité. Vous l''aurez compris, si vous êtes prêt à faire des nuits blanches, lui aussi !\r\n\r\n6 touches G programmables !\r\n\r\nLe clavier G105 propose aux gamers de s''armer comme il se doit avant la bataille ! Ses 6 touches G programmables et leurs 3 modes respectifs (M1, M2, M3) vous permettent d''enregistrer jusqu''à 18 fonctions différentes. Vos macros peuvent être enregistrées à la volée grâce à la touche MR, pour vous simplifier la vie et être réactif en toute occasion !\r\n\r\nCe clavier malin a pensé à tout, notamment à intégrer une touche spécialement conçue pour vous faire basculer du mode bureau au mode jeu. Le mode jeu bloque ainsi la touche Windows pour éviter les dérapages en pleine partie...', 1),
								(4, 'Razer DeathStalker Ultimate', 'http://media.materiel.net/live/252886.png', 249.9, 'La marque au serpent tricéphale dévoile une version améliorée de son célèbre DeathStalker. Ajoutant l''interface SwitchBlade, composée d''un écran LCD et de touches dynamiques, abattez vos ennemis depuis les ténèbres...\r\n\r\nTouches plates de type chiclet\r\n\r\nHabile, le clavier Razer DeathStalker Ultimate n''a pas peur de montrer qui il est et ose dévoiler au grand jour ses deux visages : élégant lorsqu''il est question de design, plus agressif lorsqu''il s''agit du jeu ! Grâce à son rétroéclairage LED vert et son profil ultra-fin, ce clavier Razer fait un sacré effet sur votre bureau ! Au delà du confort de frappe, ses touches plates de type chiclet (2 mm d''épaisseur seulement) réduisent le temps de réponse ; vos doigts se déplacent plus vite, favorisant votre réactivité et les commandes en rafale. Il ne vous reste plus qu''à suivre le rythme pour faire le plus de dégâts possibles sur votre passage ! Toutes les touches sont d''ailleurs entièrement programmables, qu''il s''agisse d''enregistrer de simples raccourcis ou des macros d’action évoluées...\r\n\r\nInterface SwitchBlade et 10 touches tactiles\r\n\r\nVoici le centre névralgique de ce clavier. Développée par Razer, l''interface SwitchBlade est un concentré de technologie qui sait se rendre indispensable ! Composée de 10 touches à affichage dynamique (comprendre par là que leur apparence peut être modifiée) et d''un écran LCD multi-touch d''une taille de 89,2 mm x 53,6 mm et d''une résolution de 800 x 480 pixels. Plusieurs applications sont disponibles réparties en deux catégories : les utilitaires et les applications de jeu.\r\n\r\nPour la bureautique, cela permet de configurer certains raccourcis sur les touches dynamiques. Par exemple pour Facebook ou YouTube, la touche de raccourci affichera le logo correspondant. Lancez votre musique, affichez votre playlist, gérez votre volume, consultez les ressources utilisées sur votre PC... Le tout sans quitter votre jeu ! Et ce ne sont que quelques exemples !\r\n\r\nConcernant le jeu, cela permet de disposer de quelques raccourcis supplémentaires (et personnalisés), mais aussi d''un écran très utile pour afficher des informations stratégiques ! Par exemple, affichez le chat de Steam directement sur votre clavier pour éviter qu''il ne vienne masquer des informations à l''écran ! Activez le mode miroir pour afficher des éléments de votre jeu en miroir sur le Switchblade. Avoir une copie de la minimap peut être bien utile selon les circonstances.\r\n\r\nJoueurs de League of Legends, ce clavier va révolutionner votre vie (et votre jungle surtout) ! Drake toutes les 5 minutes, Nashor toutes les 7 minutes... Oubliez les messages sur le chat tels que \"C''est quand le prochain drake ?\", affichez les timers sur votre écran de clavier ! Un coup d’œil rapide dessus et consultez tous les timers de la jungle ! Savoir quand aller counter pour récupérer le blue adverse devient un jeu d''enfant pour peu que vous sachiez quand il a été tué précédemment. Calez vos mouvements à la seconde près ou activez vos objets directement via les touches dynamiques qui prendront l''apparence adéquate.\r\n\r\nAprès tout, si Stalker signifie Traqueur, cela ne peut être un hasard. Traquez-les. Combattez-les. Remportez la victoire.', 1),
								(5, 'Gigabyte GA-Z77-D3H', 'http://media.materiel.net/live/173458.jpg', 94.49, 'Carte mère Gigabyte GA-Z77-D3H : 2 ports PCI-Express 16x 3.0, 4 ports USB 3.0, port mSATA, sortie audio optique\r\nLa carte mère Gigabyte GA-Z77-D3H est conçue à partir d''un contrôleur Intel Z77, et supporte la seconde génération de processeurs Intel Core i3, i5, i7. Premier chipset Intel à pouvoir gérer jusqu''à 4 ports USB 3.0 sans l''adjonction d''un contrôleur supplémentaire le chipset Intel Z77 a également vu sa partie graphique grandement améliorée. Compatible DirectX 11.\r\n\r\nÉquipée de 2 ports PCI-Express 16x, cette carte mère supporte la technologie Crossfire et vous permet de faire fonctionner ensemble jusqu''à deux cartes graphiques.\r\n\r\n3D BIOS\r\n\r\nGigabyte propose sur les cartes mères Z77 un BIOS UEFI à la fois simple, détaillé et efficace. Que vous soyez un utilisateur averti ou un néophyte cherchant juste à régler sa mémoire ou son SSD, le 3D BIOS saura se montrer à la hauteur.\r\n\r\nEn mode avancé, Le BIOS UEFI de GIGABYTE vous donne accès à un très grand nombre d''options et de fonctions techniques.\r\nEn mode 3D, une vue en perspective de votre carte mère regroupe les options par éléments, de façon très visuelle. Vous voulez régler vos barrettes mémoires ? cliquez sur les emplacements mémoire de votre carte mère pour faire apparaitre les options concernant la mémoire. Pour régler votre SSD ? Rien de plus simple, cliquez sur les ports SATA et vous voilà fin prêt. Facile et éducatif le mode 3D réussira certainement à vous réconcilier avec les BIOS d''antan.\r\n\r\n3D POWER\r\n\r\nUtilisant un tout nouveau contrôleur PWM, les cartes mères dotées de la technologie GIGABYTE 3D power offre à l''utilisateur la possibilité de régler encore plus finement les paramètres de sa configuration. Cette technologie permet d''agir sur les trois éléments essentiels que sont les tensions, les fréquences et l''ampérage.\r\n\r\nEn contrôlant plus efficacement les tensions cette technologie permet d''éviter les chutes de tensions au CPU (Vdrop). Une sécurité (Over Voltage Protection) permet de surcroit d''éviter tout risques de dommages au niveau du processeur et de la mémoire.\r\n\r\nCette technologie permet également de calibrer le courant (Over Current Protection) et de lisser les éventuelles micro variations d''ampérage, pour une stabilité accrue même en cas d''overclocking.\r\n\r\nCompatible PCI-Express 3.0\r\n\r\nLe PCI-Express 3.0 offre des performances doublées par rapport à l''actuel PCI-Express 2.0. La bande passante monte désormais à 32 GB/s, ce qui permet à ces nouveaux ports de ne pas brider les prochaines cartes graphiques haut de gamme. Ce nouveau format est de plus rétrocompatible avec les normes PCI-Express 2.0 et 1.0 et vos cartes graphiques actuelles seront à même de vous délivrer leur puissance maximale.\r\n\r\nTout le meilleur de la plateforme 1155\r\n\r\nFort de son expérience avec la puce Hydra, qui permet de combiner les cartes graphiques dédiées AMD et NVIDIA, Lucidlogix a imaginé une puce permettant de faire fonctionner de façon complémentaire le chipset graphique intégré au processeur et votre carte graphique. Ainsi est née Virtu.\r\n\r\nSon système de virtualisation lui permet d''adresser de manière dynamique le chipset graphique intégré ou la carte graphique dédiée en fonction de la charge demandée. Ainsi quand la puissance de la carte graphique n''est pas nécessaire, Virtu bascule sur la solution graphique intégrée au processeur, mettant la carte graphique en veille. La consommation et la ventilation de celle ci sont alors réglées au minimum afin d''offrir un environnement plus économique et silencieux.\r\n\r\nBoostez l''accès à vos fichiers\r\n\r\nDéveloppée par Intel et intégrée pour la première fois sur le chipset Z68 la technologie SSD Caching va vous permettre de transformer un SSD en zone de mémoire cache, afin d''accélérer l''accès aux fichiers les plus fréquemment consultés.\r\n\r\nConsacrer un SSD au système d''exploitation permet certes de profiter d''un démarrage plus rapide et qui ne ralentira pas dans le temps. Si votre machine comporte également un disque dur classique, alors les données et les applications qui s''y trouvent ne profitent pas du gain de rapidité du SSD, pire cela bride ce dernier. L''Intel SMART Response Technology permet d''équilibrer la donne, en agissant comme une vaste zone de stockage où sont conservés les fichiers et les applications les plus utilisés. Ainsi si vous possédez un SSD de faible capacité, cette fonctionnalité vous permettra d''accélérer tout votre système et pas seulement son démarrage. Vous aurez bien sûr la possibilité de vous équiper d''un nouveau SSD de plus grande capacité et profiter à la fois d''un démarrage bien plus rapide et d''un environnement plus réactif.\r\n\r\nON/OFF Charge\r\n\r\nGrâce à cette ingénieuse innovations vous pourrez recharger vos périphériques USB même si votre PC est éteint ou en veille ! Bien pratique pour recharger votre baladeurs MP3 ou votre téléphone la nuit sans avoir besoin de laisser toute votre machine en fonctionnement. De plus le rechargement des péripherique se fait plus rapidement que sur des ports USB 2.0 classique, ce gain peut même jusqu''à 40% de temps gagné ! Cette innovation est donc à la fois pratique et économique, nul doute qu''une fois que vous y aurez gouté, vous ne pourrez plus vous en passer !', 3),
								(6, 'Asus SABERTOOTH Z87 C2', 'http://media.materiel.net/live/230632.jpg', 225.49, 'Nouvelle venue dans la série Asus TUF la carte mère SABERTOOTH Z87 dispose de la même robustesse légendaire que ses ainées. Toujours équipée d''une armure thermique, la SABERTOOTH Z87 dispose de plus d''une armure supplémentaire au dos. Clairement orientée gamer avec ses couleurs militaires. Dotée de 4 ports USB 3.0, d''autant de ports USB 2.0 et de deux ports eSATA cette carte mère est de plus compatible avec les technologies SLI et Crossfire.\r\n\r\nUne série d''exception\r\n\r\nLa série TUF (The Ultimate Force) est aussi l''homonyme anglais de tough qui signifie \"costaud\"; à l''image de leur look militaire, et de la qualité de leur composants. Les cartes mères de cette série sont un concentré de technologies développées dans un seul but : une stabilité sans faille, une compatibilité maximum avec les différents composants et une durée de vie accrue.\r\n\r\nLa carte mère Asus SABERTOOTH Z87 reprend bien sur les codes de la série TUF, avec son carénage noir et ses connecteurs aux couleurs style camouflage. Mais sous l''armure palpite un chipset Intel Z87 spécialement conçu pour épauler au mieux la quatrième génération de processeur Intel Core i3 i5 ou i7. De plus le processeur graphique intégré au processeur a subi d''importantes améliorations en terme de performances. Mais surtout la carte mère SABERTOOTH Z87 offre 3 ports PCI-Express 16x et s''avère pleinement compatibles avec les technologies SLI et Crossfire (2-way). La connectique n''est pas en reste avec 8 ports SATA Revision 3.0 et 4 ports USB 3.0 (+ 1 connecteur interne pour deux ports USB 3.0 en façade).\r\n\r\nLes cartes qui savent garder leur sang-froid !\r\n\r\nQuand vous tomberez nez à nez avec cette carte il est possible qu''un \"petit\" détail attire votre attention, en effet cette carte mère est équipée d''une \"discrète\" armure thermique ! TUF Thermal Armor, de son petit nom, est une innovation que vous ne retrouverez que sur les cartes mères Asus, et outre l''aspect redoutable que cela donne à cette carte mère, cette armure est aussi une ingénieuse façon de protéger les composants de la carte mères contre l''air chaud généré par les autres composants.\r\nAinsi vous pourrez remarquer que la partie la plus protégée de la SABERTOOTH Z87 se situe au niveau des ports PCI-Express 16x, destinés à accueillir les cartes graphiques. La SABERTOOTH Z87 introduit également une nouveauté par rapport aux anciennes version : la présence d''une armure thermique a l''arrière de la carte mère. Destinée à refroidir les VRM présents sur le dos de la carte mère le TUF Fortifier permet aussi de renforcer la carte contre les déformations dues à certaines cartes graphiques haut de gamme très lourdes et encombrantes.\r\nEn cas d''utilisation intensive l''ajout de ventilateurs est possible, afin de forcer le flux d''air sous l''armure thermique. En effet en dessous celle ci est loin d''être lisse et différentes rainures permettent d''orienter les flux d''air afin que les composants importants soient toujours refroidis au mieux.\r\n\r\nCarénée mais loin d''être opaque\r\n\r\nComment savoir ce qu''il se passe sous cette armure ? C''est sans doute la question que vous serez tenté de vous poser, mais Asus a pris les devants et vous offre comme réponse le système Thermal Radar 2.\r\nCe système comprend plusieurs sondes thermiques réparties aux endroits clés de la carte mère SABERTOOTH Z87. Elles ont pour but de suivre en temps réel les températures de la carte mère afin de régler la vitesse du système de refroidissement du processeur et des ventilateurs de façon optimale.\r\nLe système est doté d''une interface graphique conviviale vous permettra d''ajuster les températures en sélectionnant les profils prédéfinis ou en les personnalisant certains vous-mêmes en fonction de vos besoins.', 3),
								(7, 'Intel Core i5 4670K', 'http://media.materiel.net/live/216225.jpg', 204.85, 'La 4ème génération de processeurs Intel Core i5 et i7 est arrivée chez Materiel.net ! Intel présente sa famille de processeurs \"Intel Core\" basés sur sa nouvelle architecture nommée Haswell et sur le nouveau socket 1150. Au programme de cette nouvelle plateforme des performances toujours plus avancées, des contrôleurs graphiques encore plus puissants et une consommation énergétique une nouvelle fois réduite ! Découvrez les nouveaux CPU Intel Core i5 et i7 et tous leurs avantages !\r\n\r\nLe Core i5 en version K : coefficient débloqué !\r\n\r\nLa nouvelle architecture de processeurs Intel débarque sur le marché des PC de bureau. Avec son nom de code Haswell cette nouvelle plateforme s''appuie sur le nouveau socket 1150 (LGA1150). Ces nouveaux CPU Intel Core i5 et i7 affichent des performances processeur jusqu''à 15% supérieures à l''ancienne génération. Ces performances améliorées permettent ainsi un démarrage plus rapide de votre système, de vos logiciels et de vos applications.\r\n\r\nCe nouveau fleuron de la gamme : le Intel Core i5 4670K débarque avec des arguments à faire rougir bon nombre d''autres processeurs ! Dans la tradition des Core i7 il embarque 4 coeurs cadencés à 3,4 GHz qui passeront jusqu''à 3,8 GHz quand la fonction Turbo Boost s''activera ! Avec ses 6 Mo de mémoire cache ce Core i5 4670K ; ultra performant et rapide sera le coeur de votre nouvelle configuration sur ce socket 1150 ! Une nouvelle fois la consommation énergétique a été diminuée puisque son taux de dissipation n''est que de 84 Watts. Cette version K du Core i5 4670 bénéficie d''un avantage très intéressant pour les joueurs et utilisateurs exigeants, son coefficient multiplicateur est débloqué : idéal pour l''overclocking.\r\n\r\nIntel HD 4600 : nouveau contrôleur graphique !\r\n\r\nLa nouvelle génération de processeurs Intel Core i5 et i7 répondant au nom de code Haswell embarque de nouvelles puces graphiques directement intégrées aux processeurs. Ce Core i5 4670K est équipé du contrôleur graphique Intel HD 4600 qui vous fera bénéficier d''une expérience visuelle et graphique plus riche, immersive et fluide en haute définition ! Plus besoin de carte graphique dédiée (si vous ne jouez pas aux derniers jeux) et la résolution 4K est même prise en charge par cette puce graphique aux performances étonnantes !\r\n\r\nTechnologie Intel Turbo Boost 2.0 : le plein de puissance !\r\n\r\nCe processeur Intel Core i5 4670K fleuron de cette nouvelle gamme Intel embarque le maximum de technologies ! Digne des Core i5 il intègre une fonctionnalité majeures d''Intel : le Turbo Boost en version 2.0. A quoi cela peut vous servir ? Concrètement la technologie Turbo Boost permet à votre Intel Core i5 4670K d''augmenter la fréquence de vos coeurs quand vous en avez le besoin en utilisant l''énergie disponible. Il augmente donc ses performances exactement quand votre utilisation le nécessite ! Votre Core i5 4670K passera alors de 3,40 GHz à 3,80 GHz en mode Turbo Boost !', 52),
								(8, 'Intel Xeon E3-1280', 'http://media.materiel.net/live/135979.jpg', 601.99, 'Après la sortie de ses processeurs destinés aux PC de bureau au début de cette l''année 2011, le géant de Santa Clara propose désormais sa nouvelle gamme de processeurs Xeons destinés aux serveurs. En toute logique Intel intègre une nouvelle fois toutes ses dernières avancées technologiques au cœur de ces Xeons.\r\n\r\nAvec ses quatre cœurs cadencés à 3,5 GHz et ses 8 Mo de cache L3, le processeur Intel Xeon E3-1280 est idéal pour une utilisation serveur performante et fiable. Les performances de pointe, la fiabilité, l''évolutivité de ces processeurs n''est plus à prouver, ils sauront palier à tous vos besoins pour toutes vos applications. On retrouve une fois de plus au rendez-vous la technologie Intel® Turbo Boost 2.0 qui vous permettra d''optimiser les performances de ce Xeon E3-1280 en fonction de votre utilisation et augmentera la fréquence d''un cœur jusqu''à 3,9 GHz ! La technologie d''Hyperthreading est également de la partie, simulant la présence de 8 processeurs logiques, ce qui vous assure une utilisation plus efficace et des ressources optimisées surtout dans les applications optimisées pour plusieurs cœurs. Gravé avec une finesse de 32 nanomètres son TDP est lui de 95 Watts.\r\n\r\nCette version des processeurs Xeons basée sur l''architecture Sandybridge et le socket 1155 reprend une fois de plus toutes les caractéristiques d''un bon processeur véloce et destiné aux utilisations professionnelles à la fois exigeantes et évolutives. Les stations de travail dotées de processeurs Intel Xeon E3 vous offriront les performances sur mesure et une puissance optimisé dont vous avez besoin pour l''analyse de données et la création de contenu.', 6)",
							"INSERT INTO `articles_categories` (`id`, `article_id`, `category_id`) VALUES
								(1, 1, 3),
								(2, 2, 3),
								(4, 3, 4),
								(5, 4, 4),
								(6, 5, 1),
								(7, 6, 1),
								(8, 7, 2),
								(9, 8, 2),
								(13, 5, 6),
								(14, 6, 5),
								(15, 7, 9),
								(16, 8, 9),
								(17, 1, 7),
								(18, 2, 8),
								(19, 3, 7),
								(20, 4, 8)",
							"INSERT INTO `categories` (`id`, `name`) VALUES
								(1, 'Cartes-mères'),
								(2, 'Processeurs'),
								(3, 'Souris'),
								(4, 'Claviers'),
								(5, 'Asus'),
								(6, 'Gigabyte'),
								(7, 'Logitech'),
								(8, 'Razer'),
								(9, 'Intel')",
							"INSERT INTO `checkouts` (`id`, `user_id`, `ref`, `handling_charge`, `ht`, `tva`, `ttc`, `last_name`, `name`, `address`, `postal_code`, `city`, `phone`, `timestamp`, `done`) VALUES
								(1, 1, '5341c37d358a6', 6, 621.19, 121.75, 742.94, 'Douglas', 'Adams', '42, Allée Edward Snowden', '42000', 'Forty-Two', '0613374269', '2014-04-06 21:13:33', 0)",
							"INSERT INTO `checkouts_articles` (`id`, `checkout_id`, `article_id`, `price`, `quantity`) VALUES
								(1, 1, 1, 65.95, 1),
								(2, 1, 4, 249.9, 1),
								(3, 1, 5, 94.49, 1),
								(4, 1, 7, 204.85, 1)",
							"INSERT INTO `users` (`id`, `username`, `password`, `level`) VALUES
								(1, '$username', '$hashpass', 5)"];
							foreach ($queries as $query)
							{
								if (!mysqli_query($db, $query))
									$error = 'Impossible de remplir les tables : ' . mysqli_error($db);
							}
							if (empty($error))
								$messages[] = 'Remplissage des tables';
						}
					}
				}
			}
		}
	}
	else
		$error = 'Tous les champs ne sont pas remplis.';
}

?>
<html>
	<head>
		<meta charset="utf-8">
		<title>Installation - Rushop</title>
		<link rel="stylesheet" href="style/style.css">
	</head>
	<body>
		<header>
			<h1 class="sitename">
				<?php if (isset($error) && empty($error)) : ?>
				<a href="index.php" title="Accueil">Rushop</a>
				<?php else : ?>
				<a href="install.php" title="Accueil">Rushop</a>
				<?php endif; ?>
			</h1>
		</header>
		<div class="container">
			<div class="content">
				<h1>
					Installation
					<span>Rapide...</span>
				</h1>
				<?php if (!isset($error)) : ?>
				<p>
					Pour commencer l'installation, veuillez renseigner vos identifiants de votre base de données.
				</p>
				<?php endif; ?>
				<?php if (isset($messages) && count($messages) > 0) : ?>
					<ul class="check">
						<?php foreach ($messages as $message) : ?>
							<li>
								<?= $message ?>
							</li>
						<?php endforeach; ?>
					</ul>
				<?php endif; ?>
				<?php if (!empty($error)) : ?>
				<p class="error">
					<?= $error ?>
				</p>
				<?php elseif (isset($error)) : ?>
				<p class="success">
					Tout s'est bien passé, enjoy ! <a href="index.php">Aller sur Rushop</a>
				</p>
				<?php endif; ?>
				<?php if (!isset($error) || !empty($error)) : ?>
					<form action="" method="POST">
						<p>
							<label for="db_host">Nom d'hôte :</label>
							<input type="text" name="db_host" id="db_host" value="localhost" size="40">
						</p>
						<p>
							<label for="username">Nom d'utilisateur :</label>
							<input type="text" name="username" id="username" size="40">
						</p>
						<p>
							<label for="password">Mot de passe :</label>
							<input type="password" name="password" id="password" size="40">
						</p>
						<p>
							<input type="submit" value="Commencer l'installation">
						</p>
					</form>
				<?php endif; ?>
			</div>
			<footer>
				<p>
					Made with &lt;3 by prenvois &amp; jlejeune.
				</p>
			</footer>
		</div>
	</body>
</html>
