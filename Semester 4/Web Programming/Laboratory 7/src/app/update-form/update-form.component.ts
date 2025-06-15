import {Component} from '@angular/core';
import {FormControl, ReactiveFormsModule} from '@angular/forms';
import {ActivatedRoute, Router} from '@angular/router';

@Component({
  selector: 'app-update-form',
  imports: [
    ReactiveFormsModule
  ],
  templateUrl: './update-form.component.html',
  styleUrl: './update-form.component.css'
})
export class UpdateFormComponent {
  name = new FormControl('');
  description = new FormControl('');
  price = new FormControl('');

  id: number;
  outdatedName: string;
  outdatedDescription: string;
  outdatedPrice: number;
  categoryId: number;

  updateProduct()
  {
    const data = {
      id: this.id,
      name: this.name.value,
      description: this.description.value,
      price: this.price.value,
      category_id: this.categoryId
    };

    fetch("http://localhost/Laboratory%206/api/products.php", {
      method: "PATCH",
      headers: {
        "Content-Type": "application/json"
      },
      body: JSON.stringify(data)
    })
      .then(response => {
        if (response.ok) {
          this.router.navigate(["/products/" + this.categoryId]).then();
        } else {
          alert("Failed to update product.");
        }
      })
  }

  constructor(private router: Router, private activateRoute: ActivatedRoute)
  {
    this.id = Number(this.activateRoute.snapshot.paramMap.get("id"));
    this.outdatedName = String(this.activateRoute.snapshot.paramMap.get("name"));
    this.outdatedDescription = String(this.activateRoute.snapshot.paramMap.get("description"));
    this.outdatedPrice = Number(this.activateRoute.snapshot.paramMap.get("price"));
    this.categoryId = Number(this.activateRoute.snapshot.paramMap.get("category_id"));

    this.name.setValue(this.outdatedName);
    this.description.setValue(this.outdatedDescription);
    this.price.setValue(String(this.outdatedPrice))
  }
}
