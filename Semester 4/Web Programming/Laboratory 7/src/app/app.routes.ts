import { Routes } from '@angular/router';
import {CategoriesComponent} from './categories/categories.component';
import {AddFormComponent} from './add-form/add-form.component';
import {UpdateFormComponent} from './update-form/update-form.component';
import {ProductsComponent} from './products/products.component';
// import {ShoppingCartComponent} from './shopping-cart/shopping-cart.component';

export const routes: Routes = [
  { path: '', component: CategoriesComponent},
  { path: 'products/:id', component: ProductsComponent},
  { path: 'add/:id', component: AddFormComponent},
  { path: 'update/:id/:name/:description/:price/:category_id', component: UpdateFormComponent},
  // { path: 'shopping-cart', component: ShoppingCartComponent}
];
