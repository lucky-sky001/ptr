#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	int fd;
	char buffer[100];
	ssize_t bytes_read;

	fd = open("hi.txt",O_RDONLY);

	if(fd == -1) {
		perror("open failed");
		return 1;

	}

	printf("File open successfully for reading\n");

	bytes_read = read(fd,buffer,sizeof(buffer) - 1);

	if(bytes_read == -1) {
		perror("read failed");
		close(fd);
		return 1;
	}

	buffer[bytes_read] = '\0';

	printf("read %ld bytes:%s\n",bytes_read,buffer);

	if(close(fd) == -1) {
		perror("close failed");
		return 1;

	}

	printf("File closed successfully.\n");

	exit(0);
}
