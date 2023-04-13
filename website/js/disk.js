var container = document.querySelector('.d-container');

function getRandom(min, max) {
	return Math.floor(Math.random()* (max - min + 1)) + min;
}

function CreateSmallDisk()
{
	var small = document.createElement('div');
	small.className = 'small-disk';
	small.textContent = getRandom(0,255);
	return small;
}

var product = document.getElementById('product');
product.addEventListener("click",ResetDiskQue);

var DiskQue = [55,58,39,18,90,160,150,38,184];
function ResetDiskQue()
{
	container.innerHTML = "";
	var n = getRandom(5,14);
	DiskQue.length = 0;
	for(i = 1;i <= n; ++i)
	{
		var child = CreateSmallDisk();
		DiskQue.push(child.textContent);
		container.appendChild(child);
	}
}

function CreateTR(tid,nextNum,dis)
{
	var tr = document.createElement('tr');
	var left = document.createElement('td');
	var right = document.createElement('td');
	left.textContent = nextNum;
	right.textContent = dis;
	left.className = 'left';
	right.className = 'right';
	tr.appendChild(left);
	tr.appendChild(right);
	tr.id = tid;
	return tr;
}

function Run()
{
	var radios = document.getElementsByName('Radio');
	for(i = 0; i < radios.length; i++)
	{
		if(radios[i].checked)
		{
			var option = radios[i].value;
		}
	}
	TableInit();
	if(option == 1)
	{
		FCFS();
	}
	else if(option == 2)
	{
		SSTF();
	}
	else if(option == 3)
	{
		SCAN();
	}
	else if(option == 4)
	{
		CSCAN();
	}
	Change();
}
var run = document.getElementById('run');
run.addEventListener("click",Run);

var table = document.querySelector('.table');
function TableInit()
{
	table.innerHTML = "<thead><tr><th colspan=\"2\">(从100号磁道开始)</th></tr><tr><th>被访问的下一个磁道号</th><th>移动距离（磁道数）</th></tr></thead><tbody></tbody><tfoot><tr><td id = \"tfoot\" colspan=\"2\">平均寻道长度：</td></tr></tfoot>";
}

var SqQueue = new Array();

function ClearSq()
{
	for(i = 0;i < SqQueue.length;++i)
	{
		anim.removeChild(SqQueue[i]);
	}
	SqQueue.length = 0;
}
function FCFS()
{
	var tbody = document.querySelector('tbody');
	ClearSq();
	for(i = 0;i < DiskQue.length;++i)
	{
		SqQueue.push(createScale(DiskQue[i]));
	}
	for(i = 0;i < DiskQue.length;++i)
	{
		tbody.appendChild(CreateTR("tr"+i,DiskQue[i],""));
	}
}

function SSTF()
{
	var tbody = document.querySelector('tbody');
	ClearSq();
	let last = 100,now;
	var temp = DiskQue.concat();	//复制diskque
	for(i = 0;i < DiskQue.length;++i)
	{
		let mn = 1025;
		for(j = 0;j < temp.length;++j)	//seek 最近的磁道
		{
			if(Math.abs(last - temp[j]) < mn)
			{
				mn = Math.abs(last - temp[j]);
				now = temp[j];
			}
		}
		SqQueue.push(createScale(now));
		last = now;
		for(j = 0;j < temp.length;++j) //删除一个值位last的元素
		{
			if(temp[j] == last)
			{
				temp.splice(j,1);
				break;
			}
		}
	}
	for(i = 0;i < SqQueue.length;++i)
	{
		tbody.appendChild(CreateTR("tr"+i,SqQueue[i].value,""));
	}
}

function SCAN()
{
	var tbody = document.querySelector('tbody');
	ClearSq();
	var temp = DiskQue.concat();
	temp.sort();
	for(i = 0;i < temp.length; ++i)
	{
		if(temp[i] >= 100) SqQueue.push(createScale(temp[i]));
	}
	for(i = temp.length-1;i >= 0; --i)
	{
		if(temp[i] < 100) SqQueue.push(createScale(temp[i]));
	}
	for(i = 0;i < SqQueue.length;++i)
	{
		tbody.appendChild(CreateTR("tr"+i,SqQueue[i].value,""));
	}
}

function CSCAN()
{
	var tbody = document.querySelector('tbody');
	ClearSq();
	var temp = DiskQue.concat();
	temp.sort();
	for(i = 0;i < temp.length; ++i)
	{
		if(temp[i] >= 100) SqQueue.push(createScale(temp[i]));
	}
	for(i = 0;i < temp.length; ++i)
	{
		if(temp[i] < 100) SqQueue.push(createScale(temp[i]));
	}
	for(i = 0;i < SqQueue.length;++i)
	{
		tbody.appendChild(CreateTR("tr"+i,SqQueue[i].value,""));
	}
}
var axis = document.querySelector('.axis');
var anim = document.querySelector('.animation');

function createScale(val)
{
	var scale = document.createElement('div');
	scale.className = 'scale';
	scale.value = val;
	scale.style.left = Math.floor((axis.offsetWidth - 28) * val / 256 - 2) + 'px';
	scale.style.backgroundColor = 'orange';
	anim.appendChild(scale);
	return scale;
}
var timer;
function Change()
{
	clearInterval(timer);
	var arrow = document.querySelector('.arrow');
	var axix = document.querySelector('.axix');
	var scale = createScale(100);
	scale.style.backgroundColor = 'red';
	arrow.style.left = Math.floor((axis.offsetWidth - 28) * 100 / 256 - 22)  + 'px';
	var nextIndex = 0 , counter = 400 , last = 100 , sum = 0;
	timer = setInterval(function(){
		if(nextIndex >= SqQueue.length)
		{
			var td = document.querySelector('#tfoot');
			td.textContent = '平均寻道长度：' + sum;
			clearInterval(timer);
			return;
		}
		if(Math.floor(arrow.offsetLeft) > Math.floor(SqQueue[nextIndex].offsetLeft - 20) )
		{
			arrow.style.left = Math.floor(arrow.offsetLeft) - 1 + 'px';
		}
		else if(Math.floor(arrow.offsetLeft) < Math.floor(SqQueue[nextIndex].offsetLeft - 20))
		{
			arrow.style.left = Math.floor(arrow.offsetLeft) + 1 + 'px';
		}
		else
		{
			if(counter > 0) counter--;
			else
			{
				SqQueue[nextIndex].style.backgroundColor = 'red';
				var td = document.querySelector('#tr'+nextIndex+'>.right');
				td.textContent = Math.abs(last - SqQueue[nextIndex].value);
				sum += parseInt(td.textContent);
				last = SqQueue[nextIndex].value;
				nextIndex++;
				counter = 400;
			}
		}
	},1/1000);
}
