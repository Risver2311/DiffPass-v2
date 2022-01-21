<?php
	
	session_start();
	if((isset($_SESSION['login'])) && ($_SESSION['login'] == true))
	{
		header('Location:manager.php');
		exit();
	}
?>

<!DOCTYPE html>
<html>
<head>
	<meta charset="utf-8">
	<title>DiffPass v2</title>
	<link rel="stylesheet" href="main.css">
</head>
<body>
	<div class="wrapper">
	<form class="login" action="login.php" method="POST">
		<p class="title">Login</p>
		<input class="input" type="text" placeholder="Username" name="username"></br>
		<input class="input" type="password" placeholder="Password" name="password"></br>
		<button class="button"> 
			<span>Log in</span>
		</button>
	</form>
		<?php
			if(isset($_SESSION['error']))
			{	
				echo $_SESSION['error'];
			}
		?>
	</div>
</body>
</html>