const RGBselect = document.querySelector("#RGBselector");

const playBtn = document.querySelector("#playButton");

const songSelector = document.querySelector("#song-select");

function toggleLed(id, element){
    if (element.checked) {
        console.log(`${id}: ON`);
        var xhr = new XMLHttpRequest();
        xhr.onreadystatechange = function () {
            if (this.readyState == 4 && this.status == 200) {
                console.log(this.responseText);
            }
        };
        
        xhr.open("GET", `/${id}/${element.checked ? 'ON' : 'OFF'}`, true);
        xhr.send();
    } else {
        console.log(`${id}: OFF`);
        var xhr = new XMLHttpRequest();
        xhr.open("GET", `/${id}/${element.checked ? 'ON' : 'OFF'}`, true);
        xhr.send();
    }
}

function rgbLEDchange(id, element){
    console.log(`${id}: New color selected: ` + element.value);
    var xhr = new XMLHttpRequest();
    xhr.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            console.log(this.responseText);
        }
    };

    xhr.open("GET", `/${id}/${element.value}`, true);
    xhr.send();
}

function songSelection(id){
    console.log(`${id}: New song selected`);
    var xhr = new XMLHttpRequest();
    xhr.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            console.log(this.responseText);
        }
    };


    xhr.open("GET", `/${id}/${songSelector.value}`, true);
    xhr.send();
}
