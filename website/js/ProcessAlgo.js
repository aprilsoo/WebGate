let localURL = "http://localhost:8080/";
class Process{
    index;
    name;
    arriveTime;
    runTime;
    blockTime;
    blockLength;
    priority;
    status;
    restTime;
    constructor(index,name,arriveTime,runTime,blockTime,blockLength,priority,status,restTime) {
        this.index = index;
        this.name = name;
        this.arriveTime = arriveTime;
        this.runTime = runTime;
        this.blockTime = blockTime;
        this.blockLength = blockLength;
        this.priority = priority;
        this.status = status;
        this.restTime = restTime;
    }
}
let processList = [];
let addDiv = document.querySelector(".p-add");
addDiv.addEventListener("click",createProcess);

function getRandom(min, max) {
    return Math.floor(Math.random()* (max - min + 1)) + min;
}
function createProcess(){
    if (flag)   return;
    let index = processList.length + 1;
    let name = "进程" + index;
    let arriveTime = getRandom(1,10);
    let runTime = getRandom(1,10);
    let blockTime = 0;
    let blockLength = 0;
    let priority = getRandom(1,5);
    let status = "未到达";
    let restTime = runTime;
    let pobj = new Process(index,name,arriveTime,runTime,blockTime,blockLength,priority,status,restTime);
    processList.push(pobj);

    let pdiv = addDiv;
    pdiv.className = "p-panel"
    pdiv.id = index.toString();
    pdiv.innerHTML = processToHTML(pobj);
    pdivEventHandle(pdiv);
    createAddDiv();
}
function processToHTML(p){
    return "<p class=\"p-index\"><span>编号: </span>" + p.index + "</p>\n" +
        "                <p class=\"p-name\"><span>名称: </span>" + p.name + "</p>\n" +
        "                <p class=\"p-arrive\"><span>到达时间: </span>" + p.arriveTime + "</p>\n" +
        "                <p class=\"p-length\"><span>运行时间: </span>" + p.runTime + "</p>\n" +
        "                <p class=\"p-block\"><span>阻塞时间: </span>" + p.blockTime + "</p>\n" +
        "                <p class=\"p-blength\"><span>阻塞时长: </span>" + p.blockLength + "</p>\n" +
        "                <p class=\"p-priority\"><span>优先级: </span>" + p.priority + "</p>\n" +
        "                <p class=\"p-status\"><span>状态: </span>" + p.status + "</p>\n" +
        "                <p class=\"p-rest\"><span>剩余时长: </span>" + p.restTime + "</p>\n" +
        "                <img src=\"img/delete-filling.svg\" alt=\"删除\">\n";
}
function createAddDiv(){
    addDiv = document.createElement("div");
    let pListDiv = document.querySelector(".process");
    pListDiv.appendChild(addDiv);
    addDiv.className = "p-add"
    addDiv.innerHTML = "<img src=\"img/add-circle.svg\" alt=\"添加\">";
    addDiv.addEventListener("click",createProcess);
}
function deleteProcess(e){
    if(flag)    return;
    let pPanel = e.target.parentNode;
    let index = Number(pPanel.querySelector(".p-index").childNodes[1].nodeValue);
    for(let i = index;i < processList.length;i++){
        processList[i].index = i;
        let div = document.getElementById((i + 1).toString());
        div.id = i.toString();
        let divIndex = div.querySelector(".p-index").childNodes[1];
        divIndex.nodeValue = i.toString();
    }
    processList.splice(index - 1,1);
    pPanel.outerHTML = "";
}

function setProcessName(index,name){
    let para = document.getElementById(index).querySelector(".p-name");
    para.innerHTML = "<span>名称: </span>" + name;
    processList[index - 1].name = name;
}
function setProcessArriveTime(index,arriveTime){
    let para = document.getElementById(index).querySelector(".p-arrive");
    para.innerHTML = "<span>到达时间: </span>" + arriveTime;
    processList[index - 1].arriveTime = Number(arriveTime);
}
function setProcessRunTime(index,runTime){
    let para = document.getElementById(index).querySelector(".p-length");
    para.innerHTML = "<span>运行时间: </span>" + runTime;
    processList[index - 1].runTime = Number(runTime);
}
function setProcessBlockTime(index,blockTime){
    let para = document.getElementById(index).querySelector(".p-block");
    para.innerHTML = "<span>阻塞时间: </span>" + blockTime;
    processList[index - 1].blockTime = Number(blockTime);
}
function setProcessBlockLength(index,blockLength){
    let para = document.getElementById(index).querySelector(".p-blength");
    para.innerHTML = "<span>阻塞时长: </span>" + blockLength;
    processList[index - 1].blockLength = Number(blockLength);
}
function setProcessPriority(index,priority){
    let para = document.getElementById(index).querySelector(".p-priority");
    para.innerHTML = "<span>优先级: </span>" + priority;
    processList[index - 1].priority = Number(priority);
}
function setProcessStatus(index,status){
    let para = document.getElementById(index).querySelector(".p-status");
    para.innerHTML = "<span>状态: </span>" + status;
    processList[index - 1].status = status;
}
function setProcessRestTime(index,restTime){
    let para = document.getElementById(index).querySelector(".p-rest");
    para.innerHTML = "<span>剩余时长: </span>" + restTime;
    processList[index - 1].restTime = restTime;
}

function pdivEventHandle(pdiv){
    pdiv.removeEventListener("click",createProcess);
    pdiv.querySelector("img").addEventListener("click",deleteProcess);
    pdiv.querySelector(".p-name").ondblclick = processNameEdit;
    pdiv.querySelector(".p-arrive").ondblclick = processArriveTimeEdit;
    pdiv.querySelector(".p-length").ondblclick = processRunTimeEdit;
    pdiv.querySelector(".p-block").ondblclick = processBlockTimeEdit;
    pdiv.querySelector(".p-blength").ondblclick = processBlockLengthEdit;
    pdiv.querySelector(".p-priority").ondblclick = processPriorityEdit;
}
function processNameEdit(e){
    if (flag)   return;
    if (e.currentTarget.childNodes[1].tagName === "INPUT")   return;
    let pName = e.currentTarget.childNodes[1].nodeValue;
    e.currentTarget.innerHTML = "<span>名称: </span>" + "<input value=\"" + pName + "\">"
    e.currentTarget.querySelector("input").onblur = processNameBlur;
    e.currentTarget.querySelector("input").focus();
}

function processNameBlur(e){
    let val = e.target.value;
    let index = Number(e.target.parentNode.parentNode.id);
    if(val !== ""){
        setProcessName(index,val);
    }
    else{
        setProcessName(index,processList[index - 1].name);
    }
}
function checkDecimal(number){
    if(!isNaN(number)){
         let reg=/^[0-9]{1}\.\d+$/;
         return reg.test(number);
    }
    return false;
}
function processArriveTimeEdit(e){
    if (flag)   return;
    if (e.currentTarget.childNodes[1].tagName === "INPUT")   return;
    let pArriveTime = Number(e.currentTarget.childNodes[1].nodeValue);
    e.currentTarget.innerHTML = "<span>到达时间: </span>" + "<input type='number' min='1' max='50' value=\"" + pArriveTime + "\">"
    e.currentTarget.querySelector("input").onblur = processArriveTimeBlur;
    e.currentTarget.querySelector("input").focus();
}

function processArriveTimeBlur(e){
    let val = e.target.value;
    let index = Number(e.target.parentNode.parentNode.id);
    if(val !== "" && val > 0 && val < 51 && !checkDecimal(val)){
        setProcessArriveTime(index,val);
    }
    else{
        setProcessArriveTime(index,processList[index - 1].arriveTime);
    }
}
function processRunTimeEdit(e){
    if (flag)   return;
    if (e.currentTarget.childNodes[1].tagName === "INPUT")   return;
    let pRunTime = Number(e.currentTarget.childNodes[1].nodeValue);
    e.currentTarget.innerHTML = "<span>运行时间: </span>" + "<input type='number' min='1' max='50' value=\"" + pRunTime + "\">"
    e.currentTarget.querySelector("input").onblur = processRunTimeBlur;
    e.currentTarget.querySelector("input").focus();
}

function processRunTimeBlur(e){
    let val = e.target.value;
    let index = Number(e.target.parentNode.parentNode.id);
    if(val !== "" && val > 0 && val < 51 && !checkDecimal(val)){
        setProcessRunTime(index,val);
        setProcessRestTime(index,val);
    }
    else{
        setProcessRunTime(index,processList[index - 1].runTime);
    }
}
function processBlockTimeEdit(e){
    if (flag)   return;
    if (e.currentTarget.childNodes[1].tagName === "INPUT")   return;
    let pBlockTime = Number(e.currentTarget.childNodes[1].nodeValue);
    e.currentTarget.innerHTML = "<span>阻塞时间: </span>" + "<input type='number' min='1' max='50' value=\"" + pBlockTime + "\">"
    e.currentTarget.querySelector("input").onblur = processBlockTimeBlur;
    e.currentTarget.querySelector("input").focus();
}

function processBlockTimeBlur(e){
    let val = e.target.value;
    let index = Number(e.target.parentNode.parentNode.id);
    if(val !== "" && val >= 0 && val <= processList[index - 1].runTime && !checkDecimal(val)){
        setProcessBlockTime(index,val);
    }
    else{
        setProcessBlockTime(index,processList[index - 1].blockTime);
    }
}
function processBlockLengthEdit(e){
    if (flag)   return;
    if (e.currentTarget.childNodes[1].tagName === "INPUT")   return;
    let pBlockLength = Number(e.currentTarget.childNodes[1].nodeValue);
    e.currentTarget.innerHTML = "<span>阻塞时长: </span>" + "<input type='number' min='1' max='50' value=\"" + pBlockLength + "\">"
    e.currentTarget.querySelector("input").onblur = processBlockLengthBlur;
    e.currentTarget.querySelector("input").focus();
}

function processBlockLengthBlur(e){
    let val = e.target.value;
    let index = Number(e.target.parentNode.parentNode.id);
    if(val !== "" && val >= 0 && val <= 50 && !checkDecimal(val)){
        setProcessBlockLength(index,val);
    }
    else{
        setProcessBlockLength(index,processList[index - 1].blockLength);
    }
}
function processPriorityEdit(e){
    if (flag)   return;
    if (e.currentTarget.childNodes[1].tagName === "INPUT")   return;
    let pPriority = Number(e.currentTarget.childNodes[1].nodeValue);
    e.currentTarget.innerHTML = "<span>优先级: </span>" + "<input type='number' min='1' max='5' value=\"" + pPriority + "\">"
    e.currentTarget.querySelector("input").onblur = processPriorityBlur;
    e.currentTarget.querySelector("input").focus();
}

function processPriorityBlur(e){
    let val = e.target.value;
    let index = Number(e.target.parentNode.parentNode.id);
    if(val !== "" && val > 0 && val <= 5 && !checkDecimal(val)){
        setProcessPriority(index,val);
    }
    else{
        setProcessPriority(index,processList[index - 1].priority);
    }
}

let startButton = document.querySelector(".start");
let resetButton = document.querySelector(".reset");
let readyQueue = document.querySelector(".ready>div");
let blockQueue = document.querySelector(".block>div");
let runningProcess = document.querySelector(".run-process-container");
let log = document.querySelector(".log>div");
let copyList;
startButton.addEventListener("click",startRequest);
resetButton.addEventListener("click",resetRequest);
let flag = false;
let orders = [];
let cpuRunning = false;
let count = 0;
let nowOrder = 0;

function getSmallProcess(index){
    let pdiv = document.createElement("div");
    pdiv.className = "small-process"
    pdiv.innerText = index;
    return pdiv;
}
function readyQueuePush(index){
    let pdiv = getSmallProcess(index);
    readyQueue.appendChild(pdiv);
}
function blockQueuePush(index){
    let pdiv = getSmallProcess(index);
    blockQueue.appendChild(pdiv);
}
function readyQueuePop(index){
    for (let i = 0; i < readyQueue.childNodes.length; i++) {
        let pdiv = readyQueue.childNodes[i];
        if (Number(pdiv.innerText) == index){
            pdiv.outerHTML = "";
        }
    }
}
function blockQueuePop(index){
    for (let i = 0; i < blockQueue.childNodes.length; i++) {
        let pdiv = blockQueue.childNodes[i];
        if (Number(pdiv.innerText) == index){
            pdiv.outerHTML = "";
        }
    }
}

function runningProcessSet(index){
    if (index > processList.length)    return;
    cpuRunning = true;
    let pdiv = runningProcess.querySelector(".run-process");
    let h4 = runningProcess.querySelector("h4");
    pdiv.style.backgroundColor = "orange";
    pdiv.innerText = index;
    h4.innerText = processList[index-1].name + "正在运行,剩余时长" + processList[index-1].restTime;
}
function runningProcessClear(){
    cpuRunning = false;
    let pdiv = runningProcess.querySelector(".run-process");
    let h4 = runningProcess.querySelector("h4");
    pdiv.style.backgroundColor = "gray";
    pdiv.innerText = "";
    h4.innerText = "当前无进程运行";
}
function getP(str){
    let p = document.createElement("p");
    p.innerText = str;
    return p;
}
function handleOrder(order){
    if (order[1] === "Ready"){
        let x = Number(order[2]);
        setProcessStatus(x,"就绪");
        readyQueuePush(x);
        let text = order[0] + ": 进程" + x + "(" + processList[x-1].name + ")" + "就绪";
        log.appendChild(getP(text));
    }
    else if(order[1] === "Block"){
        let x = Number(order[2]);
        setProcessStatus(x,"阻塞");
        blockQueuePush(x);
        runningProcessClear();
        let text = order[0] + ": 进程" + x + "(" + processList[x-1].name + ")" + "阻塞";
        log.appendChild(getP(text));
    }
    else if(order[1] === "BlockEnd"){
        let x = Number(order[2]);
        setProcessStatus(x,"就绪");
        readyQueuePush(x);
        blockQueuePop(x);
        let text = order[0] + ": 进程" + x + "(" + processList[x-1].name + ")" + "阻塞结束";
        log.appendChild(getP(text));
    }
    else if(order[1] === "Run"){
        let x = Number(order[2]);
        setProcessStatus(x,"运行");
        readyQueuePop(x);
        runningProcessSet(x);
        let text = order[0] + ": 进程" + x + "(" + processList[x-1].name + ")" + "运行";
        log.appendChild(getP(text));
    }
    else if(order[1] === "Running"){
        let x = Number(order[2]);
        setProcessRestTime(x,processList[x - 1].restTime - 1);
        runningProcessSet(x);
        let text = order[0] + ": 进程" + x + "(" + processList[x-1].name + ")" + "正在运行,剩余时间" + processList[x-1].restTime;
        log.appendChild(getP(text));
    }
    else if(order[1] === "Finish"){
        let x = Number(order[2]);
        setProcessStatus(x,"结束");
        runningProcessClear();
        let text = order[0] + ": 进程" + x + "(" + processList[x-1].name + ")" + "运行结束";
        log.appendChild(getP(text));
    }
    else if (order[1] === "Exhaust"){
        let x = Number(order[2]);
        setProcessStatus(x,"就绪");
        readyQueuePush(x);
        runningProcessClear();
        let text = order[0] + ": 进程" + x + "(" + processList[x-1].name + ")" + "时间片耗尽";
        log.appendChild(getP(text));
    }
    else{
        console.log("error");
    }
}
let timer;

function orderExecute(){
    if (nowOrder >= orders.length){
        alert("模拟结束")
        clearInterval(timer);
        return;
    }
    count++;
    let order = orders[nowOrder].split(' ');
    while(Number(order[0]) === count){
        handleOrder(order);
        nowOrder++;
        if (nowOrder >= orders.length){
            console.log("break");
            break;
        }
        order = orders[nowOrder].split(' ');
    }
}
function init(){
    cpuRunning = false;
    count = 0;
    nowOrder = 0;
    runningProcessClear();
    blockQueue.innerHTML = "";
    readyQueue.innerHTML = "";
    log.innerHTML = "";
}
function resetRequest(){
    if (flag === false) return;
    clearInterval(timer);
    processList = JSON.parse(copyList);
    console.log(copyList);
    console.log(processList);
    flag = false;
    init();
    let listDiv = document.querySelector(".process");
    listDiv.innerHTML = "<h2>进程列表</h2>";
    createAddDiv();
    for (let i = 0;i < processList.length;i++) {
        let pdiv = addDiv;
        pdiv.className = "p-panel"
        pdiv.id = processList[i].index.toString();
        pdiv.innerHTML = processToHTML(processList[i]);
        pdivEventHandle(pdiv);
        createAddDiv();
    }
}

function startRequest(){
    if (flag === true)   return;
    $.ajax({
        // url:localURL + "os/ProcessService",
        url:"ProcessService",
        method:'POST',
        dataType:'JSON',
        data:{
            "processCount":processList.length,
            "processList":processList,
            "algorithm":document.getElementById("algo-select").value,
        },
        success:function (data){
            alert("模拟开始");
            orders = data;
            copyList = JSON.stringify(processList);
            init();
            timer = setInterval(orderExecute,500);
            flag = true;
        },
        error:function (){
          alert("error")
        }
    })
}