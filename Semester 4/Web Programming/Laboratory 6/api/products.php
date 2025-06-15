<?php
include '../database.php';

header("Access-Control-Allow-Origin: *");
header("Content-Type: application/json");
header("Access-Control-Allow-Methods: GET, POST, PATCH, DELETE");
header("Access-Control-Allow-Headers: Origin, Content-Type, Authorization, X-Requested-With, X-Auth-Token");

if ($_SERVER['REQUEST_METHOD'] == 'OPTIONS') {
    exit(0);
}
elseif ($_SERVER['REQUEST_METHOD'] === 'GET')
{
    $category = null;

    if (isset($_GET['category']))
    {
        $category = filter_input(INPUT_GET, 'category', FILTER_SANITIZE_NUMBER_INT);
    }
    else
    {
        $category = 1;
    }

    $get_products_query = "SELECT * FROM products WHERE category_id = $category";
    $products = mysqli_query($conn, $get_products_query);
    $response = array();

    while ($row = mysqli_fetch_assoc($products))
    {
        $response[] = $row;
    }
    http_response_code(200);
    echo json_encode($response);
}
elseif ($_SERVER['REQUEST_METHOD'] === 'DELETE')
{
    $sent = json_decode(file_get_contents('php://input'), true);

    switch (isset($sent['id']))
    {
        case true:
            $delete_product_query = "DELETE FROM products WHERE id = $sent[id]";
            mysqli_query($conn, $delete_product_query);
            http_response_code(200);
            break;
        case false:
            http_response_code(400);
            break;
    }
}
elseif ($_SERVER['REQUEST_METHOD'] === 'POST')
{
    $sent = json_decode(file_get_contents('php://input'), true);

    if (!isset($sent['name']) || !isset($sent['description']) || !isset($sent['price']) || !isset($sent['category_id']))
    {
        http_response_code(400);
        exit();
    }
    
    $product_name = mysqli_real_escape_string($conn, $sent['name']);
    $product_description = mysqli_real_escape_string($conn, $sent['description']);
    $product_price = mysqli_real_escape_string($conn, $sent['price']);
    $product_category_id = mysqli_real_escape_string($conn, $sent['category_id']);

    $insert_product_query = "INSERT INTO products (name, description, price, category_id) VALUES ('$product_name', '$product_description', '$product_price', '$product_category_id')";
    mysqli_query($conn, $insert_product_query);
    
    http_response_code(200);
}
elseif ($_SERVER['REQUEST_METHOD'] === 'PATCH')
{
    $sent = json_decode(file_get_contents('php://input'), true);

    if (!isset($sent['id']) || !isset($sent['name']) || !isset($sent['description']) || !isset($sent['price']) || !isset($sent['category_id']))
    {
        http_response_code(400);
        exit();
    }

    $product_id = mysqli_real_escape_string($conn, $sent['id']);
    $product_name = mysqli_real_escape_string($conn, $sent['name']);
    $product_description = mysqli_real_escape_string($conn, $sent['description']);
    $product_price = mysqli_real_escape_string($conn, $sent['price']);
    $product_category_id = mysqli_real_escape_string($conn, $sent['category_id']);

    $update_product_query = "UPDATE products SET name='$product_name', description='$product_description', price='$product_price', category_id='$product_category_id' WHERE id=$product_id";
    mysqli_query($conn, $update_product_query);
    
    http_response_code(200);
}
else
{
    http_response_code(405);
}
