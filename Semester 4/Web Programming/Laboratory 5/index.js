let currentTransition = 0;
let lastX;
let lastY;
let isHolding = false;
let interval;
let intervalPassed = false;

interval = setInterval(() => {
    intervalPassed = true;
}, 200);

$("body").on("mousedown", function() {
    isHolding = true;
}).on("mouseup", function() {
    isHolding = false;
}).on("mousemove", function(e) {
    let currentX = e.pageX;
    let currentY = e.pageY;

    console.log(`page X: ${e.pageX}, page Y: ${e.pageY}`);

    let cssTransitions = [{"background-image": `radial-gradient(at ${currentX}px ${currentY}px, red, yellow, green)`},
        {"background-image": `radial-gradient(at ${currentX}px ${currentY}px, blue, yellow, green)`},
        {"background-image": `radial-gradient(at ${currentX}px ${currentY}px, green, yellow, green)`},
        {"background-image": `radial-gradient(at ${currentX}px ${currentY}px, yellow, yellow, green)`},
        {"background-image": `radial-gradient(at ${currentX}px ${currentY}px, purple, yellow, green)`},
        {"background-image": `radial-gradient(at ${currentX}px ${currentY}px, pink, yellow, green)`},
        {"background-image": `radial-gradient(at ${currentX}px ${currentY}px, black, yellow, green)`},
        {"background-image": `radial-gradient(at ${currentX}px ${currentY}px, white, yellow, green)`}]

    switch(isHolding) {
        case true:
            if (intervalPassed && currentX >= lastY) {
                currentTransition = currentTransition >= cssTransitions.length - 1 ? 0 : currentTransition + 1;
                intervalPassed = false;
            }
            else if(intervalPassed){
                currentTransition = currentTransition <= 0 ? cssTransitions.length - 1 : currentTransition - 1;
                intervalPassed = false;
            }
            console.log(`${currentTransition}`);
            $("#gradient").css(cssTransitions[currentTransition]);
            break;
        case false:
            currentTransition = 0;
            $("#gradient").css({"background-image": `radial-gradient(at ${lastX}px ${lastY}px, red, yellow, green)`})
            break;
    }

    lastX = currentX;
    lastY = currentY;
})