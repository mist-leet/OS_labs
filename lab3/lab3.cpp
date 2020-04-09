#include<iostream>
#include<pthread.h>
#include<unistd.h>
#include <fcntl.h>


using namespace std;

 int pipefd[2];

void* echo_1(void *args)
{
	cout << "first thread started \n" << flush;
	int &flag_adr = *(int*)args;

	char buff = 65;

	while (flag_adr != 1)
		{
			write(pipefd[1], &buff, sizeof(buff));
			
			if (buff < 65 + 26 - 1)
				buff++;
			else buff = 65;
			
			cout << buff << flush;
			
			usleep(10000);
		}

	string *retcode = new string("ok");
	cout << "first thread ended with code : " << *retcode << "\n" << flush;
	pthread_exit(retcode);
}

void* echo_2(void *args)
{
	cout << "second thread started \n" << flush;
	int &flag_adr = *(int*)args;

	char buff;

	while (flag_adr != 1)
		{
			read(pipefd[0], &buff, sizeof(buff));

			cout << buff << flush;

			usleep(10000);
		}


	string *retcode = new string("ok");
	cout << "second thread ended with code : " << *retcode << "\n" << flush;
	pthread_exit(retcode);
}

int main()
{
 	int first_flag = 0;
	int second_flag = 0;

 	pipe(pipefd);
 	// pipe2(pipefd, O_NONBLOCK);
 	fcntl(pipefd[0], F_SETFL, O_NONBLOCK);
 	fcntl(pipefd[1], F_SETFL, O_NONBLOCK);

 	pthread_t thread_1;
	pthread_t thread_2;
	
	int status_1 = pthread_create(&thread_1, NULL, echo_1, &first_flag);
	int status_2 = pthread_create(&thread_2, NULL, echo_2, &second_flag);

	int status_adr;

	int a;
	cin >> a;

	first_flag = second_flag = 1;

	status_1 = pthread_join(thread_1, (void**)&status_adr);
	status_2 = pthread_join(thread_2, (void**)&status_adr);

	cout << "Main ended \n" << flush;
	close(pipefd[0]);
	close(pipefd[1]);
	return 0;
}

/*
ilya@ilya-VirtualBox:~/Документы/pr/pr_labs/labs/lab3$ ./q
first thread started 
Bsecond thread started 
ACBDCEDFEFGFHGIJHIKJLKMLNMOPNQOPRSQTR-SUTVUWVXYWZXAYBZACDBCEDFEGFHGIHJIKJLKMLNMONPOQPRQSRTSUTVUWVXWYXZYAZBACDBECFDGEHFIGJHKILJMKLNOM
first thread ended with code : ok
second thread ended with code : ok
Main ended 


*/
