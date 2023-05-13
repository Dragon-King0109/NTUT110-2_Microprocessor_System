#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <errno.h>
#include <fcntl.h>

sem_t semaphore;
int counter = 0;

char gpio_get_value(unsigned int gpio)
{
    int fd;
    char buf[64];
    char rd[2];
    snprintf(buf, sizeof(buf),"/sys/class/gpio/gpio%d/value", gpio);
    fd = open(buf, O_RDONLY);
    if (fd < 0){
        perror("gpio/value");
        return fd;
    }
    read(fd,rd,2);
    close(fd);
    return rd[0];
}

int gpio_set_value(unsigned int gpio,int value)
{
    int fd;
    char buf[64];
    snprintf(buf, sizeof(buf),"/sys/class/gpio/gpio%d/value", gpio);
    fd = open(buf, O_WRONLY);
    if (fd < 0){
        perror("gpio/value");
        return fd;
    }
    if (value == 0)
        write(fd, "0" , 2);
    if (value == 1)
        write(fd, "1" , 2);
    close(fd);
    return 0;
}

int gpio_set_dir(unsigned int gpio, int dirStatus)
{
    int fd;
    char buf[64];

    snprintf(buf, sizeof(buf),"/sys/class/gpio/gpio%d/direction", gpio);

    fd = open(buf, O_WRONLY);
    if (fd < 0 ){
        perror("gpio/direction");
        return fd;
    }

    if (dirStatus == 0)
        write(fd, "out", 4);
    else
        write(fd, "in", 3);
    
    close(fd);
    return 0;
}

int gpio_export(unsigned int gpio) {
    int fd, len;
    char buf[64];

    fd = open("/sys/class/gpio/export", O_WRONLY);
    if (fd < 0) {
        perror("gpio/export");
        return fd;
    }
    
    len = snprintf(buf, sizeof(buf), "%d", gpio);
    write(fd, buf, len);
    close(fd);

    return 0;

}


int gpio_unexport(unsigned int gpio) {
    int fd, len;
    char buf[64];

    fd = open("/sys/class/gpio/unexport", O_WRONLY);
    if (fd < 0) {
        perror("gpio/export");
        return fd;
    }

    len = snprintf(buf, sizeof(buf), "%d", gpio);
    write(fd, buf, len);
    close(fd);

    return 0;
} 
int setLed(int argc[])
{
    gpio_export(396);
    gpio_export(255);
    gpio_export(429);
    gpio_export(427);
    gpio_set_dir(396,0);
    gpio_set_dir(255,0);
    gpio_set_dir(429,0);
    gpio_set_dir(427,0);      
    gpio_set_value(396,argc[0]);
    gpio_set_value(255,argc[1]);
    gpio_set_value(429,argc[2]);
    gpio_set_value(427,argc[3]);
    sleep(1);
    printf("status: %d%d%d%d\n", argc[0],argc[1],argc[2],argc[3]);
    printf("GPIO: 396 status: %c\n",gpio_get_value(396));
    printf("GPIO: 255 status: %c\n",gpio_get_value(255));
    printf("GPIO: 429 status: %c\n",gpio_get_value(429));
    printf("GPIO: 427 status: %c\n",gpio_get_value(427));
    return 0;
}


void* child(void* data){
    sem_wait(&semaphore);
    int *count = (int *) data;
    int LED[4];
    LED[0]=count[0];
    LED[1]=count[1];
    LED[2]=count[2];
    LED[3]=count[3];
    int set = count[4];
    printf("counter: 1\n");
    setLed(LED);
    sleep(1);
    
    for(int i = 1; i < set; i++)
    {
        printf("counter: %d\n",i+1);
        for(int j = 0 ; j < 4 ; j++)
        {
            LED[j]=(LED[j]+1)%2;
        }
        setLed(LED);
        sleep(1);
    }
    pthread_exit(NULL);
}

int main(int argc,char *argv[]) {
    sem_init(&semaphore, 0 , 0);
    int input[5];
    input[0]=argv[1][0]-'0';
    input[1]=argv[1][1]-'0';
    input[2]=argv[1][2]-'0';
    input[3]=argv[1][3]-'0';
    input[4]=argv[2][0]-'0';
    //printf("input : %d %d %d %d %d\n",input[0],input[1],input[2],input[3],input[4]);
    pthread_t t;
    pthread_create(&t, NULL, child, (void*) input);
    sem_post(&semaphore);
    sleep(4);

    pthread_join(t,NULL);

    return 0;
}