#include<stdio.h>
#include <time.h>
#include <unistd.h>

int main()
{
	const int TARGET_WEEKDAY = 5;
	const int TARGET_HOUR = 18;

	time_t now_timestamp;
	time(&now_timestamp);

	struct tm *now_struct = localtime(&now_timestamp);

	struct tm target_struct = *now_struct;

	int current_weekday = now_struct->tm_wday;
	int days_to_target = TARGET_WEEKDAY - current_weekday;

	if(days_to_target < 0 || (days_to_target == 0 && now_struct->tm_hour >= TARGET_HOUR)) {
		days_to_target += 7;
	}

	target_struct.tm_mday += days_to_target;
	target_struct.tm_hour = TARGET_HOUR;
	target_struct.tm_min = 0;
	target_struct.tm_sec = 0;

	time_t target_timestamp = mktime(&target_struct);

	double remaining_seconds_double = difftime(target_timestamp,now_timestamp);
	long remaining_seconds = (long)remaining_seconds_double;

	if(remaining_seconds <= 0) {
		printf("欢迎来到快乐周末时间 ！！！\n");
		return 0;
	}

	while(remaining_seconds > 0) {
		long days = remaining_seconds / 86400;
		long hours = (remaining_seconds % 86400) / 3600;
		long minutes = (remaining_seconds % 3600) / 60;
		long seconds = remaining_seconds % 60;

		printf("\r距离快乐周末还有:  %ld天 %02ld小时 %02ld分钟 %02ld秒 ", days, hours, minutes, seconds);
		fflush(stdout);

		sleep(1);
		remaining_seconds--;
	}


	return 0;
}







