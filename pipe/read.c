#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    int fd;
    char *myfifo = "/tmp/myfifo";
    char buffer[100];

	printf("等待消息...\n");

    fd = open(myfifo,O_RDONLY);

    read(fd,buffer,sizeof(buffer));

    printf("收到消息: %s",buffer);
    close(fd);

    return 0;
}
