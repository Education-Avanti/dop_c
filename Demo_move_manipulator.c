/*****************************************************************************
* | File      	:   Demo_move_manipulator.c
* | Author      :   AVANTI TEAM
* | Function    :
* | Info        :
*----------------
* |	This version:   V0.1
* | Date        :   2024-27-11
* | Info        :
******************************************************************************/
#include "include/Union.h"

// Инициализация программы
void init_program() {
    init_lib();        // Инициализация библиотеки
    init_arm();        // Инициализация манипулятора
    init_joystick();   // Инициализация джойстика
    init_button(1);    // Инициализация кнопки 1
    init_button(2);
    init_button(3);    // Инициализация кнопки 2
    printf("Программа успешно инициализирована и подключена к манипулятору\n");
    go_home();         // Отправляем манипулятор в начальное положение
}

int main(void) {
    init_program();

    // Начальные координаты
    int x = 0, y = 300, z = 0;
    int feedrate = 5000; // Скорость движения
    const int sensitivity = 10; // Чувствительность джойстика
    const int deadzone_min = 110, deadzone_max = 140; // Зона мертвой чувствительности
    int air_picker_switched = 0; 

    set_module_type(2);   
     
    air_picker_pick();
    delay_s(5000000);
    air_picker_stop();


    while (1) {
        // Получение значений осей
        int axis_x = get_axis_x();
        int axis_y = get_axis_y();

        // Обработка оси X
        if (axis_x < deadzone_min || axis_x > deadzone_max) {
            if (axis_x > deadzone_max) {x -= sensitivity; // Движение вправо
                if(XY_limit(x,y)) x += sensitivity;
            }
            else if (axis_x < deadzone_min){ x += sensitivity;  // Движение влево
                if(XY_limit(x,y)) x -= sensitivity;} 
            printf("X: %d\n", x);
        }

        // Обработка оси Y
        if (axis_y < deadzone_min || axis_y > deadzone_max) {
            if (axis_y > deadzone_max) {y -= sensitivity; // Движение вверх
                if(XY_limit(x,y))   y+= sensitivity; }
            else if (axis_y < deadzone_min){ y += sensitivity; // Движение вниз
                if(XY_limit(x,y)) y -= sensitivity;}
            printf("Y: %d\n", y);
        }

        // Обработка кнопок для управления осью Z
        if (button_push(1)) {
            z += sensitivity; // Поднять
            if (Z_limit(z)) z -= sensitivity;
            printf("Z: %d\n", z);
        }
        if (button_push(2)) {
            z -= sensitivity; // Опустить
            if (Z_limit(z)) z += sensitivity;
            printf("Z: %d\n", z);
        }
        // Отправка команды движения
        move_to(x, y, z, feedrate);

        if (button_hold(3,5)){air_picker_pick(); air_picker_switched=1;printf("pick");}

        if (button_push(3))  { if(air_picker_switched) air_picker_place(); usleep(500); air_picker_stop(); air_picker_switched=0;printf("stop");}

        // Задержка для предотвращения перегрузки интерфейса
        usleep(300000); // 300 мс
    }

    return 0;
}
