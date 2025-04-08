function DropDownContentShow(id) {
    document.getElementById(id).classList.toggle("show");

    const subMenus = document.getElementsByClassName('dropdown-content-inner')
    for (let i = 0; i < subMenus.length; i++) {
        if (subMenus[i].id !== id) {
            subMenus[i].classList.remove('show');
        }
    }
}

window.onclick = function(event) {
    if (!event.target.matches('.dropdown-content-button, .option-button')) {
        const dropdowns = document.getElementsByClassName("dropdown-content");
        let i;
        for (i = 0; i < dropdowns.length; i++) {
            const openDropdown = dropdowns[i];
            if (openDropdown.classList.contains('show')) {
                openDropdown.classList.remove('show');
            }
        }
    }
}