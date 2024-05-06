// AJAX

$.ajaxSetup({timeout:1000});

//==============================================================================================

// LEDS

const redLed = document.querySelector("#red");
const blueLed = document.querySelector("#blue");
const yellowLed = document.querySelector("#yellow");

function toggleLed(id, element){
    console.log(`${id}: New state selected: ` + element.value);
    $.get("/?value=" + element.value + "&");
    {Connection: close};
    element.value = element.value == "on" ? "off" : "on";
}

//==============================================================================================

// RGB LED

const RGBselect = document.querySelector("#RGBselector");

function rgbLEDchange(id, element){
    console.log(`${id}: New color selected: ` + element.value);
    $.get("/?value=" + element.value + "&");
    {Connection: close};
}

//==============================================================================================

// SERVO MOTOR

var slider = document.getElementById("servoSlider");
var servoP = document.getElementById("servoPos");
servoP.innerHTML = slider.value;

function servo(pos) {
    $.get("/?value=" + pos + "&");
    {Connection: close};
}

slider.oninput = function() {
    slider.value = this.value;
    servoP.innerHTML = this.value;
}

//===============================================================================================

// PIEZO

const playBtn = document.querySelector("#playButton");
const songSelector = document.querySelector("#song-select");

function songSelection(id){
    console.log(`${id}: New song selected`);
    $.get("/?value=" + songSelector.value + "&");
    {Connection: close};
}

//===============================================================================================

// ULTRASONIC SENSOR

const ultrasonicBox = document.querySelector("#ultrasonicBox");

setInterval(function() {
    $.get("/?value=ultrasonic&", function() {
        console.log(1);
        ultrasonicBox.innerHTML = 1 + " cm";
    });
    {Connection: close};
}, 1000);

//===============================================================================================