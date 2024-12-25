#include "include/Union.h"

#define pos_1 23
#define pos_2 131

int x = 0, y = 300, z = 0;
int feedrate = 5000; // Скорость движения
const int sensitivity = 10; // Чувствительность джойстика
const int deadzone_min = 110, deadzone_max = 140; // Зона мертвой чувствительности
int xxx(int axis_x)
{
    if (axis_x < deadzone_min || axis_x > deadzone_max)
        {
            return (1);
        }
    else
        return (0);
}

int yyy(int axis_y)
{
    if (axis_y < deadzone_min || axis_y > deadzone_max)
        {
            return (1);
        }
    else
        return (0);
}

int main()
{
    init_lib();
    init_relay(1);
    init_relay(2);
    init_obstacle_sensor();
    init_led(1);
    init_led(2);
    init_led(3);
    init_joystick();

    while(1)
    {

        light_led(1, button_push(1) || xxx(get_axis_x()) || yyy(get_axis_y()) || get_obstacle_sensor());
        push_relay(1, xxx(get_axis_x()) || yyy(get_axis_y()) || get_obstacle_sensor());
        push_relay(2, xxx(get_axis_x()) || yyy(get_axis_y()) || get_obstacle_sensor());
        light_led(2, button_push(2) || xxx(get_axis_x()) || yyy(get_axis_y()) || get_obstacle_sensor());
        light_led(3, button_push(3) || xxx(get_axis_x()) || yyy(get_axis_y()) || get_obstacle_sensor());
        // printf("x == %d y == %d\n", get_axis_x(), get_axis_y());
        // delay(500);
   
    }

}

//  gcc proverka.c src/*.c -o proverka -lwiringPi -lpthread -lm