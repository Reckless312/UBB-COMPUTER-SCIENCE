<?php
    include 'header.html';

    $category = null;

    if (isset($_GET['category']))
    {
        $category = filter_input(INPUT_GET, 'category', FILTER_SANITIZE_NUMBER_INT);
    }
?>

<html lang="en">
<body>
<div id="products-container">
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
    let cart =JSON.parse(localStorage.getItem("cart")) || [];

    function createProductCard(component, id, name, description, price)
    {
        const innerDiv = document.createElement("div");
        const productName = document.createElement("h2");
        const productDescription = document.createElement("p");
        const buttonsDiv = document.createElement("div");
        const buyButton = document.createElement("button");
        const removeButton = document.createElement("button");

        innerDiv.classList.add("card");
        buttonsDiv.classList.add("product-buttons");

        productName.innerText = name;
        productDescription.innerText = description;
        buyButton.innerText = "Buy";
        removeButton.innerText = "Remove from cart";

        buyButton.style.backgroundColor = "#FFB25A";
        removeButton.style.backgroundColor = "#FF7070";

        buyButton.addEventListener("click", () =>
        {
            removeFromCart(id);
        })

        removeButton.addEventListener("click", () =>
        {
            let confirmation = confirm("Are you sure you want to remove this product from the cart?");

            switch(confirmation)
            {
                case true:
                    removeFromCart(id);
                    break;
                case false:
                    break;
            }
        })

        buttonsDiv.appendChild(buyButton);
        buttonsDiv.appendChild(removeButton);

        innerDiv.appendChild(productName);
        innerDiv.appendChild(productDescription);
        innerDiv.appendChild(buttonsDiv);

        component.appendChild(innerDiv);
    }

    function showCurrentProductsOnPage()
    {
        const firstItem = (currentPage - 1) * itemsPerPage;
        const pageItems = cart.slice(firstItem, firstItem + itemsPerPage);

        const productDiv = document.getElementById("products-container");
        productDiv.innerHTML = "";
        pageItems.forEach(item =>
        {
            createProductCard(productDiv, item.id, item.name, item.description, item.price);
        })
    }

    function removeFromCart(id)
    {
        cart = cart.filter(item => item.id !== id);
        localStorage.setItem("cart", JSON.stringify(cart));
        createPagesButtons(showCurrentProductsOnPage, cart);
    }

    createPagesButtons(showCurrentProductsOnPage, cart);
</script>

