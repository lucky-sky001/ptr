#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	int fd;
	char *text = "linux ,hi\n";
	ssize_t bytes_written;

	fd = open("hi.txt",O_WRONLY | O_CREAT,0644);

	if(fd == -1) {
		perror("open failed");
		return -1;

	}
	printf("File open successfully.Fd number is %d\n", fd);

	bytes_written = write(fd,text,strlen(text));

	if(bytes_written == -1) {
		perror("write failed");
		close(fd);
		return -1;
	}

	printf("Successfully wote %ld bytes.\n",bytes_written);

	if(close(fd) == -1) {
		perror("close failed");
		return 1;
	}

	printf("File closed successfully.\n");

	exit(0);
}
