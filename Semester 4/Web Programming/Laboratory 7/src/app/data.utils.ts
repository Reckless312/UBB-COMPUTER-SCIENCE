// export const itemsPerPage : number = 2;
// export let currentPage : number = 1;
//
// export function setPage(newPage: number)
// {
//   currentPage = newPage;
// }
//
// export function createPagesButtons(displayItems: () => void, data: any)
// {
//   const pagesDiv = document.getElementById("pagination");
//   const lastPage = Math.ceil(data.length / itemsPerPage);
//
//   if (pagesDiv === null)
//   {
//     return;
//   }
//
//   pagesDiv.innerHTML = "";
//
//   let firstPageButton, nextPageButton, previousPageButton, lastPageButton, currentPageButton;
//
//   switch (currentPage)
//   {
//     case 1:
//       firstPageButton = createButton("1");
//
//       pagesDiv.appendChild(firstPageButton);
//       if (currentPage !== lastPage && lastPage !== 0)
//       {
//         nextPageButton = createButton(">");
//
//         nextPageButton.addEventListener("click", () =>
//         {
//           currentPage++;
//           createPagesButtons(displayItems, data);
//         })
//
//         nextPageButton.style.backgroundColor = "#568FDA";
//         pagesDiv.appendChild(nextPageButton);
//       }
//       break;
//     case lastPage:
//       lastPageButton = createButton(lastPage.toString());
//       previousPageButton = createButton("<");
//
//       previousPageButton.addEventListener("click", () =>
//       {
//         currentPage--;
//         createPagesButtons(displayItems, data);
//       })
//
//       previousPageButton.style.backgroundColor = "#568FDA";
//
//       pagesDiv.appendChild(previousPageButton);
//       pagesDiv.appendChild(lastPageButton);
//       break;
//     default:
//       currentPageButton = createButton(currentPage.toString());
//       nextPageButton = createButton(">");
//       previousPageButton = createButton("<");
//
//       previousPageButton.addEventListener("click", () =>
//       {
//         currentPage--;
//         createPagesButtons(displayItems, data);
//       })
//
//       nextPageButton.addEventListener("click", () =>
//       {
//         currentPage++;
//         createPagesButtons(displayItems, data);
//       })
//
//       previousPageButton.style.backgroundColor = "#568FDA";
//       nextPageButton.style.backgroundColor = "#568FDA";
//
//       pagesDiv.appendChild(previousPageButton);
//       pagesDiv.appendChild(currentPageButton);
//
//       break;
//   }
//
//   displayItems();
// }
//
// export function createButton(content: string)
// {
//   const button = document.createElement("button");
//   button.innerText = content;
//   return button;
// }
