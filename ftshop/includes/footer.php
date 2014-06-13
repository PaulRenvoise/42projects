<?php
	if ($db !== false)
		mysqli_close($db);
?>
			</div>
			<footer>
				<p>
					<?php if (!empty($_SESSION['user_level']) && $_SESSION['user_level'] >= 4) : ?>
					<a href="admin.php">Espace Admin</a>
					<?php else : ?>
					Made with &lt;3 by prenvois &amp; jlejeune.
					<?php endif; ?>
				</p>
			</footer>
		</div>
	</body>
</html>