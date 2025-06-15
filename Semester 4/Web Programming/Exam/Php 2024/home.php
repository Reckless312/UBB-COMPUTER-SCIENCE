<?php
    include 'database.php';
    session_start();

    if(!isset($_SESSION['popular'])) {
        $_SESSION['popular'] = array();
    }
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
</head>
<body>
    <form action="home.php" method="post">
        <label for="description">Property Description:</label>
        <input type="text" id="description" name="description"><br>
        <input type="submit" name="search" value="Search">
    </form>

    <form action="home.php" method="post">
        <input type="submit" name="showPopular" value="Show Popular Properties">
    </form>

    <form action="home.php" method="post">
        <input type="submit" name="showOwned" value="Show Properties Owned By Multiple People">
    </form>
    <a href="property.php">Properties</a>
    <form action="home.php" method="post">
        <input type="submit" name="logout" value="Logout">
    </form>
</body>
</html>

<?php
    if(isset($_POST['search'])) {
        $description = mysqli_real_escape_string($conn, $_POST['description']);
        $query = "SELECT * FROM Property WHERE description LIKE '%$description%'";
        $result = mysqli_query($conn, $query);

        if (mysqli_num_rows($result) > 0) {
            echo "<h2>Search Results:</h2>";
            while ($row = mysqli_fetch_assoc($result)) {
                $currentAddress = $row['address'];
                $currentDescription = $row['description'];

                if (!isset($_SESSION['popular'][$currentDescription])) {
                    $_SESSION['popular'][$currentDescription] = 1;
                } else {
                    $_SESSION['popular'][$currentDescription]++;
                }

                echo "<p>Address: " . htmlspecialchars($currentAddress) . " - Description: " . htmlspecialchars($currentDescription) . "<br>";
            }
        } else {
            echo "<p>No properties found.</p>";
        }
    }

    if (isset($_POST['showPopular'])) {
        echo "<h2>Popular Property:</h2>";
        
        if (count($_SESSION['popular']) == 0) {
            echo '<p>No popular property found.</p>';
            exit(); 
        }

        $mostPopularPropertyDescription = array_keys($_SESSION['popular'], max($_SESSION['popular']))[0];

        $query = "SELECT * FROM Property WHERE description = '" . mysqli_real_escape_string($conn, $mostPopularPropertyDescription) . "'";
        $result = mysqli_query($conn, $query);

        $row = mysqli_fetch_assoc($result);
        $mostPopularPropertyAddress = $row['address'];

        echo "<p>Address: " . htmlspecialchars($mostPopularPropertyAddress) . " - Description: " . htmlspecialchars($mostPopularPropertyDescription) . "</p>";
        echo "<p>Popularity: " . $_SESSION['popular'][$mostPopularPropertyDescription] . "</p>";
    }

    if (isset($_POST['showOwned'])) {
        $query = "SELECT * FROM Property WHERE id IN (SELECT idProperty FROM UserToProperty GROUP BY idProperty HAVING COUNT(idUser) > 1)";
        $result = mysqli_query($conn, $query);

        if (mysqli_num_rows($result) > 0) {
            echo "<h2>Properties Owned By Multiple People:</h2>";
            while ($row = mysqli_fetch_assoc($result)) {
                echo "<p>Address: " . htmlspecialchars($row['address']) . " - Description: " . htmlspecialchars($row['description']) . "</p>";
            }
        } else {
            echo "<p>No properties owned by multiple people found.</p>";
        }
    }

    if (isset($_POST['logout'])) {
        session_destroy();
        header("Location: login.php");
        exit();
    }
?>