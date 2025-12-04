#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int main()
{
    int fd[2];
    pid_t pid;
    char buffer[50];
    const char *message = "hello child";

    if(pipe(fd) == -1) {
        perror("pipe");
        return 1;
    }

    pid = fork();
    if(pid == -1) {
        perror("fork");
        return 1;
    }

    if(pid > 0) {
        close(fd[0]);
        printf("父进程开始写入管道...\n");
        write(fd[1],message,strlen(message)+1);
        close(fd[1]);
    }

    if(pid == 0) {
        close(fd[1]);
        printf("子进程正在读管道...\n");
        read(fd[0],buffer,sizeof(buffer));
        printf("子进程收到父进程消息:%s\n",message);
        close(fd[0]);
    }

    return 0;
}
