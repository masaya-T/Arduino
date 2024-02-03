#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

#define RLEDPIN 0
#define GLEDPIN 1
#define BLEDPIN 2

static void led_init(void);
static void led_color_set(uint8_t r_val, uint8_t g_val, uint8_t b_val);

static void led_init(void)
{
    softPwmCreate(RLEDPIN, 0, 100);
    softPwmCreate(GLEDPIN, 0, 100);
    softPwmCreate(BLEDPIN, 0, 100);
}
static void led_color_set(uint8_t r_val, uint8_t g_val, uint8_t b_val)
{
    softPwmWrite(RLEDPIN, r_val);
    softPwmWrite(GLEDPIN, g_val);
    softPwmWrite(BLEDPIN, b_val);
}

static void my_led_init(void)
{
    pinMode(RLEDPIN, OUTPUT);
    pinMode(GLEDPIN, OUTPUT);
    pinMode(BLEDPIN, OUTPUT);
    digitalWrite(RLEDPIN, 0);
    digitalWrite(GLEDPIN, 0);
    digitalWrite(BLEDPIN, 0);
}

/* value: 0 ~ 255 */
static void pwm(uint8_t value)
{
    uint8_t d, t, p;
}
int main(void)
{
    uint8_t i;
    if (wiringPiSetup() == -1)
    {
        printf("setup faild");
        return 1;
    }

    while (1)
    {
        digitalWrite(GLEDPIN, 0);
        usleep(10000);
        digitalWrite(GLEDPIN, 1);
        usleep(10000);
    }

    return (0);
}