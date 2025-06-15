<?php
    include 'header.html';

    $category = null;

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
    <form id="add-product-form" method="POST" action="add_product.php">
        <label for="name">Name</label>
        <input type="text" id="name" name="name" required placeholder="Value">
        <label for="description">Description</label>
        <input type="text" id="description" name="description" required placeholder="Value"></h>
        <label for="price">Price</label>
        <input type="number" id="price" name="price" required placeholder="Value">
        <input type="submit" value="Create Product">
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
            name: formData.get("name"),
            description: formData.get("description"),
            price: formData.get("price"),
            category_id: <?php echo $category; ?>
        };

        fetch("http://localhost/Laboratory%206/api/products.php", {
            method: "POST",
            headers: {
                "Content-Type": "application/json"
            },
            body: JSON.stringify(data)
        })
        .then(response => {
            if (response.ok) {
                window.location.href = "products.php?category=" + <?php echo $category; ?>;
            } else {
                alert("Failed to add product.");
            }
        })
    });
</script>

