import { Component } from '@angular/core';
import {RouterLink} from '@angular/router';
import {HomeComponent} from '../components/home/home.component';
import {ShoppingCartComponent} from '../components/shopping-cart/shopping-cart.component';

@Component({
  selector: 'app-header',
  imports: [HomeComponent, ShoppingCartComponent, RouterLink],
  templateUrl: './header.component.html',
  styleUrl: './header.component.css'
})
export class HeaderComponent {
}
