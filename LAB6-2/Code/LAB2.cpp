#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <cstdlib>

using namespace std;

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
std::string* gpio_get_value(unsigned int gpio)
{
    int fd;
    int set;
    char buf[64];
    snprintf(buf, sizeof(buf),"/sys/class/gpio/gpio%d/value", gpio);
    fd = open(buf, O_RDONLY);
    std::string* isLight;
    read(fd,isLight,set);
    return isLight;
}

int gpio_set_dir(unsigned int gpio, string dirStatus)
{
    int fd;
    char buf[64];

    snprintf(buf, sizeof(buf),"/sys/class/gpio/gpio%d/direction", gpio);

    fd = open(buf, O_WRONLY);
    if (fd < 0 ){
        perror("gpio/direction");
        return fd;
    }

    if (dirStatus == "out")
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
int main(int argc,char *argv[])
{
    gpio_export(396);
    gpio_export(255);
    gpio_export(429);
    gpio_export(427);
    std::string* LED1 = (gpio_get_value(396));
    std::string* LED2 = (gpio_get_value(255));
    std::string* LED3 = (gpio_get_value(429));
    std::string* LED4 = (gpio_get_value(427));
    int gpio;
    if(argc ==  3){
        std::string arg1(argv[1]);
        std::string arg2(argv[2]);
        if(arg1 == "LED1")
        {
            gpio = 396;
            if(arg2 == "on")*LED1 = "1";
            else *LED1 = "0";
        }
        if (arg1 == "LED2")
        {
            gpio = 255;
            if(arg2 == "on")*LED2 = "1";
            else *LED2 = "0";
        }
        if (arg1 == "LED3")
        {
            gpio = 429;
            if(arg2 == "on")*LED3 = "1";
            else *LED3 = "0";
        }
        if (arg1 == "LED4")
        {
            gpio = 427;
            if(arg2 == "on")*LED4 = "1";
            else *LED4 = "0";
        }
        if (arg2 == "on"){
            gpio_set_dir(gpio,"out");
            gpio_set_value(gpio,1);
        }
        if (arg2 == "off"){
            gpio_set_value(gpio,0);
        }
    }
    else {
        std::string isLight;
        std::string arg1(argv[1]);
        if(arg1 == "LED1")isLight = LED1[0];
        if(arg1 == "LED2")isLight = LED2[0];
        if(arg1 == "LED3")isLight = LED3[0];
        if(arg1 == "LED4")isLight = LED4[0];
        printf("%s Status:%s",arg1,isLight);
    }
    return 0;
}
// 7:6 15:14 19:20 23:25