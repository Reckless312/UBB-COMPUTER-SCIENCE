import {Component, computed, inject, OnInit, signal} from '@angular/core';
import {RouterLink} from '@angular/router';
import {CategoriesService} from '../services/categories.service';
import {Category} from '../model/category.type';
@Component({
  selector: 'app-categories',
  imports: [
    RouterLink
  ],
  templateUrl: './categories.component.html',
  styleUrl: './categories.component.css'
})
export class CategoriesComponent implements OnInit {
  categoryService = inject(CategoriesService);

  categories = signal<Array<Category>>([])
  currentPage = signal<number>(1)

  lastPage = signal<number>(1)

  allCategories: Array<Category> = [];
  categoriesOnPage = 3;

  ngOnInit(): void {
      this.categoryService.getCategories().subscribe(categories => {
        this.allCategories = categories
        this.lastPage.set(Math.ceil(this.allCategories.length / this.categoriesOnPage))
        this.displayCategories()
      })
  }

  displayCategories() {
    const start = (this.currentPage() - 1) * this.categoriesOnPage;
    const end = this.currentPage() * this.categoriesOnPage;
    this.categories.set(this.allCategories.slice(start, end))
  }

  nextPage() {
    if(this.currentPage() < this.lastPage()){
      this.currentPage.update(page => page + 1);
      this.displayCategories();
    }
  }

  prevPage() {
    if(this.currentPage() > 1){
      this.currentPage.update(page => page - 1);
      this.displayCategories();
    }
  }

  isFirstPage = computed(() => this.currentPage() === 1)
  isLastPage = computed(() => this.currentPage() === this.lastPage())
}
