#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

pthread_t person[5];
pthread_mutex_t count[5];

void *func(int n)
{
    printf("\nperson % d is thinking.", n);
    pthread_mutex_lock(&count[n]);
    pthread_mutex_lock(&count[(n + 1) % 5]);
    printf("\nperson % d is eating.", n);
    sleep(3);
    pthread_mutex_unlock(&count[n]);
    pthread_mutex_unlock(&count[(n + 1) % 5]);
    printf("\nperson % d Finished eating ", n);
}

int main()
{
    int  k;
    long i;
    void *message;
    for (i = 1; i <= 5; i++)
    {
        k = pthread_mutex_init(&count[i], NULL);
        if (k == -1)
        {
            printf("Failed to initialize the mutex\n");
            exit(1);
        }
    }
    for (i = 1; i <= 5; i++)
    {
        k = pthread_create(&person[i], NULL, (void *)func, (int *)i);
        if (k != 0)
        {
            printf("Error in thread creation.\n");
            exit(1);
        }
    }
    for (i = 1; i <= 5; i++)
    {
        k = pthread_join(person[i], &message);
        if (k != 0)
        {
            printf("Failed to join the thread.\n");
            exit(1);
        }
    }
    for (i = 1; i <= 5; i++)
    {
        k = pthread_mutex_destroy(&count[i]);
        if (k != 0)
        {
            printf("Mutex destroyed.\n");
            exit(1);
        }
    }
    return 0;
}
