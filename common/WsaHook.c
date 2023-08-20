#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <linux/input.h>
#include <pthread.h>
#include <time.h>
#include <string.h>
#include <errno.h>

struct timespec ts1, ts2;

int listen_keyboard(const char *dev, int timeout)
{
    int retval;
    fd_set readfds;
    struct timeval tv;
    struct input_event event;

    int fd = open(dev, O_RDONLY);
    if (fd < 0)
    {
        return errno;
    }

    while (1)
    {
        FD_ZERO(&readfds);
        FD_SET(fd, &readfds);
        tv.tv_sec = timeout;
        tv.tv_usec = 0;
        if((retval = select(fd+1, &readfds, NULL, NULL, &tv)) == 1)
        {
            if (read(fd, &event, sizeof(event)) == sizeof(event))
            {
		    clock_gettime(CLOCK_REALTIME, &ts1);
		    return 0;
            } else {
		    return 0;
	    }
        }
        else
        {
            break;
        }
    }

    close(fd);
    return 0;
}

int listen_mice(const char *dev, int timeout)
{
    char buf[256];
    int n_len;

    int retval;
    fd_set readfds;
    struct timeval tv;

    int fd = open(dev, O_RDONLY);

    if (fd < 0)
    {
        return errno;
    }

    while (1)
    {
        FD_ZERO(&readfds);
        FD_SET(fd, &readfds);
        tv.tv_sec = timeout;
        tv.tv_usec = 0;
        if((retval = select(fd+1, &readfds, NULL, NULL, &tv)) == 1)
        {
            if ((n_len = read(fd, buf, sizeof(buf))) > 0)
            {
                if (n_len == 3)
                {
			clock_gettime(CLOCK_REALTIME, &ts1);
			return 0;
                }
            }
        }
        else
        {
            break;
        }
    }

    close(fd);
    return 0;
}

void * mon_key(void *arg)
{
	int ret;
	char *path = (char *)arg;
	while(1) {
		ret = listen_keyboard(path, 3600);
		if (ret != 0) {
			exit(-1);
		}
	}
}

void * mon_mouse(void *arg)
{
	while(1) {
		listen_mice("/dev/input/mice", 3600);
	}
}

int main(int argc, char **argv)
{
    pthread_t id[10];
    int i;
    char apath[100];
    char *bpath[i];
    FILE *fp;

    clock_gettime(CLOCK_REALTIME, &ts1);
    clock_gettime(CLOCK_REALTIME, &ts2);

    fp = popen("ls /dev/input/by-path |grep kbd", "r");
    if (fp == NULL){
	    printf("popen failed\n");
	    return -1;
    }else{
        printf("popen ok");
    }

    i=0;
    while (fgets(apath, sizeof(apath), fp)) {
	    bpath[i] = malloc(200);

	    apath[strlen(apath) - 1] = '\0';
	    sprintf(bpath[i], "/dev/input/by-path/%s", apath);
	    pthread_create(&id[i], NULL, &mon_key, bpath[i]);
	    i++;
    }
    pclose(fp);
    pthread_create(&id[i++], NULL, &mon_mouse, NULL);

    while(1) {
	    sleep(1);
	    clock_gettime(CLOCK_REALTIME, &ts2);
	    printf("idletime %ld\n", ts2.tv_sec - ts1.tv_sec);
    }

    return 0;
}

