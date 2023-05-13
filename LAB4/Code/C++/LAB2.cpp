#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <cstdlib>

using namespace std;

int gpio_set_value(unsigned int gpio, int value)
{
    int fd;
    char buf[64];
    snprintf(buf, sizeof(buf), "/sys/class/gpio/gpio%d/value", gpio);
    fd = open(buf, O_WRONLY);
    if (fd < 0)
    {
        perror("gpio/value");
        return fd;
    }
    if (value == 0)
        write(fd, "0", 2);
    if (value == 1)
        write(fd, "1", 2);
    close(fd);
    return 0;
}

int gpio_set_dir(unsigned int gpio, string dirStatus)
{
    int fd;
    char buf[64];

    snprintf(buf, sizeof(buf), "/sys/class/gpio/gpio%d/direction", gpio);

    fd = open(buf, O_WRONLY);
    if (fd < 0)
    {
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

int gpio_export(unsigned int gpio)
{
    int fd, len;
    char buf[64];

    fd = open("/sys/class/gpio/export", O_WRONLY);
    if (fd < 0)
    {
        perror("gpio/export");
        return fd;
    }

    len = snprintf(buf, sizeof(buf), "%d", gpio);
    write(fd, buf, len);
    close(fd);

    return 0;
}

int gpio_unexport(unsigned int gpio)
{
    int fd, len;
    char buf[64];

    fd = open("/sys/class/gpio/unexport", O_WRONLY);
    if (fd < 0)
    {
        perror("gpio/export");
        return fd;
    }

    len = snprintf(buf, sizeof(buf), "%d", gpio);
    write(fd, buf, len);
    close(fd);

    return 0;
}
int main(int argc, char *argv[])
{
    int gpio;
    std::cout << argv[1];
    std::string arg1(argv[1]);
    std::string arg2(argv[2]);
    if (arg1 == "LED1")
    {
        gpio = 396;
    }
    if (arg1 == "LED2")
    {
        gpio = 255;
    }
    if (arg1 == "LED3")
    {
        gpio = 429;
    }
    if (arg1 == "LED4")
    {
        gpio = 427;
    }
    if (arg2 == "on")
    {
        gpio_export(gpio);
        gpio_set_dir(gpio, "out");
        gpio_set_value(gpio, 1);
    }
    if (arg2 == "off")
    {
        gpio_set_value(gpio, 0);
        gpio_unexport(gpio);
    }
    int a = atoi(argv[2]);
    if (arg1 == "Mode_Shine")
    {
        gpio_export(396);
        gpio_export(255);
        gpio_export(429);
        gpio_export(427);
        gpio_set_dir(396, "out");
        gpio_set_dir(255, "out");
        gpio_set_dir(429, "out");
        gpio_set_dir(427, "out");
        for (int i = 0; i < a; i++)
        {

            gpio_set_value(396, 1);
            gpio_set_value(255, 1);
            gpio_set_value(429, 0);
            gpio_set_value(427, 0);
            sleep(1);
            gpio_set_value(396, 0);
            gpio_set_value(255, 0);
            gpio_set_value(429, 1);
            gpio_set_value(427, 1);
            sleep(1);
        }
        gpio_unexport(396);
        gpio_unexport(255);
        gpio_unexport(429);
        gpio_unexport(427);
    }
    return 0;
}
// 7:6 15:14 19:20 23:25