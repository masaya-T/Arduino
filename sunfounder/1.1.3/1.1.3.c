#include <wiringPi.h>
#include <stdio.h>
#include <unistd.h>
// LED棒グラフに対応するピン番号割り当て
int pins[10] = {0, 1, 2, 3, 4, 5, 6, 8, 9, 10};
// 奇数番号を点灯する
void oddLedBarGraph(void)
{
    for (int i = 0; i < 5; i++)
    {
        int j;
        j = i * 2;
        digitalWrite(pins[j], HIGH);
        delay(300);
        digitalWrite(pins[j], LOW);
    }
}
// 偶数番号を点灯する
void evenLedBarGraph(void)
{
    for (int i = 0; i < 5; i++)
    {
        int j;
        j = i * 2 + 1;
        digitalWrite(pins[j], HIGH);
        delay(300);
        digitalWrite(pins[j], LOW);
    }
}
// LED棒グラフのLEDを1つずつ点灯させる
void allLedBarGraph(void)
{
    for (int i = 0; i < 10; i++)
    {
        digitalWrite(pins[i], LOW);
        usleep(50000);
        digitalWrite(pins[i], HIGH);
    }
}

int main(void)
{
    if (wiringPiSetup() == -1)
    {
        printf("setup faild");
        return 1;
    }
    for (int i = 0; i < 10; i++)
    {
        pinMode(pins[i], OUTPUT);
        digitalWrite(pins[i], HIGH);
    }

    while (1)
    {
        // oddLedBarGraph();
        // delay(300);
        // evenLedBarGraph();
        // delay(300);
        allLedBarGraph();
        usleep(5000);
    }
    return 0;
}