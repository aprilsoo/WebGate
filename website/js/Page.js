let number1 = document.querySelector(".num1");
let number2 = document.querySelector(".num2");
let number3 = document.querySelector(".num3");
let but1 = document.querySelector(".but1");
let but2 = document.querySelector(".but2");
let fifo1 = document.querySelector(".fifo1");
let fifo2 = document.querySelector(".fifo2");
let fifo3 = document.querySelector(".fifo3");
let fifo4 = document.querySelector(".fifo4");

but1.addEventListener("click",xianjin);

but2.addEventListener("click",zuijiu);

function getP(str){
	let p = document.createElement("p");
	p.innerText = str;
	p.style.border="1px solid black";
	return p;
}

let tm = [];
let id = [];

function xianjin(){
	fifo1.innerHTML = "进程编号";
	fifo2.innerHTML = "物理块中页号";
	fifo3.innerHTML = "置换出的页号";
	fifo4.innerHTML = "是否缺页";
	
	for(i=1;i<=number1.value;i++){
		tm[i]=0;
		id[i]="0";
	}
	
	var str = number3.value.split(' ');
	var num=0;
	for(i=0;i<str.length;i++){
		fifo1.appendChild(getP(str[i]));
		var mn = 100000,ok=0;
		for(j=1;j<=number1.value;j++){
			if(tm[j]<mn){
				mn=tm[j];
			}
			if(id[j]==str[i]){
				ok=1;
			}
		}
		if(mn!=0&&ok==0){
			num++;
			fifo4.appendChild(getP("是"));
		}else{
			fifo4.appendChild(getP("否"));
		}
		if(ok==0){
			for(j=1;j<=number1.value;j++){
				if(tm[j]==mn){
					fifo3.appendChild(getP(id[j]));
					id[j]=str[i];
					tm[j]=i+1;
					break;
				}
			}
		}else{
			fifo3.appendChild(getP(0));
		}
		var ss="";
		for(j=1;j<=number1.value;j++){
			if(id[j]=="0"){
				break;
			}
			ss=ss+"\t"+id[j];
		}
		fifo2.appendChild(getP(ss));
	}
	var st = "缺页次数："+num;
	fifo1.appendChild(getP(st));
	var st2 = "缺页率："+num/str.length;
	fifo1.appendChild(getP(st2));
}

function zuijiu(){
	fifo1.innerHTML = "进程编号";
	fifo2.innerHTML = "物理块中页号";
	fifo3.innerHTML = "置换出的页号";
	fifo4.innerHTML = "是否缺页";
	
	for(i=1;i<=number1.value;i++){
		tm[i]=0;
		id[i]="0";
	}
	
	var str = number3.value.split(' ');
	var num=0;
	for(i=0;i<str.length;i++){
		fifo1.appendChild(getP(str[i]));
		var mn = 100000,ok=0;
		for(j=1;j<=number1.value;j++){
			if(tm[j]<mn){
				mn=tm[j];
			}
			if(id[j]==str[i]){
				tm[j]=i+1;
				ok=1;
			}
		}
		if(mn!=0&&ok==0){
			num++;
			fifo4.appendChild(getP("是"));
		}else{
			fifo4.appendChild(getP("否"));
		}
		if(ok==0){
			for(j=1;j<=number1.value;j++){
				if(tm[j]==mn){
					fifo3.appendChild(getP(id[j]));
					id[j]=str[i];
					tm[j]=i+1;
					break;
				}
			}
		}else{
			fifo3.appendChild(getP(0));
		}
		var ss="";
		for(j=1;j<=number1.value;j++){
			if(id[j]=="0"){
				break;
			}
			ss=ss+"\t"+id[j];
		}
		fifo2.appendChild(getP(ss));
	}
	var st = "缺页次数："+num;
	fifo1.appendChild(getP(st));
	var st2 = "缺页率："+num/str.length;
	fifo1.appendChild(getP(st2));
}