// AJAX

$.ajaxSetup({timeout:1000});

//==============================================================================================

// LEDS

const redLed = document.querySelector("#red");
const blueLed = document.querySelector("#blue");
const yellowLed = document.querySelector("#yellow");

function toggleLed(id, element){
    console.log(`${id}: New state selected: ` + element.value);

    $.ajax({
        type: 'GET',
        dataType:"jsonp",
        url: window.location.href + id + '/' + element.value + '/',
        headers:{
            'Authorization' : 'Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhcHBWZXIiOiIwLjAuMCIsImV4cCI6NDcyNjM4OTEyMiwibG9jYWxlIjoiIiwibWFzdGVyVmVyIjoiIiwicGxhdGZvcm0iOiIiLCJwbGF0Zm9ybVZlciI6IiIsInVzZXJJZCI6IiJ9.QIZbmB5_9Xlap_gDhjETfMI6EAmR15yBtIQkWFWJkrg',
        },
        success: function (data, status, xhr) {
            console.log(id + " " + element.value + " success");
        },
        error: function (jqXhr, textStatus, errorMessage){
            console.log(id + " " + element.value + " error");
        }
    })

    element.value = element.value == "on" ? "off" : "on";
}

//==============================================================================================

// RGB LED

const RGBselect = document.querySelector("#RGBselector");

function rgbLEDchange(id, element){
    console.log(`${id}: New color selected: ` + element.value);
    
    $.ajax({
        type: 'GET',
        url: "/?" + id + "=" + element.value + "&",
        dataType: 'json', // Add the dataType parameter with value 'json'
        success: function () { // Remove unused variables 'data', 'status', and 'xhr'
            console.log(id + " " + element.value + " success");
        },
        error: function () { // Remove unused variables 'jqXhr', 'textStatus', and 'errorMessage'
            console.log(id + " " + element.value + " error");
        }
    });
}

//===============================================================================================

var servoP = document.getElementById("servoPos");
servoP.innerHTML = slider.value;

function servo(pos) {
    $.get("/?servo=" + pos + "&");
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
    $.get("/?song=" + songSelector.value + "&");
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