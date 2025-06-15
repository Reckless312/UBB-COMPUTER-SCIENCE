import { Component } from '@angular/core';
import {FormControl, ReactiveFormsModule} from '@angular/forms';
import {ActivatedRoute, Router} from '@angular/router';

@Component({
  selector: 'app-add-form',
  imports: [
    ReactiveFormsModule
  ],
  templateUrl: './add-form.component.html',
  styleUrl: './add-form.component.css'
})
export class AddFormComponent {
    name = new FormControl('');
    description = new FormControl('');
    price = new FormControl('');

   categoryId: number;

    addProduct()
    {
      const data = {
        name: this.name.value,
        description: this.description.value,
        price: this.price.value,
        category_id: this.categoryId
    };

      fetch("http://localhost/Laboratory%206/api/products.php", {
        method: "POST",
        headers: {
          "Content-Type": "application/json"
        },
        body: JSON.stringify(data)
      })
        .then(response => {
          if (response.ok) {
            this.router.navigate(["/products/" + this.categoryId]).then();
          } else {
            alert("Failed to add product.");
          }
        })
    }

    constructor(private router: Router, private activateRoute: ActivatedRoute)
    {
      this.categoryId = Number(this.activateRoute.snapshot.paramMap.get("id"));
    }
}
