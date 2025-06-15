import {Component, inject, OnInit, signal} from '@angular/core';
import {FormControl, ReactiveFormsModule} from '@angular/forms';
import {ActivatedRoute, Router} from '@angular/router';
import {ProductsService} from '../services/products.service';

@Component({
  selector: 'app-add-form',
  imports: [
    ReactiveFormsModule
  ],
  templateUrl: './add-form.component.html',
  styleUrl: './add-form.component.css'
})
export class AddFormComponent implements OnInit{
  name = new FormControl('');
  description = new FormControl('');
  price = new FormControl('');

  productService = inject(ProductsService);
  activatedRoute = inject(ActivatedRoute);
  router = inject(Router);

  categoryId = signal(0);

  ngOnInit(): void {
    this.categoryId.set(Number(this.activatedRoute.snapshot.paramMap.get("id")));
  }

  onSubmit(){
      if (this.name.value === "" || this.description.value === "" || this.price.value === "") {
        alert("Please fill all fields.");
        return;
      }

      this.productService.addProduct(this.name.value, this.description.value, this.price.value, this.categoryId()).subscribe(response => {
        this.router.navigate(["/products/" + this.categoryId()]).then();
      })
  }

  constructor()
  {
  }
}
