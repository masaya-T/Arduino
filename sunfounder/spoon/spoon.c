#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>
#include <math.h>

#define ServoPin 1 // define the servo to GPIO1

int fd;
int acclX, acclY, acclZ;
int gyroX, gyroY, gyroZ;
double acclX_scaled, acclY_scaled, acclZ_scaled;
double gyroX_scaled, gyroY_scaled, gyroZ_scaled;

// MPU6050から送信されたセンサーデータを読み取る。
int read_word_2c(int addr)
{
    int val;
    val = wiringPiI2CReadReg8(fd, addr);
    val = val << 8;
    val += wiringPiI2CReadReg8(fd, addr + 1);
    printf("%d", val);
    if (val >= 0x8000)
        val = -(65536 - val);
    return val;
}

double dist(double a, double b)
{
    return sqrt((a * a) + (b * b));
}
// Y軸の転向角を取得する。
double get_y_rotation(double x, double y, double z)
{
    double radians;
    radians = atan2(x, dist(y, z));
    return -(radians * (180.0 / M_PI));
}
// x軸の転向角を計算する。
double get_x_rotation(double x, double y, double z)
{
    double radians;
    radians = atan2(y, dist(x, z));
    return (radians * (180.0 / M_PI));
}

long Map(long value, long fromLow, long fromHigh, long toLow, long toHigh)
{
    return (toHigh - toLow) * (value - fromLow) / (fromHigh - fromLow) + toLow;
}

// 角度をサーボに書き込む
void setAngle(int pin, int angle)
{ // Create a funtion to control the angle of the servo.
    if (angle < 0)
        angle = 0;
    if (angle > 180)
        angle = 180;
    softPwmWrite(pin, Map(angle, 0, 180, 5, 25));
}

int servo_motor(void)
{
    int i;
    if (wiringPiSetup() == -1)
    { // when initialize wiring failed,print message to screen
        printf("setup wiringPi failed !");
        return 1;
    }
    softPwmCreate(ServoPin, 0, 200); // initialize PMW pin of servo
    while (1)
    {
        for (i = 0; i < 181; i++)
        { // Let servo rotate from 0 to 180.                  
            // setAngle(ServoPin,i);
            delay(2);
        }
        delay(1000);
        for (i = 181; i > -1; i--)
        { // Let servo rotate from 180 to 0.              
            // setAngle(ServoPin,i);
            delay(2);
        }
        delay(1000);
    }
    return 0;
}
int main()
{
    fd = wiringPiI2CSetup(0x68);
    wiringPiI2CWriteReg8(fd, 0x6B, 0x00); // disable sleep mode
    printf("set 0x6B=%X\n", wiringPiI2CReadReg8(fd, 0x6B));

    while (1)
    {
        // servo_motor();
        // ジャイロセンサーのx軸、y軸、z軸の値を読み取り、メタデータを角速度値に変換してから出力する
        gyroX = read_word_2c(0x43);
        gyroY = read_word_2c(0x45);
        gyroZ = read_word_2c(0x47);

        gyroX_scaled = gyroX / 131.0;
        gyroY_scaled = gyroY / 131.0;
        gyroZ_scaled = gyroZ / 131.0;

        printf("My gyroX_scaled: %f\n", gyroX_scaled);
        delay(100);
        // printf("My gyroY_scaled: %f\n", gyroY_scaled);
        // delay(100);
        // printf("My gyroZ_scaled: %f\n", gyroZ_scaled);
        // delay(100);

        // 加速度センサーのx軸、y軸、z軸の値を読み取り、メタデータを加速速度値（重力単位）に変換してから出力する
        acclX = read_word_2c(0x3B);
        acclY = read_word_2c(0x3D);
        acclZ = read_word_2c(0x3F);

        acclX_scaled = acclX / 16384.0;
        acclY_scaled = acclY / 16384.0;
        acclZ_scaled = acclZ / 16384.0;

        // printf("My acclX_scaled: %f\n", acclX_scaled);
        // delay(100);
        // printf("My acclY_scaled: %f\n", acclY_scaled);
        // delay(100);
        // printf("My acclZ_scaled: %f\n", acclZ_scaled);
        // delay(100);

        // printf("My X rotation: %f\n", get_x_rotation(acclX_scaled, acclY_scaled, acclZ_scaled));
        // delay(100);
        // printf("My Y rotation: %f\n", get_y_rotation(acclX_scaled, acclY_scaled, acclZ_scaled));
        // delay(100);

        delay(100);
    }
    return 0;
}