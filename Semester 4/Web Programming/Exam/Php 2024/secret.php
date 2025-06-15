<?php
    session_start();
?>


<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Exam 2024 Php</title>
</head>
<body>
    <form action="secret.php" method="post">
        <?php
            echo $_SESSION['secretQuestion']
        ?><br>
        <input type="password" name="secretAnswer"><br>
        <input type="submit" name="submitAnswer" value="Submit Answer">
    </form>
</html>

<?php
    if (!isset($_SESSION['name'])) {
        header("Location: login.php");
        exit();
    }

    if (isset($_POST['submitAnswer'])) {
        if ($_POST['secretAnswer'] === $_SESSION['secretAnswer']) {
            header("Location: home.php");
        } else {
            echo "<p>Incorrect answer to the secret question!</p>";
        }
    }
?>