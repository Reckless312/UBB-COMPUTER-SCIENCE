import { Component } from '@angular/core';
import {currentPage, data, initializeComponents, itemsPerPage} from '../data.utils';
import {Router} from '@angular/router';

@Component({
  selector: 'app-categories',
  imports: [],
  templateUrl: './categories.component.html',
  styleUrl: './categories.component.css'
})
export class CategoriesComponent {
  createCategoryCard(component: HTMLElement, id: number, name: string, description: string): void {
    const innerDiv = document.createElement("div");
    const categoryName = document.createElement("a");
    const categoryDescription = document.createElement("p");

    innerDiv.classList.add("card");

    categoryName.innerText = name;
    categoryName.addEventListener("click", async () => {
      await this.router.navigate(["/products/" + id]);
    })
    categoryDescription.innerText = description;

    innerDiv.appendChild(categoryName);
    innerDiv.appendChild(categoryDescription);

    component.appendChild(innerDiv);
  }

  showCurrentCategoriesOnPage(): void {
    const firstItem = (currentPage - 1) * itemsPerPage;
    const pageItems = data.slice(firstItem, firstItem + itemsPerPage);

    const categoriesDiv = document.getElementById("categories-container");

    if (categoriesDiv === null) {
      return;
    }

    categoriesDiv.innerHTML = "";
    pageItems.forEach((item: { id: number; name: string; description: string }) => {
      this.createCategoryCard(categoriesDiv, item.id, item.name, item.description);
    });
  }

  constructor(private router: Router) {
    initializeComponents("http://localhost/Laboratory%206/api/categories.php", this.showCurrentCategoriesOnPage.bind(this));
  }
}
