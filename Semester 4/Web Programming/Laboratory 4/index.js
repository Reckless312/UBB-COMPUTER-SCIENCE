function createButtonWithClickEvent(buttonText, buttonClass, clickEventId) {
    const button = document.createElement('button');
    const buttonContent = document.createTextNode(buttonText);
    button.appendChild(buttonContent);
    button.classList.add(buttonClass);
    button.addEventListener('click', (e) => {DropDownContentShow(clickEventId)});

    return button;
}

function createButton(buttonText, buttonClass) {
    const button = document.createElement('button');
    const buttonContent = document.createTextNode(buttonText);
    button.appendChild(buttonContent);
    button.classList.add(buttonClass);

    return button;
}

function createDivWithIdAndClass(className, id) {
    const div = document.createElement('div');
    div.classList.add(className);
    div.id = id;

    return div;
}

function createDivWithClass(className) {
    const div = document.createElement('div');
    div.classList.add(className);

    return div;
}

const mainDivContainer = createDivWithIdAndClass('dropdown-content-container', 'main-container')
mainDivContainer.appendChild(createButtonWithClickEvent("DropDownMenu", 'dropdown-content-button', 'drop-major'));

const optionContainer = createDivWithIdAndClass('dropdown-content', 'drop-major');

for (let i = 0; i < 5; i++) {
    const div = createDivWithClass('inner-content-container');
    div.appendChild(createButtonWithClickEvent(`Option ${i+1}`, 'dropdown-content-button', `drop-major-${i+1}`));

    const innerDiv = createDivWithIdAndClass('dropdown-content-inner', `drop-major-${i+1}`);
    for (let j = 0; j < 3; j++) {
        innerDiv.appendChild(createButton(`Inner option ${j+1}`, 'option-button'));
    }

    div.appendChild(innerDiv);
    optionContainer.appendChild(div);
}

mainDivContainer.appendChild(optionContainer);

document.body.appendChild(mainDivContainer);

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

function buttonSubmitClick() {
    const div = createDivWithClass('inner-content-container');

    const input = document.getElementById('input-option')

    div.appendChild(createButtonWithClickEvent(input.value, 'dropdown-content-button', `drop-major-${input.value}`));

    const innerDiv = createDivWithIdAndClass('dropdown-content-inner', `drop-major-${input.value}`);

    const textArea = document.getElementById('textarea-inner-option');

    const contentInTextArea = textArea.value.split('\n');

    for (let j = 0; j < contentInTextArea.length; j++) {
        innerDiv.appendChild(createButton(`${contentInTextArea[j]}`, 'option-button'));
    }

    div.appendChild(innerDiv);
    optionContainer.appendChild(div);
}