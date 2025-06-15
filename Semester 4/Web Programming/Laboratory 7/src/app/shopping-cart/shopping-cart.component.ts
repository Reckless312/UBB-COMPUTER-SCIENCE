import {Component, OnInit, signal} from '@angular/core';
import {Product} from '../model/product.type';
import {NavigationComponent} from '../components/navigation/navigation.component';

@Component({
  selector: 'app-shopping-cart',
  imports: [
    NavigationComponent
  ],
  templateUrl: './shopping-cart.component.html',
  styleUrl: './shopping-cart.component.css'
})
export class ShoppingCartComponent implements OnInit {
  products = signal<Array<Product>>([]);
  allProducts = signal<Array<Product>>([]);
  currentPage = signal<number>(1);
  productsOnPage = signal(3);

  ngOnInit(): void {
    let item = localStorage.getItem("cart") || "";
    this.cart = item === "" ? [] : JSON.parse(item);

    this.allProducts.set(this.cart);
    this.displayProducts();

    console.log(this.cart);
  }
  cart: any;

  removeFromCart(id: number)
  {
    this.cart = this.cart.filter((item: any) => item.id !== id);
    localStorage.setItem("cart", JSON.stringify(this.cart));

    this.allProducts.set(this.cart);
    this.displayProducts();
  }

  displayProducts() {
    const start = (this.currentPage() - 1) * this.productsOnPage();
    const end = this.currentPage() * this.productsOnPage();
    this.products.set(this.allProducts().slice(start, end))
  }

  onPageChange(page: number) {
    this.currentPage.set(page);
    this.displayProducts();
  }
}

interface CartItem {
  id: string;
  name: string;
  description: string;
  price: string;
}

