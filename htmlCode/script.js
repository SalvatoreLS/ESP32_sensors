// LEDS

const redLed = document.querySelector("#red");
const blueLed = document.querySelector("#blue");
const yellowLed = document.querySelector("#yellow");

function toggleLed(id, element) {
    console.log(`${id}: New state selected: ` + element.value);

    fetch("/?" + id + "=" + element.value + "&")
        .then(response => {
            if (response.ok) {
                console.log(id + " " + element.value + " success");
            } else {
                console.log(id + " " + element.value + " error");
            }
        })
        .catch(error => {
            console.log(id + " " + element.value + " error: " + error);
        });

    element.value = element.value == "on" ? "off" : "on";
}

//==============================================================================================

// RGB LED

const RGBselect = document.querySelector("#RGBselector");

function rgbLEDchange(id, element) {
    console.log(`${id}: New color selected: ` + element.value);

    fetch("/?" + id + "=" + element.value + "&")
        .then(response => {
            if (response.ok) {
                console.log(id + " " + element.value + " success");
            } else {
                console.log(id + " " + element.value + " error");
            }
        })
        .catch(error => {
            console.log(id + " " + element.value + " error: " + error);
        });
}

//===============================================================================================

var servoP = document.getElementById("servoPos");
servoP.innerHTML = slider.value;

function servo(pos) {
    fetch("/?servo=" + pos + "&")
        .then(response => {
            if (response.ok) {
                console.log("Servo position set to: " + pos);
            } else {
                console.log("Error setting servo position");
            }
        })
        .catch(error => {
            console.log("Error setting servo position: " + error);
        });
}

slider.oninput = function () {
    slider.value = this.value;
    servoP.innerHTML = this.value;
}

//===============================================================================================

// PIEZO

const playBtn = document.querySelector("#playButton");
const songSelector = document.querySelector("#song-select");

function songSelection(id) {

    console.log(`${id}: New song selected`);
    fetch("/?song=" + songSelector.value + "&")
        .then(response => {
            if (response.ok) {
                console.log(id + " " + songSelector.value + " success");
            } else {
                console.log(id + " " + songSelector.value + " error");
            }
        })
        .catch(error => {
            console.log(id + " " + songSelector.value + " error: " + error);
        });
}

//===============================================================================================

// ULTRASONIC SENSOR

const ultrasonicBox = document.querySelector("#ultrasonicBox");

setInterval(function () {

    fetch("/?value=ultrasonic&")
        .then(response => {
            if (response.ok) {
                response.text().then(data => {
                    ultrasonicBox.innerHTML = data + " cm";
                });
            } else {
                console.log("Error getting ultrasonic value");
            }
        })
        .catch(error => {
            console.log("Error getting ultrasonic value: " + error);
        });
}, 1000);

//===============================================================================================