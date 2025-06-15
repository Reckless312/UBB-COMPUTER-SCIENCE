import {inject, Injectable} from '@angular/core';
import {HttpClient, HttpHeaders} from '@angular/common/http';
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

  addProduct(name: string | null, description: string | null, price: string | null, category_id: number) {
    const url = "http://localhost/Laboratory%206/api/products.php";
    const headers = new HttpHeaders().set('Content-Type', 'application/json');
    const body = {
      name: name,
      description: description,
      price: price,
      category_id: category_id
    };

    return this.http.post(url, body, { headers: headers });
  }


  constructor() { }
}
