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
    char message[100];

    mkfifo(myfifo,0666);

    printf("准备发送消息...\n");
    printf("请输入: ");

    fgets(message,sizeof(message),stdin);

    fd = open(myfifo,O_WRONLY);

    write(fd,message,strlen(message) + 1);
    close(fd);

    printf("消息发送成功...\n");

    return 0;
}
