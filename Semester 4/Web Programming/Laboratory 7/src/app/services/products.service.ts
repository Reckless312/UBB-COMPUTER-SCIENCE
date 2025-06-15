import {inject, Injectable} from '@angular/core';
import {HttpClient} from '@angular/common/http';
import {Product} from '../model/product.type';

@Injectable({
  providedIn: 'root'
})
export class ProductsService {
  http = inject(HttpClient);

  getProducts(id: number) {
    const url = "http://localhost/Laboratory%206/api/products.php?category=" + id;
    return this.http.get<Array<Product>>(url)
  }

  deleteProduct(id: number) {
    const url = "http://localhost/Laboratory%206/api/products.php";
    return this.http.delete(url, {
      headers: {'Content-Type': 'application/json'},
      body: JSON.stringify({id: id})
    })
  }

  constructor() { }
}
