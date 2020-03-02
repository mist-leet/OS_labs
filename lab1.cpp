#include<iostream>
#include<pthread.h>
#include<unistd.h>

using namespace std;

void* echo_1(void *args)
{
	int &flag_adr = *(int*)args;
	while (flag_adr != 1)
		{
			cout << "1 ";
			usleep(10000);
		}
}

void* echo_2(void *args)
{
	int &flag_adr = *(int*)args;
	while (flag_adr != 1)
		{
			cout << "2 ";
			usleep(10000);
		}
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

	cout << a * a;

	first_flag = 1;
	second_flag = 1;

	status_1 = pthread_join(thread_1, (void**)&status_adr);
	status_2 = pthread_join(thread_2, (void**)&status_adr);

	return 0;
}
