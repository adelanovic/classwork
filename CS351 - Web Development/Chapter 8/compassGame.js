//Swap right with bottom
function swapBottom(){
    let temp;
    temp = document.getElementById("bottom-value").innerHTML;
    document.getElementById("bottom-value").innerHTML = document.getElementById("right-value").innerHTML;
    document.getElementById("right-value").innerHTML = temp;
}

//Swap left with right
function swapMiddle() {
    let temp;
    temp = document.getElementById("left-value").innerHTML;
    document.getElementById("left-value").innerHTML = document.getElementById("right-value").innerHTML;
    document.getElementById("right-value").innerHTML = temp;
}

//Swap top with left
function swapTop() {
    let temp;
    temp = document.getElementById("top-value").innerHTML;
    document.getElementById("top-value").innerHTML = document.getElementById("left-value").innerHTML;
    document.getElementById("left-value").innerHTML = temp;
}

//Restart Button
function restartGame(){
    document.getElementById("top").disabled = false;
    document.getElementById("left").disabled = false;
    document.getElementById("right").disabled = false;
    document.getElementById("bottom").disabled = false;
    document.getElementById("update").disabled = false;
    document.getElementById("top-value").innerHTML = " ";
    document.getElementById("left-value").innerHTML = " ";
    document.getElementById("right-value").innerHTML = " ";
    document.getElementById("bottom-value").innerHTML = " ";
}

//Update Button
function updateGame() {
    document.getElementById("top-value").innerHTML = document.getElementById("top").value;
    document.getElementById("left-value").innerHTML = document.getElementById("left").value;
    document.getElementById("right-value").innerHTML = document.getElementById("right").value;
    document.getElementById("bottom-value").innerHTML = document.getElementById("bottom").value;
    document.getElementById("top").disabled = true;
    document.getElementById("left").disabled = true;
    document.getElementById("right").disabled = true;
    document.getElementById("bottom").disabled = true;
    document.getElementById("update").disabled = true;
}

//Extra credit function
function shuffleButton(){
    var directions = ['S', 'E', 'W', 'N'];
    var i = directions.length;
    var temp;
    var randomIndex;


    while(0 !== i) {
        randomIndex = Math.floor(Math.random() * i);
        i -= 1;
        temp = directions[i];
        directions[i] = directions[randomIndex];
        directions[randomIndex] = temp;
    }
    placeValues(directions);

}

function placeValues(directions){
    document.getElementById("top-value").innerHTML = directions[0];
    document.getElementById("left-value").innerHTML = directions[1];
    document.getElementById("right-value").innerHTML = directions[2];
    document.getElementById("bottom-value").innerHTML = directions[3]
}