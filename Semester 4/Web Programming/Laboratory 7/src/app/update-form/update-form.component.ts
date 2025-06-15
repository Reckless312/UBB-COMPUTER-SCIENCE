import {Component, inject, OnInit, signal} from '@angular/core';
import {FormControl, ReactiveFormsModule} from '@angular/forms';
import {ActivatedRoute, Router} from '@angular/router';
import {ProductsService} from '../services/products.service';

@Component({
  selector: 'app-update-form',
  imports: [
    ReactiveFormsModule
  ],
  templateUrl: './update-form.component.html',
  styleUrl: './update-form.component.css'
})
export class UpdateFormComponent implements OnInit{
  name = new FormControl('');
  description = new FormControl('');
  price = new FormControl('');

  productService = inject(ProductsService);
  activateRoute = inject(ActivatedRoute);
  router = inject(Router);

  id = signal(0);
  outdatedName = signal("");
  outdatedDescription = signal("");
  outdatedPrice = signal("");
  categoryId = signal("");

  onSubmit(){
    if (this.name.value === "" || this.description.value === "" || this.price.value === "") {
      alert("Please fill all fields.");
      return;
    }

    this.productService.updateProduct(this.id(), this.name.value, this.description.value, this.price.value, this.categoryId()).subscribe(response => {
      this.router.navigate(["/products/" + this.categoryId()]).then();
    })
  }

  constructor()
  {
  }

  ngOnInit(): void {
      this.id.set(Number(this.activateRoute.snapshot.paramMap.get("id")));
      this.outdatedName.set(String(this.activateRoute.snapshot.paramMap.get("name")));
      this.outdatedDescription.set(String(this.activateRoute.snapshot.paramMap.get("description")));
      this.outdatedPrice.set(<string>this.activateRoute.snapshot.paramMap.get("price"));
      this.categoryId.set(<string>this.activateRoute.snapshot.paramMap.get("category_id"));

      this.name.setValue(this.outdatedName());
      this.description.setValue(this.outdatedDescription());
      this.price.setValue(String(this.outdatedPrice()))
    }
}
