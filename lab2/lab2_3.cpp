#include<iostream>
#include<pthread.h>
#include<unistd.h>

using namespace std;

pthread_mutex_t mutex;

void* echo_1(void *args)
{
	cout << "first thread started \n" << flush;
    timespec timeoutTime;
    clock_gettime(CLOCK_REALTIME, &timeoutTime);
    timeoutTime.tv_sec += 1;
	
	int retVal = pthread_mutex_timedlock(&mutex, &timeoutTime);

	for(int i = 0; i < 100; i++)
		{
			cout << "1" << flush;
			usleep(100);
		}

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
    timespec timeoutTime;
    clock_gettime(CLOCK_REALTIME, &timeoutTime);
    timeoutTime.tv_sec += 1;
	
	int retVal = pthread_mutex_timedlock(&mutex, &timeoutTime);

	for(int i = 0; i < 100; i++)
		{
			cout << "2" << flush;
			usleep(100);
		}
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

ilya@ilya-VirtualBox:~/Документы/pr/pr_labs/labs/lab2$ ./l3
first thread started 
1second thread started 
111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111
2222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222
first thread ended with code : ok
second thread ended with code : ok
0
Main ended 


/*
