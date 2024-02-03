#include <wiringPi.h>
#include <stdio.h>
#include <unistd.h>
#define LEDPIN 0

int main(void)
{
    if (wiringPiSetup() == -1)
    {
        printf("setup faild");
        return 1;
    }
    pinMode(LEDPIN, OUTPUT);
    digitalWrite(LEDPIN, LOW);
    printf("LED ON\n");
    usleep(50000);
    digitalWrite(LEDPIN, HIGH);
    printf("LED OFF\n");
    usleep(50000);

    return (0);
}