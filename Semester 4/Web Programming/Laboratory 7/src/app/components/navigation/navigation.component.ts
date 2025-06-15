import {Component, computed, EventEmitter, Input, input, Output, output} from '@angular/core';

@Component({
  selector: 'app-navigation',
  standalone: true,
  imports: [],
  templateUrl: './navigation.component.html',
  styleUrl: './navigation.component.css'
})
export class NavigationComponent {
  currentPage = input(1)
  totalItems = input(0)
  itemsPerPage = input(3)

  @Output() pageChange = new EventEmitter<number>()

  lastPage = computed(() => Math.ceil(this.totalItems() / this.itemsPerPage()))
  isFirstPage = computed(() => this.currentPage() === 1)
  isLastPage = computed(() => this.currentPage() === this.lastPage())


  onNext() {
    if (!this.isLastPage()) {
      this.pageChange.emit(this.currentPage() + 1)
    }
  }

  onPrev() {
    if (!this.isFirstPage()) {
      this.pageChange.emit(this.currentPage() - 1)
    }
  }
}
