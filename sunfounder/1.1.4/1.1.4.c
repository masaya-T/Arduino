#include <wiringPi.h>
#include <stdio.h>
#define SDI 0                       // serial data input
#define RCLK 1                      // memory clock input(STCP)
#define SRCLK 2                     // shift register clock input(SHCP)
unsigned char SegCode[16] = {0x3f,  // 0
                             0x06,  // 1
                             0x5b,  // 2
                             0x4f,  // 3
                             0x66,  // 4
                             0x6d,  // 5
                             0x7d,  // 6
                             0x07,  // 7
                             0x7f,  // 8
                             0x6f,  // 9
                             0x77,  // A
                             0x7c,  // B
                             0x39,  // C
                             0x5e,  // D
                             0x79,  // E
                             0x71}; // F

void init(void)
{
    pinMode(SDI, OUTPUT);
    pinMode(RCLK, OUTPUT);
    pinMode(SRCLK, OUTPUT);
    digitalWrite(SDI, 0);
    digitalWrite(RCLK, 0);
    digitalWrite(SRCLK, 0);
}

void hc595_shift(unsigned char dat)
{
    int i;:
    for (i = 0; i < 8; i++)
    {
        // ビットごとにdatデータをSDI（DS）に割り当てる
        digitalWrite(SDI, 0x80 & (dat << i));
        // 立ち上がりエッジパルスを生成し、DSのdataをシフトレジスタにシフト
        digitalWrite(SRCLK, 1);
        delay(1);
        digitalWrite(SRCLK, 0);
    }
    // 立ち上がりエッジパルスを生成し、データーをシフトレジスタからストレージレジスターにシフト
    digitalWrite(RCLK, 1);
    delay(1);
    digitalWrite(RCLK, 0);
}

int main(void)
{
    int i;
    if (wiringPiSetup() == -1)
    {
        printf("setup wiringPi failed");
        return 1;
    }
    init();
    while (1)
    {
        for (i = 0; i < 16; i++)
        {
            printf("Print %1X on Segment\n", i);
            hc595_shift(SegCode[i]);
            delay(500);
        }
    }
    return 0;
}