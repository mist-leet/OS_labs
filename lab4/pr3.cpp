#include<iostream>
#include<pthread.h>
#include<unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

#define STACK_SIZE 1024 * 1024

int run()
{
	const char *p1 = "hello";
	const char *p2 = "from";
	const char *p3 = "pr1";
	return  execl("./q1", "./q1",p1, p2,p3, NULL);
}

static int runner(void *args)
{
	return run();
}

int main(int args, char **argv)
{
	std::cout << "===program 2 started===" << std::endl;
	
	int status = -2;

	char *stack = new char[STACK_SIZE];
	char *stackTop;

	pid_t pid = clone(runner, stackTop, SIGCHLD, NULL);

	std::cout << "process id : " << pid << std::endl;

	
	if (pid == 0)
	{
		std:: cout << "==child process started==" << std::endl;

		std::cout << "Hello from child process!!!" << std::endl;

		status = run();	
	
		_exit(0);
	}
	else
	{	
		std::cout<<"==parent process started==" << std::endl;
		
		do
		{
			std::cout << "checking for pr1... "  <<  "status : " << status << "\n";
			usleep(5000);
		}		while (waitpid (pid, &status,0)  == 0);
		std::cout <<" pr1 ended with status : " << WEXITSTATUS(status) << std::endl;
		
		std::cout <<"==parent process ended==" << std::endl;
	}
	
	
	std::cout << "===program 2 ended===" << std::endl;

	return 0;
}

// output

/*
ilya@ilya-VirtualBox:~/Документы/pr/pr_labs/labs/lab4$ ./q3
===program 2 started===
process id : 4863
==parent process started==
checking for pr1... status : -2
process id : 0
==child process started==
Hello from child process!!!
===program 1 started===
./q1
hello
from
pr1
===program 1 ended===
 pr1 ended with status : 25
==parent process ended==
===program 2 ended===
ilya@ilya-VirtualBox:~/Д
*/