<?php

	session_start();

	require_once "connect.php";

	if((!isset($_POST['username'])) || (!isset($_POST['password'])))
	{
		header('Location: index.php');
		exit();
	}

	$connection = new mysqli($host, $db_user, $db_password, $db_name);

	$username=$_POST['username'];
	$password=$_POST['password'];

	$username = htmlentities($username, ENT_QUOTES, "UTF-8");
	$password = md5($password);

	if($result = $connection->query(sprintf("SELECT * FROM users WHERE username='%s' AND password='$password'",
		mysqli_real_escape_string($connection, $username))))
	{
		$number_of_users = $result->num_rows;
		if($number_of_users > 0)
		{
			$row = $result->fetch_assoc();
			$_SESSION['login'] = true;
			$_SESSION['username'] = $row['username'];

			unset($_SESSION['error']);
			$result->free_result();
			header('Location: manager.php');

		}

		else
		{
			$_SESSION['error'] = '<span style="color:red">Your login or password is not correct</span>';
			header('Location: index.php');
		}

		$connection->close();
	}

?>