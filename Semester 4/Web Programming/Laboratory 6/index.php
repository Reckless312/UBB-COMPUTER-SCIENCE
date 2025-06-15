<?php
    include 'header.html';
?>

<html lang="en">
    <head>
        <title>E-Commerce Store</title>
    </head>
    <body>
        <div id="categories-container">
        </div>

        <div class="pagination-container">
            <p style="margin-left: 6px">E-Commerce Store</p>
            <div id="pagination">
            </div>
        </div>
        <script src="items.js"></script>
        <script src="pagination.js"></script>
    </body>
</html>

<script>
    function createCategoryCard(component, id, name, description)
    {
        const innerDiv = document.createElement("div");
        const categoryName = document.createElement("a");
        const categoryDescription = document.createElement("p");

        innerDiv.classList.add("card");

        categoryName.innerText = name;
        categoryName.href = "products.php?category=" + id;
        categoryDescription.innerText = description;

        innerDiv.appendChild(categoryName);
        innerDiv.appendChild(categoryDescription);

        component.appendChild(innerDiv);
    }

    function showCurrentCategoriesOnPage()
    {
        const firstItem = (currentPage - 1) * itemsPerPage;
        const pageItems = data.slice(firstItem, firstItem + itemsPerPage);

        const categoriesDiv = document.getElementById("categories-container");
        categoriesDiv.innerHTML = "";
        pageItems.forEach(item =>
        {
            createCategoryCard(categoriesDiv, item.id, item.name, item.description);
        })
    }

    initializeComponents("http://localhost/Laboratory%206/api/categories.php", showCurrentCategoriesOnPage);
</script>
