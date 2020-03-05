#include<iostream>
#include<pthread.h>
#include<unistd.h>

using namespace std;

pthread_mutex_t mutex;

void* echo_1(void *args)
{
	cout << "first thread started \n" << flush;
    if (pthread_mutex_trylock(&mutex) == 0)
	{
		for(int i = 0; i < 10; i++)
		{
			cout << "1";
			usleep(100);
		}
    }
    else
    	cout << "first thread is blocked\n";
    cout << endl;
    
    pthread_mutex_unlock(&mutex);
    sleep(1);

    string *retcode = new string("ok");
	cout << "first thread ended with code : " << *retcode << "\n" << flush;
	pthread_exit(retcode);
}

void* echo_2(void *args)
{
	cout << "second thread started \n" << flush;
    if (pthread_mutex_trylock(&mutex) == 0)
	{
		for(int i = 0; i < 10; i++)
		{
			cout << "2";
			usleep(100);
		}
	}
	else
    	cout << "second thread is blocked\n";
	cout << endl;
    
    pthread_mutex_unlock(&mutex);
    sleep(1);

	string *retcode = new string("ok");
	cout << "second thread ended with code : " << *retcode << "\n" << flush;
	pthread_exit(retcode);
}

int main()
{
	int first_flag = 0,
	    second_flag = 0;

    pthread_mutex_init(&mutex, NULL);

	pthread_t thread_1;
	pthread_t thread_2;
	
	int status_1 = pthread_create(&thread_1, NULL, echo_1, NULL);
	int status_2 = pthread_create(&thread_2, NULL, echo_2, NULL);

	int status_adr;

	int a;
	cin >> a;

	status_1 = pthread_join(thread_1, (void**)&status_adr);
	status_2 = pthread_join(thread_2, (void**)&status_adr);

    pthread_mutex_destroy(&mutex);

    cout << "Main ended \n" << flush;

	return 0;
}

/*
ilya@ilya-VirtualBox:~/Документы/pr/pr_labs/labs/lab2$ ./l2
first thread started 
1second thread started 
second thread is blocked

111111111
second thread ended with code : ok
first thread ended with code : ok
0
Main ended 
*/