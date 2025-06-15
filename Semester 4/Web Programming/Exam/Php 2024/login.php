<?php
    include 'database.php';
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
    <form action="login.php" method="post">
        <label for="name">Name:</label>
        <input type="text" id="name" name="name" required><br>
        <input type="submit" name="login" value="Login">
    </form>
</html>

<?php
    if (isset($_POST['login'])) {
        $get_user_query = "SELECT * FROM User WHERE name = '" . mysqli_real_escape_string($conn, $_POST['name']) . "'";
        $get_user_result = mysqli_query($conn, $get_user_query);

        if (mysqli_num_rows($get_user_result) > 0) {
            $user = mysqli_fetch_assoc($get_user_result);
            $_SESSION['userId'] = $user['id'];
            $_SESSION['name'] = $user['name'];
            $_SESSION['secretQuestion'] = $user['secretQuestion'];
            $_SESSION['secretAnswer'] = $user['secretAnswer'];

            header("Location: secret.php");
        } else {
            echo "<p>User not found!</p>";
        }
    }
?>