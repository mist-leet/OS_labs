#include<iostream>
#include<pthread.h>
#include<unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

int run()
{
	const char *p1 = "hello";
	const char *p2 = "from";
	const char *p3 = "pr1";
	return  execl("./q1", "./q1",p1, p2,p3, NULL);
}

int main(int args, char **argv)
{
	std::cout << "===program 2 started===" << std::endl;
	
	pid_t pid = fork();
	int status = -2;

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

/*


		

std:: cout << "status of pr1 : " << status << std::endl;
		while (status != 1)
		{
			std:: cout << "status of pr1 : " << status << std::endl;
			waitpid(pid, &status,0);
			usleep(100000);
			
		} 
		std::cout << "program 1 ended with status : " << status << std::endl;

*/