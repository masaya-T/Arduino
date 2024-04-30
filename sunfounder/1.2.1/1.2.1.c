#include <wiringPi.h>
#include <stdio.h>
#include <wiringShift.h>
#include <signal.h>
#include <unistd.h>

#define BeepPin 0
#define FREQUENCY 10
void main(void)
{
    if (wiringPiSetup() == -1)
    {
        printf("setup wiringPi failed !");
        return;
    }
    pinMode(BeepPin, OUTPUT);

    for (int i = 0; i < 100; i++)
    {
        printf("%d\n", i);
        for (int j = 0; j < 1000; j++)
        {
            digitalWrite(BeepPin, LOW);
            usleep(i * 100);
            digitalWrite(BeepPin, HIGH);
            usleep(i * 100);
        }
        usleep(1);
    }
}