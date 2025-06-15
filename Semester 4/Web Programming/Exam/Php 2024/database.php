<?php
    $db_server = "localhost";
    $db_username = "cora";
    $db_password = "GMTz1234";
    $db_name = "php_2024";

    try
    {
        $conn = mysqli_connect($db_server, $db_username, $db_password, $db_name);
    }
    catch (mysqli_sql_exception)
    {
        echo "Can't retrieve data! Couldn't connect to the server!";
    }