// import {AfterViewInit, Component} from '@angular/core';
//
// @Component({
//   selector: 'app-shopping-cart',
//   imports: [],
//   templateUrl: './shopping-cart.component.html',
//   styleUrl: './shopping-cart.component.css'
// })
// export class ShoppingCartComponent implements AfterViewInit {
//   cart: any;
//
//   createProductCard(component: HTMLElement, id: number, name: string, description: string, price: number)
//   {
//     const innerDiv = document.createElement("div");
//     const productName = document.createElement("h2");
//     const productDescription = document.createElement("p");
//     const buttonsDiv = document.createElement("div");
//     const buyButton = document.createElement("button");
//     const removeButton = document.createElement("button");
//
//     innerDiv.classList.add("card");
//     buttonsDiv.classList.add("product-buttons");
//
//     productName.innerText = name;
//     productDescription.innerText = description;
//     buyButton.innerText = "Buy";
//     removeButton.innerText = "Remove from cart";
//
//     buyButton.style.backgroundColor = "#FFB25A";
//     removeButton.style.backgroundColor = "#FF7070";
//
//     buyButton.addEventListener("click", () =>
//     {
//       this.removeFromCart(id);
//     })
//
//     removeButton.addEventListener("click", () =>
//     {
//       let confirmation = confirm("Are you sure you want to remove this product from the cart?");
//
//       switch(confirmation)
//       {
//         case true:
//           this.removeFromCart(id);
//           break;
//         case false:
//           break;
//       }
//     })
//
//     buttonsDiv.appendChild(buyButton);
//     buttonsDiv.appendChild(removeButton);
//
//     innerDiv.appendChild(productName);
//     innerDiv.appendChild(productDescription);
//     innerDiv.appendChild(buttonsDiv);
//
//     component.appendChild(innerDiv);
//   }
//
//   showCurrentProductsOnPage()
//   {
//     const firstItem = (currentPage - 1) * itemsPerPage;
//     const pageItems = this.cart.slice(firstItem, firstItem + itemsPerPage);
//
//     const productDiv = document.getElementById("products-container");
//
//     if (productDiv === null)
//     {
//       return;
//     }
//
//     productDiv.innerHTML = "";
//     pageItems.forEach((item: any) =>
//     {
//       this.createProductCard(productDiv, item.id, item.name, item.description, item.price);
//     })
//   }
//
//   removeFromCart(id: number)
//   {
//     this.cart = this.cart.filter((item: any) => item.id !== id);
//     localStorage.setItem("cart", JSON.stringify(this.cart));
//     createPagesButtons(this.showCurrentProductsOnPage.bind(this), this.cart);
//   }
//
//   ngAfterViewInit() {
//     let item = localStorage.getItem("cart") || "";
//     this.cart = item === "" ? [] : JSON.parse(item);
//     createPagesButtons(this.showCurrentProductsOnPage.bind(this), this.cart);
//   }
// }
