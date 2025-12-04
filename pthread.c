#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

int counter = 0;

void *worker_task(void *arg)
{	
	printf("--> 子线程:开始工作!\n");

	for(int i = 0; i < 5; i++) {
		printf("--> 子线程:正在工作...(%d/5)\n", i);
		sleep(1);
	}

	printf("--> 子线程:工作完成了!\n");

	return NULL;
}

int main()
{
	pthread_t my_thread_id;

	printf("主线程:程序开始\n");

	if(pthread_create(&my_thread_id,NULL,worker_task,NULL) != 0){
		fprintf(stderr,"错误:无法创建线程");
		return 1;
	}

	printf("主线程:已经创建子线程,现在做点别的事情");

	for(int i = 1; i <= 3; i++) {
		printf("主线程:正在运行...(%d/3)\n",i);
		sleep(1);
	}

	printf("主线程:正在等待子线程结束...\n");
	if(pthread_join(my_thread_id,NULL) != 0) {
		fprintf(stderr, "错误:无法等待线程\n");
		return 1;
	}

	printf("主线程:子线程已经结束,程序即将退出\n");


	exit(0);
}
