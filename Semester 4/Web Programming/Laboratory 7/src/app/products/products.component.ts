import { Component } from '@angular/core';
import {currentPage, data, initializeComponents, itemsPerPage, setData, setPage} from '../data.utils';
import {ActivatedRoute, Router} from '@angular/router';

@Component({
  selector: 'app-products',
  imports: [],
  templateUrl: './products.component.html',
  styleUrl: './products.component.css'
})
export class ProductsComponent {
  categoryId: number;

  createAddCard(component: HTMLElement)
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
    addImage.src = "plus.png";
    addImage.style.width = "50px";
    addImage.style.height = "50px";

    addImage.addEventListener("click", async () =>
    {
      await this.router.navigate(["/add/" + this.categoryId]);
    });

    innerDiv.appendChild(productName);
    innerDiv.appendChild(productDescription);
    flexDiv.appendChild(innerDiv);
    flexDiv.appendChild(addImage);

    component.appendChild(flexDiv);
  }

  createProductCard(component: HTMLElement, id: number, name: string, description: string, price: number)
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

              let newData: any = [];
              data.forEach((item: any) =>
              {
                if (item.id != id)
                {
                  newData.push(item);
                }
              });
              setData(newData);
              setPage(1);
              this.showCurrentProductsOnPage();
            });
          break;
        case false:
          break;
      }
    })



    updateButton.addEventListener("click", async () =>
    {
      await this.router.navigate(['/update', id, name, description, price, this.categoryId]);
    })

    addToCartButton.addEventListener("click", () =>
    {
      let item = localStorage.getItem("cart") || "";
      let cart = item === "" ? [] : JSON.parse(item);
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

  showCurrentProductsOnPage()
  {
    const firstItem = (currentPage - 1) * itemsPerPage;
    const pageItems = data.slice(firstItem, firstItem + itemsPerPage);

    const productDiv = document.getElementById("products-container");

    if (productDiv === null)
    {
      return;
    }

    productDiv.innerHTML = "";
    this.createAddCard(productDiv);
    pageItems.forEach((item: any) =>
    {
      this.createProductCard(productDiv, item.id, item.name, item.description, item.price);
    })
  }

  constructor(private router: Router, private activateRoute: ActivatedRoute)
  {
    this.categoryId = Number(this.activateRoute.snapshot.paramMap.get("id"));
    initializeComponents("http://localhost/Laboratory%206/api/products.php?category=" + this.categoryId , this.showCurrentProductsOnPage.bind(this));
  }
}
