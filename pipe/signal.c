#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int ctrl_count = 0;

void handle_sigint(int sig) {
	if(ctrl_count == 0) {
		printf("\n收到信号,再按ctrl + c 就会退出\n");
		ctrl_count ++;
	} else {
		printf("\n好的,正在退出...\n");
		exit(0);
	}
}

int main()
{
	signal(SIGINT,handle_sigint);

	printf("程序已经启动,PID是: %d\n",getpid());
	printf("请按 ctrl + c 来发送SIGINT信号\n");

	while(1) {
		sleep(1);
	}

	return 0;
}
