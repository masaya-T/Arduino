#include "stdio.h"
#include "pthread.h"

#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define CAMERA_FD_NAME "dev/video1"

#define BUF_SIZE 50000
void *camera_thread(void *arg)
{
    int camera_fd;
    int buf[BUF_SIZE];
    int i;

    camera_fd = open(CAMERA_FD_NAME, O_RDONLY);
    read(camera_fd, &buf, BUF_SIZE);

    for (i = 0; i < BUF_SIZE; i++)
    {
        printf("%d ", buf[i]);
    }
    printf("thread %d \n", buf[0]);

    return;
}

int main(void)
{
    int ret;
    pthread_t pthread_camera;

    ret = pthread_create(&pthread_camera, NULL, &camera_thread, NULL);
    if (ret == -1)
    {
        perror("pthread_create");
    }

    pthread_join(pthread_camera, NULL);

    return 0;
}