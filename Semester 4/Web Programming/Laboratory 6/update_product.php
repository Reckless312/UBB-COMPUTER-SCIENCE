<?php
    include 'header.html';

    $id = null;
    $name = null;
    $description = null;
    $price = null;
    $category = null;

    if (isset($_GET['id']))
    {
        $id = filter_input(INPUT_GET, 'id', FILTER_SANITIZE_NUMBER_INT);
    }

    if (isset($_GET['name']))
    {
        $name = htmlspecialchars($_GET['name']);
    }

    if (isset($_GET['description']))
    {
        $description = htmlspecialchars($_GET['description']);
    }
    
    if (isset($_GET['price']))
    {
        $price = filter_input(INPUT_GET, 'price', FILTER_SANITIZE_NUMBER_FLOAT);
    }

    if (isset($_GET['category']))
    {
        $category = filter_input(INPUT_GET, 'category', FILTER_SANITIZE_NUMBER_INT);
    }
?>

<html lang="en">
<head>
    <link rel="stylesheet" href="style.css">
</head>
<body>
<div class="add-product">
    <div class="card">
        <h2><?php echo $name?></h2>
        <p><?php echo $description?></p>
        <p>Price: <?php echo $price?></p>

    </div>
    <form id="add-product-form" method="POST" action="add_product.php">
        <label for="name">Name</label>
        <input type="text" id="name" name="name" placeholder="Value">
        <label for="description">Description</label>
        <input type="text" id="description" name="description" placeholder="Value"></h>
        <label for="price">Price</label>
        <input type="number" id="price" name="price" placeholder="Value">
        <input type="submit" value="Update Product">
</div>
<div class="pagination-container">
    <p style="margin-left: 6px">E-Commerce Store</p>
</div>
<script src="items.js"></script>
</body>
</html>

<script>
    document.getElementById("add-product-form").addEventListener("submit", function(event) {
        event.preventDefault();

        const formData = new FormData(this);
        const data = {
            id: <?php echo $id; ?>,
            name: formData.get("name") == "" ? "<?php echo $name; ?>" : formData.get("name"),
            description: formData.get("description") == "" ? "<?php echo $description; ?>" : formData.get("description"),
            price: formData.get("price") == "" ? <?php echo $price; ?> : formData.get("price"),
            category_id: <?php echo $category; ?>
        };

        fetch("http://localhost/Laboratory%206/api/products.php", {
            method: "PATCH",
            headers: {
                "Content-Type": "application/json"
            },
            body: JSON.stringify(data)
        })
        .then(response => {
            if (response.ok) {
                window.location.href = "products.php?category=" + <?php echo $category; ?>;
            } else {
                alert("Failed to update product.");
            }
        })
    });
</script>

