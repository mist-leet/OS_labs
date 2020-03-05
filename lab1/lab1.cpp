#include<iostream>
#include<pthread.h>
#include<unistd.h>

using namespace std;

void* echo_1(void *args)
{
	cout << "first thread started \n" << flush;

	int &flag_adr = *(int*)args;
	while (flag_adr != 1)
		{
			cout << "1" << flush;
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
	while (flag_adr != 1)
		{
			cout << "2" << flush;
			usleep(10000);
		}


	string *retcode = new string("ok");
	cout << "second thread ended with code : " << *retcode << "\n" << flush;
	pthread_exit(retcode);
}

int main()
{
	int first_flag = 0,
		second_flag = 0;

	pthread_t thread_1;
	pthread_t thread_2;
	
	int status_1 = pthread_create(&thread_1, NULL, echo_1, &first_flag);
	int status_2 = pthread_create(&thread_2, NULL, echo_2, &second_flag);

	int status_adr;

	int a;
	cin >> a;

	first_flag = 1;
	second_flag = 1;

	status_1 = pthread_join(thread_1, (void**)&status_adr);
	status_2 = pthread_join(thread_2, (void**)&status_adr);

	cout << "Main ended \n" << flush;

	return 0;
}

/*

ilya@ilya-VirtualBox:~/Документы/pr/pr_labs/labs/lab1$ ./q
first thread started 
1second thread started 
212122121212121212121122112211221122112213122112122112
first thread ended with code : ok
second thread ended with code : ok
Main ended 

*/