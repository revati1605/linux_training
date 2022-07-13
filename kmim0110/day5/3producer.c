/*creadting  a child and parent process using fork and execl by using the shared memory concept and handling it by using posix signals*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>

void producer(int sig);

pid_t pid;
int shmid;
char *msg;

int main()
{
    int ret;
    shmid = shmget(10, 1024, 0666 | IPC_CREAT);
    if (shmid == -1)
    {
        perror("Shared memory error!");
        exit(0);
    }

    pid = fork();
    if (pid == -1)
    {
        perror("fork failed!!");
        exit(0);
    }

    if (pid == 0)
    {
        ret = execl("consumer", "consumer", NULL);
        if (ret < 0)
        {
            perror("Exec failed");
            exit(0);
        }
        if (ret == 0)
        {
            printf("Exec success");

        }
    }
    else
    {
        (void)signal(SIGUSR2, producer);
        printf("writing the data into the fuffer");
        while (1)
        {
            pause();
        }
    }

    return 0;
}

void producer(int sig)
{
    char ch = 'A';
    int x = 0, in = 0;
    msg = shmat(shmid, 0, 0);
    while (x < 26)
    {
        msg[in] = ch;
        in = (in + 1) % 26;
        ch++;
        if (in == 0)
        {
            ch = 'A';
            printf("p:%s\n", msg);
            sleep(1);
        }
        x++;
    }
    shmdt(msg);
    kill(pid, SIGUSR1);
}
