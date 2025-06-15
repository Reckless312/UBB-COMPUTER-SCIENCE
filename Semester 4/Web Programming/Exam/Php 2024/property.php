<?php
    include 'database.php';
    session_start();
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
</head>
<body>
    <h3>Add to your properties</h3>
    <form action="property.php" method="post">
        <label for="address">Property Address:</label>
        <input type="text" id="address" name="address" required><br>
        <label for="description">Property Description:</label>
        <input type="text" id="description" name="description" required><br>
        <input type="submit" name="addProperty" value="Add Property">
    </form>
    <h3>Delete from your properties</h3>
    <form action="property.php" method="post">
        <label for="deleteAddress">Property Address to Delete:</label>
        <input type="text" id="deleteAddress" name="deleteAddress" required><br>
        <input type="submit" name="deleteProperty" value="Delete Property">
    </form>
</body>
</html>
<?php
    if (isset($_POST['addProperty'])) {
        $address = mysqli_real_escape_string($conn, $_POST['address']);
        $description = mysqli_real_escape_string($conn, $_POST['description']);
        $userId = mysqli_real_escape_string($conn, $_SESSION['userId']);
        $property_id = -1;

        $selectQuery = "SELECT * FROM Property WHERE address = '" . $address . "'" . " AND description = '" . $description . "'";
        $selectResult = mysqli_query($conn, $selectQuery);
        if (mysqli_num_rows($selectResult) == 0) {
            $insert_query = "INSERT INTO Property (address, description) VALUES ('$address', '$description')";
            $insertResult = mysqli_query($conn, $insert_query);
            $property_id = mysqli_insert_id($conn);
        }

        if ($property_id == -1) {
            $property = mysqli_fetch_assoc($selectResult);
            $property_id = $property['id'];

            $checkOwnershipQuery = "SELECT * FROM UserToProperty WHERE idUser = '$userId' AND idProperty = '$property_id'";
            $checkOwnershipResult = mysqli_query($conn, $checkOwnershipQuery);
            if (mysqli_num_rows($checkOwnershipResult) > 0) {
                echo "You already own this property.<br>";
                return;
            }
        }

        $insert_query = "INSERT INTO UserToProperty (idUser, idProperty) VALUES ('" . $userId . "', '$property_id')";
        
        mysqli_query($conn, $insert_query);
    }
    if (isset($_POST['deleteProperty'])) {
        $userId = mysqli_real_escape_string($conn, $_SESSION['userId']);
        $deleteAddress = mysqli_real_escape_string($conn, $_POST['deleteAddress']);

        $checkExistanceQuery = "SELECT * FROM UserToProperty WHERE idUser = '$userId' AND idProperty IN (SELECT id FROM Property WHERE address = '$deleteAddress')";
        $checkExistanceResult = mysqli_query($conn, $checkExistanceQuery);
        if (mysqli_num_rows($checkExistanceResult) == 0) {
            echo "You don't own this property.<br>";
            return;
        }
        
        $deleteQuery = "DELETE FROM UserToProperty WHERE idUser = '$userId' AND idProperty IN (SELECT id FROM Property WHERE address = '$deleteAddress')";
        $deleteResult = mysqli_query($conn, $deleteQuery);

        $selectQuery = "SELECT * FROM UserToProperty WHERE idProperty IN (SELECT id FROM Property WHERE address = '$deleteAddress')";
        if (mysqli_num_rows(mysqli_query($conn, $selectQuery)) == 0) {
            echo "No user owns this property, deleting it from the database.<br>";
            $deletePropertyQuery = "DELETE FROM Property WHERE address = '$deleteAddress'";
            mysqli_query($conn, $deletePropertyQuery);
        }
    }

    echo "<h2>Your Properties:</h2>";
    $query = "SELECT * FROM Property WHERE id IN (SELECT idProperty FROM UserToProperty WHERE idUser = '" . mysqli_real_escape_string($conn, $_SESSION['userId']) . "')";
    $result = mysqli_query($conn, $query);
    if (mysqli_num_rows($result) > 0) {
        while ($row = mysqli_fetch_assoc($result)) {
            echo "<p>Address: " . htmlspecialchars($row['address']) . " - Description: " . htmlspecialchars($row['description']) . "</p>";
        }
    } else {
        echo "<p>You don't own any properties!</p>";
    }

    echo "<h2>Properties you don't own:</h2>";
    $query = "SELECT * FROM Property WHERE id NOT IN (SELECT idProperty FROM UserToProperty WHERE idUser = '" . mysqli_real_escape_string($conn, $_SESSION['userId']) . "')";
    $result = mysqli_query($conn, $query);
    if (mysqli_num_rows($result) > 0) {
        while ($row = mysqli_fetch_assoc($result)) {
            echo "<p>Address: " . htmlspecialchars($row['address']) . " - Description: " . htmlspecialchars($row['description']) . "</p>";
        }
    } else {
        echo "<p>You own all available properties!</p>";
    }
?>