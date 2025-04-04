#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

int gv = 0;
pthread_mutex_t mutex_increase;


void *increase_gv(void *ptr)
{
//	pthread_mutex_lock(&mutex_increase);
	int i, j;
	char *text;
	text = (char *) ptr;
	for(i = 0; i < 10; i++){
		pthread_mutex_lock(&mutex_increase);
		printf(" %d - ", gv);
		 printf("- %s - ", text);
		gv ++;
		printf("%d\n ", gv);
		pthread_mutex_unlock(&mutex_increase);
		for (j = 0; j < 500000; j++);
//		usleep(1000000);
		// printf("- %s - ", text);
		// printf("%d\n ", gv);
		// pthread_mutex_unlock(&mutex_increase);
		fflush(stdout);
	}
//	pthread_mutex_unlock(&mutex_increase);
}

int main()
{
	pthread_t thread1, thread2;

	pthread_mutex_init(&mutex_increase, NULL);

	char *str1 = "I am thread 1";
	char *str2 = "I am thread 2";

	int T1ret, T2ret;

	T1ret = pthread_create(&thread1, NULL, increase_gv, (void *) str1);
	T2ret = pthread_create(&thread2, NULL, increase_gv, (void *) str2);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	printf("T1 & T2 return: %d, %d\n", T1ret, T2ret);
	return 0;
}
