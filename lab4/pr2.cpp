#include<iostream>
#include<pthread.h>
#include<unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int args, char **argv)
{
	std::cout << "===program 2 started===" << std::endl;
	
	pid_t pid = fork();
	int status = -1;

	std::cout << "process id : " << pid << std::endl;

	
	if (pid == 0)
	{
		std:: cout << "child" << std::endl;

		char *params = "PAR1 PAR2 PAR3 PAR4 PAR5";
		//execl("q1", params, NULL);

		while (status != 0)
		{
			std:: cout << "chekc";
			waitpid(pid, &status,0);
			
		} 
		std::cout << "program 1 ended with status : " << status << std::endl;
	}
	else
	{	
		std::cout<<"parent" << std::endl;
	}

	std::cout << "===program 2 ended===" << std::endl;

	return 0;
}
