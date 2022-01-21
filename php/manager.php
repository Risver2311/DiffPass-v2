<?php

	session_start();
	require_once "connect.php";
	if(!isset($_SESSION['login']))
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
	<link rel="stylesheet" href="manager.css">
</head>
<body>
	<button class="button" onclick="location.href='logout.php'">Log out</button>
	<table class="table">
		<th>Url</th>
		<th>E-mail</th>
		<th>Password</th>

	<?php

		$method = 'AES-256-CBC';
		$iv = base64_decode("Gi9kSb/a5f0h7Mb+sRWQdQ==");
		$key = base64_decode("pE4B5J5u18U55BTJho//Fioy2bEURa5W/o7HrO1O7/s=");

		$connection = new mysqli($host, $db_user, $db_password, $db_name);
		if($connection->connect_error)
		{
			die("connection failed:".$connection-> connect_error);
		}

		$username = $_SESSION['username'];

		$sql = "SELECT url, email, password FROM $username";
		$result = $connection -> query($sql);

		$number_of_users = $result->num_rows;
		if($number_of_users > 0)
		{
			$encryption_key = quoted_printable_decode("test");
			$encryption_key_h = hash("sha256", $encryption_key);
			while($row = $result -> fetch_assoc())
			{
				echo '<tr><td>'. $row['url'] .'</td><td>'. $row['email'] .'</td><td>'. openssl_decrypt(base64_decode($row['password']), 'AES-256-CBC', $key, OPENSSL_RAW_DATA|OPENSSL_ZERO_PADDING, $iv).'</td></tr>';
			}
			echo '</table>';
		}

		$connection -> close();
	?>
</body>
</html>