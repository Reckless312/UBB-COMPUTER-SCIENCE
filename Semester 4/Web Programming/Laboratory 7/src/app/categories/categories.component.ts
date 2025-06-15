import {Component, computed, inject, OnInit, signal} from '@angular/core';
import {RouterLink} from '@angular/router';
import {CategoriesService} from '../services/categories.service';
import {Category} from '../model/category.type';
import {NavigationComponent} from '../components/navigation/navigation.component';
@Component({
  selector: 'app-categories',
  standalone: true,
  imports: [
    RouterLink,
    NavigationComponent
  ],
  templateUrl: './categories.component.html',
  styleUrl: './categories.component.css'
})
export class CategoriesComponent implements OnInit {
  categoryService = inject(CategoriesService);

  categories = signal<Array<Category>>([])
  currentPage = signal<number>(1)

  allCategories = signal<Array<Category>>([]);
  categoriesOnPage = 3;

  ngOnInit(): void {
      this.categoryService.getCategories().subscribe(categories => {
        this.allCategories.set(categories);
        this.displayCategories();
      })
  }

  displayCategories() {
    const start = (this.currentPage() - 1) * this.categoriesOnPage;
    const end = this.currentPage() * this.categoriesOnPage;
    this.categories.set(this.allCategories().slice(start, end))
  }

  onPageChange(page: number) {
    this.currentPage.set(page);
    this.displayCategories();
  }
}
