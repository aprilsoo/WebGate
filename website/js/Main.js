$(".circle-process").click(openProcess);
$(".circle-page").click(openPage);
$(".circle-disk").click(openDisk);
let localURL = "http://localhost:9000/os/";
function openProcess(){
    $(location).attr("href","ProcessAlgo.html");
}
function openPage(){
    $(location).attr("href","Page.html");
}
function openDisk(){
    $(location).attr("href","DiskScheduling.html");
}