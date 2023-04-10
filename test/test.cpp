#include<iostream>

#include"../src/tool/Logger.h"



#include"../src/config.h"

#include<unistd.h>

using namespace std;

int main(){
	

	for(int i=1;i<=10;i++){
		sleep(4);
		debug("this is %d%d%d%d",i,i,i,i);
		fatal("this is %d",i);
		std::cout<<i<<std::endl;
	}

	return 0;
}