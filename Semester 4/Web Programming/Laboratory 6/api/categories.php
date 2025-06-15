<?php
include '../database.php';

header("Access-Control-Allow-Origin: *");
header("Content-Type: application/json");
header("Access-Control-Allow-Methods: GET");
header("Access-Control-Allow-Headers: Content-Type");

$get_categories_query = "SELECT * FROM categories";
$categories = mysqli_query($conn, $get_categories_query);
$response = array();

if (mysqli_num_rows($categories))
{
    while ($row = mysqli_fetch_assoc($categories))
    {
        $response[] = $row;
    }
    http_response_code(200);
    echo json_encode($response);
}
else
{
    http_response_code(404);
}