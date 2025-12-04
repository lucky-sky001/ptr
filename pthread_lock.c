#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int bank_balance = 1000;
pthread_mutex_t balance_lock;

void *deposit_money(void *arg)
{
	int amount = 500;
	printf("--> 存钱线程: 启动!准备每次存%d 元\n",amount);

	for(int i = 0; i < 5; i++) {		
		pthread_mutex_lock(&balance_lock);

		int current_banlance = bank_balance;
		printf("-->存钱线程:当前余额%d, 准备存入%d...\n",current_banlance,amount);
		current_banlance += amount;
		sleep(1);
		bank_balance = current_banlance;
		printf("-->存钱线程:当前余额%d\n",bank_balance);

		pthread_mutex_unlock(&balance_lock);

		usleep(100000);
	}
	return NULL;
}

void *withdraw_money(void *arg) {
	int amount = 300;
	printf("--> 取钱线程:启动!每次取%d元\n",amount);

	for(int i = 0; i < 5; i++) {
		pthread_mutex_lock(&balance_lock);

		int current_banlance = bank_balance;
		printf("-->取钱线程:当前余额%d, 准备取出%d...\n",current_banlance,amount);
		current_banlance -= amount;
		sleep(1);
		bank_balance = current_banlance;
		printf("-->取钱线程:当前余额%d\n",bank_balance);

		pthread_mutex_unlock(&balance_lock);

		usleep(200000);
	}
	return NULL;
}

int main()
{
	pthread_t depositor_thread, withdrawer_thread;

	if(pthread_mutex_init(&balance_lock,NULL) != 0) {
		fprintf(stderr, "错误:无法初始化互斥锁\n");
		return 1;
	}

	printf("主线程:初始银行余额为%d\n", bank_balance);

	pthread_create(&depositor_thread,NULL,deposit_money,NULL);
	pthread_create(&withdrawer_thread,NULL,withdraw_money,NULL);

	pthread_join(depositor_thread,NULL);
	pthread_join(withdrawer_thread,NULL);

	pthread_mutex_destroy(&balance_lock);

	printf("主线程:所有交易完成,最终银行余额为:%d\n",bank_balance);

	exit(0);
}







