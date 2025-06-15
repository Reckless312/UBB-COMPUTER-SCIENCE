import {Component, inject, OnInit, signal} from '@angular/core';
import {ActivatedRoute, RouterLink} from '@angular/router';
import {ProductsService} from '../services/products.service';
import {Product} from '../model/product.type';
import {NavigationComponent} from '../components/navigation/navigation.component';

@Component({
  selector: 'app-products',
  standalone: true,
  imports: [
    RouterLink,
    NavigationComponent
  ],
  templateUrl: './products.component.html',
  styleUrl: './products.component.css'
})
export class ProductsComponent implements OnInit {
  productService = inject(ProductsService);
  route = inject(ActivatedRoute);

  products = signal<Array<Product>>([]);
  allProducts = signal<Array<Product>>([]);
  currentPage = signal<number>(1);
  productsOnPage = signal(3);

  categoryId = signal(0);

  ngOnInit(): void {
    this.categoryId.set(Number(this.route.snapshot.paramMap.get("id")));
    this.productService.getProducts(this.categoryId()).subscribe(products => {
      this.allProducts.set(products);
      this.displayProducts();
    })
  }

  displayProducts() {
    const start = (this.currentPage() - 1) * this.productsOnPage();
    const end = this.currentPage() * this.productsOnPage();
    this.products.set(this.allProducts().slice(start, end))
  }

  deleteProduct(id: number) {
    this.productService.deleteProduct(id).subscribe(response => {})
    this.productService.getProducts(this.categoryId()).subscribe(products => {
      this.allProducts.set(products);
    })
  }

  addToCart(id: number, name: string, description: string, price: number)
  {
    let item = localStorage.getItem("cart") || "";
    let cart = item === "" ? [] : JSON.parse(item);
    cart.push({id: id, name: name, description: description, price: price});
    localStorage.setItem("cart", JSON.stringify(cart));
  }

  onPageChange(page: number) {
    this.currentPage.set(page);
    this.displayProducts();
  }

  isInCart(id: number)
  {
    let item = localStorage.getItem("cart") || "";
    let cart = item === "" ? [] : JSON.parse(item);
    return cart.some((item: any) => item.id === id);
  }


  constructor()
  {
  }
}
