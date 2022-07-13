#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
void *producer();
void *consumer();
void pro(int sig);
void con(int sig);
pthread_t pro_thread, con_thread;
char buffer[5];
int main()
{
    int res;
    void *thread_result;
    res = pthread_create(&pro_thread, NULL, producer, NULL);
    if (res != 0)
    {
        perror("Producer thread creation failed");
        exit(0);
    }

    res = pthread_create(&con_thread, NULL, consumer, NULL);
    if (res != 0)
    {
        perror("Consumer thread creation failed");
        exit(0);
    }
    res = pthread_join(pro_thread, &thread_result);
    if (res != 0)
    {
        perror("Producer thread join failed");
        exit(0);
    }
    res = pthread_join(con_thread, &thread_result);
    if (res != 0)
    {
        perror("Consumer thread join failed");
        exit(0);
    }

    return 0;
}

// producer thread
void *producer()
{
    (void)signal(SIGUSR1, pro);
    while (1)
    {
        pause();
    }
    pthread_exit("exit");
}

// consumer thread
void *consumer()
{
    pthread_kill(pro_thread, SIGUSR1);
    (void)signal(SIGUSR2, con);
    while (1)
    {
        pause();
    }
    pthread_exit("exit");
}

// producer signal handler
void pro(int sig)
{
    char ch = 'A';
    int x = 0, in = 0;
    while (x < 5)
    {
        buffer[in] = ch;
        in = (in + 1) % 5;
        ch++;
        if (in == 0)
        {
            ch = 'A';
            printf("p:%s\n", buffer);
        }
        x++;
    }
    pthread_kill(con_thread, SIGUSR2);
}

// consumer signal handler
void con(int sig)
{
    int out = 0;
    char data[5];
    int y = 5;
    while (y > 0)
    {
        data[out] = buffer[out];
        out = (out + 1) % 5;
        if (out == 0)
            printf("\t c:%s\n", data);
        y--;
    }
    pthread_kill(pro_thread, SIGUSR1);
}
