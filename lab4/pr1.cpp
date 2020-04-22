#include<iostream>
#include<pthread.h>
#include<unistd.h>
#include <fcntl.h>


int main(int args, char **argv)
{
	std::cout << "===program 1 started===" << std::endl;
	
	for(int i = 0; i < args; i++)
	{
		for(int j = 0; argv[i][j] != NULL; j++)
			{
				std::cout << argv[i][j] << std::flush;
			}
			usleep(100000);
		std::cout << std::endl;
	}

 	std::cout << "===program 1 ended===" << std::endl;

	exit(25);
}


// output:
/*
ilya@ilya-VirtualBox:~/Документы/pr/pr_labs/labs/lab4$ ./q1 qwe qwe qwe 
===program 1 started===
./q1
qwe
qwe
qwe
===program 1 ended===

*/
