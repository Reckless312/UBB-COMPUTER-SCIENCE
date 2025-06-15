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
    function createAddCard(component)
    {
        const innerDiv = document.createElement("div");
        const flexDiv = document.createElement("div");
        const productName = document.createElement("h2");
        const productDescription = document.createElement("p");
        const addImage = document.createElement("img");

        flexDiv.classList.add("card");
        flexDiv.style.display = "flex";
        flexDiv.style.justifyContent = "space-between";
        flexDiv.style.alignItems = "center";
        
        productName.innerText = "Want to sell in this category?";
        productDescription.innerText = "All you have to do is click the button below and fill out the form!";
        addImage.src = "images/plus.png"
        addImage.style.width = "50px";
        addImage.style.height = "50px";

        addImage.addEventListener("click", () =>
        {
            window.location.href = "add_product.php?category=" + <?php
                echo $category;
                ?>;
        });

        innerDiv.appendChild(productName);
        innerDiv.appendChild(productDescription);
        flexDiv.appendChild(innerDiv);
        flexDiv.appendChild(addImage);

        component.appendChild(flexDiv);
    }

    function createProductCard(component, id, name, description, price)
    {
        const innerDiv = document.createElement("div");
        const productName = document.createElement("h2");
        const productDescription = document.createElement("p");
        const buttonsDiv = document.createElement("div");
        const crudOperation = document.createElement("div");
        const deleteButton = document.createElement("button");
        const updateButton = document.createElement("button");
        const addToCartButton = document.createElement("button");

        innerDiv.classList.add("card");
        buttonsDiv.classList.add("product-buttons");

        productName.innerText = name;
        productDescription.innerText = description;
        deleteButton.innerText = "Delete";
        updateButton.innerText = "Update";
        addToCartButton.innerText = "Add to cart";

        deleteButton.style.backgroundColor = "#FF7070";
        updateButton.style.backgroundColor = "#568FDA";
        addToCartButton.style.backgroundColor = "#56DA70";

        deleteButton.addEventListener("click", () =>
        {
            const confirmationResponse = confirm("Are you sure you want to delete this product?");

            switch (confirmationResponse)
            {
                case true:
                    fetch("http://localhost/Laboratory%206/api/products.php",
                        {
                            method: "DELETE",
                            headers: {"Content-Type": "application/json"},
                            body: JSON.stringify({id: id})
                        })
                        .then(response =>
                        {
                            console.log(response);
                            if (!response.ok)
                            {
                                throw new Error("We didn't receive a status 200 from the server!");
                            }

                            let newData = [];
                            data.forEach(item =>
                            {
                                if (item.id != id)
                                {
                                    newData.push(item);
                                }
                            });
                            data = newData;
                            currentPage = 1;
                            showCurrentProductsOnPage();
                        });
                    break;
                case false:
                    break;
            }
        })



        updateButton.addEventListener("click", () =>
        {
            window.location.href = "update_product.php?id=" + id + "&name=" + name + "&description=" + description + "&price=" + price + "&category=" + <?php
                echo $category;
                ?>;
        })

        addToCartButton.addEventListener("click", () =>
        {
            let cart = JSON.parse(localStorage.getItem("cart")) || [];
            cart.push({id: id, name: name, description: description, price: price});
            localStorage.setItem("cart", JSON.stringify(cart));
            
            addToCartButton.style.display = "none";
        })

        crudOperation.appendChild(deleteButton);
        crudOperation.appendChild(updateButton);

        buttonsDiv.appendChild(crudOperation);
        buttonsDiv.appendChild(addToCartButton);

        innerDiv.appendChild(productName);
        innerDiv.appendChild(productDescription);
        innerDiv.appendChild(buttonsDiv);

        component.appendChild(innerDiv);
    }

    function showCurrentProductsOnPage()
    {
        const firstItem = (currentPage - 1) * itemsPerPage;
        const pageItems = data.slice(firstItem, firstItem + itemsPerPage);

        const productDiv = document.getElementById("products-container");
        productDiv.innerHTML = "";
        createAddCard(productDiv);
        pageItems.forEach(item =>
        {
            createProductCard(productDiv, item.id, item.name, item.description, item.price);
        })
    }

    initializeComponents("http://localhost/Laboratory%206/api/products.php?category=" + <?php
        echo $category;
        ?>, showCurrentProductsOnPage);
</script>

