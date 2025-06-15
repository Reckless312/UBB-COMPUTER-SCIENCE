import {inject, Injectable} from '@angular/core';
import {Category} from '../model/category.type';
import {HttpClient} from '@angular/common/http';

@Injectable({
  providedIn: 'root'
})
export class CategoriesService {
  http = inject(HttpClient);

  getCategories() {
    const url = "http://localhost/Laboratory%206/api/categories.php";
    return this.http.get<Array<Category>>(url)
  }

  constructor() { }
}
