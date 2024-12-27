/*****************************************************************************
* | File      	:   Demo_dop_manip+module.c
* | Author      :   AVANTI TEAM
* | Function    :
* | Info        :
*----------------
* |	This version:   V0.1
* | Date        :   2024-27-11
* | Info        :
******************************************************************************/
#include <Doplib_c.h>

#define pos_1 23
#define pos_2 131
bool flag = TRUE;

#define RGB_RANGE 30

int red = 0;
int grn = 0;
int blu = 0;

typedef struct {
    int r_avg, g_avg, b_avg; // Средние значения
} ColorRange;

// Глобальные диапазоны для цветов
ColorRange red_range, yellow_range, green_range, blue_range;

void arm_move()
{
    move_to(0, 300, 40, 0);
    delay(2000);
    move_to(0, 200, 40, 0);
    delay(2000);
    move_to(0, 200, 30, 0);
    delay(2000);
    air_picker_pick();
    delay(2000);
    move_to(0, 200, 40, 0);
    delay(2000);
    move_to(-190, 200, 40, 0);
    delay(7000);
    move_to(-190, 200, -60, 0);
    delay(2000);
    air_picker_place();
    delay(1000);
    move_to(-190, 200, 0, 0);
    delay(2000);
    air_picker_stop();
    go_home();
}

void magazin(void)
{
    unsigned int angle = pos_1;
    get_servomotor(angle);
    delay(800);
    for(int i = 0; i < 5; i++)
    {
        if (i % 2 == 0)
            angle += 4;
        else
            angle -= 4; 
        get_servomotor(angle);
        delay(250);
    }
    angle = pos_2;
    get_servomotor(angle);
    delay(800);
    for(int i = 0; i < 3; i++)
    {
        if (i % 2 == 0)
            angle += 3;
        else
            angle -= 3; 
        get_servomotor(angle);
        delay(250);
    }
}
void obstacle(void)
{
    conveyor_belt_backward(5000);
    while (get_obstacle_sensor() == 0)
    {
        usleep(100000); // Ожидание появления кубика
    }
    printf("Кубик обнаружен. Уменьшение скорости конвейера...\n");
    conveyor_belt_backward(2000); // Уменьшение скорости
    while (get_obstacle_sensor() == 1)
    {
        usleep(100000); // Ждем, пока датчик потеряет кубик
    }
    conveyor_belt_stop();

}



// Функция 1: Анализ и расчет среднего значения и диапазонов для цветов
void calculate_color_ranges()
{
    // Локальные переменные для подсчета
    int r_sum = 0, g_sum = 0, b_sum = 0, r_count = 0;
    int y_sum = 0, yg_sum = 0, yb_sum = 0, y_count = 0;
    int gr_sum = 0, gg_sum = 0, gb_sum = 0, g_count = 0;
    int br_sum = 0, bg_sum = 0, bb_sum = 0, b_count = 0;

    // Открываем файл color.txt
    FILE *file = fopen("color.txt", "r");
    if (file == NULL) {
        printf("Ошибка открытия файла color.txt\n");
        return;
    }

    char color;
    int r, g, b;

    // Читаем файл и накапливаем значения
    while (fscanf(file, "%c: R=%d, G=%d, B=%d\n", &color, &r, &g, &b) != EOF) {
        switch (color) {
        case 'R': r_sum += r; g_sum += g; b_sum += b; r_count++; break;
        case 'Y': y_sum += r; yg_sum += g; yb_sum += b; y_count++; break;
        case 'G': gr_sum += r; gg_sum += g; gb_sum += b; g_count++; break;
        case 'B': br_sum += r; bg_sum += g; bb_sum += b; b_count++; break;
        }
    }
    fclose(file);

    // Рассчитываем средние значения
    if (r_count > 0) { red_range.r_avg = r_sum / r_count; red_range.g_avg = g_sum / r_count; red_range.b_avg = b_sum / r_count; }
    if (y_count > 0) { yellow_range.r_avg = y_sum / y_count; yellow_range.g_avg = yg_sum / y_count; yellow_range.b_avg = yb_sum / y_count; }
    if (g_count > 0) { green_range.r_avg = gr_sum / g_count; green_range.g_avg = gg_sum / g_count; green_range.b_avg = gb_sum / g_count; }
    if (b_count > 0) { blue_range.r_avg = br_sum / b_count; blue_range.g_avg = bg_sum / b_count; blue_range.b_avg = bb_sum / b_count; }

    printf("Средние значения диапазонов:\n");
    printf("Red: R=%d, G=%d, B=%d\n", red_range.r_avg, red_range.g_avg, red_range.b_avg);
    printf("Yellow: R=%d, G=%d, B=%d\n", yellow_range.r_avg, yellow_range.g_avg, yellow_range.b_avg);
    printf("Green: R=%d, G=%d, B=%d\n", green_range.r_avg, green_range.g_avg, green_range.b_avg);
    printf("Blue: R=%d, G=%d, B=%d\n", blue_range.r_avg, blue_range.g_avg, blue_range.b_avg);
}

// Функция 2: Проверка цвета и включение лампочек
void check_and_handle_color()
{
    while(1)
    {
    // Считывание текущего значения RGB с датчика
    int red = get_color_red_RGB888();
    int green = get_color_green_RGB888();
    int blue = get_color_blue_RGB888();
    printf("\nСчитанные значения с датчика: R=%d, G=%d, B=%d\n", red, green, blue);

    // Сравнение текущих значений с диапазонами цветов
    if ((red >= red_range.r_avg - RGB_RANGE && red <= red_range.r_avg + RGB_RANGE) &&
        (green >= red_range.g_avg - RGB_RANGE && green <= red_range.g_avg + RGB_RANGE) &&
        (blue >= red_range.b_avg - RGB_RANGE && blue <= red_range.b_avg + RGB_RANGE))
    {
        printf("Цвет: Красный (Red)\n");
        light_led(1, 1);
        conveyor_belt_backward(5000);
        delay(5000);
        push_relay(1, 1);
        push_relay(2, 1);
        delay(5000);
        push_relay(1, 0);
        push_relay(2, 0);
        light_led(1, 0);
        conveyor_belt_stop();
        break;
    }
    else if ((red >= yellow_range.r_avg - RGB_RANGE && red <= yellow_range.r_avg + RGB_RANGE) &&
             (green >= yellow_range.g_avg - RGB_RANGE && green <= yellow_range.g_avg + RGB_RANGE) &&
             (blue >= yellow_range.b_avg - RGB_RANGE && blue <= yellow_range.b_avg + RGB_RANGE))
    {
        printf("Цвет: Желтый (Yellow)\n");
        light_led(2, 1);
        light_led(1, 1);
        conveyor_belt_backward(5000);
        delay(5000);
        push_relay(1, 1);
        push_relay(2, 1);
        delay(5000);
        push_relay(1, 0);
        push_relay(2, 0);
        light_led(2, 0);
        light_led(1, 0);
        conveyor_belt_stop();
        break;
    }
    else if ((red >= green_range.r_avg - RGB_RANGE && red <= green_range.r_avg + RGB_RANGE) &&
             (green >= green_range.g_avg - RGB_RANGE && green <= green_range.g_avg + RGB_RANGE) &&
             (blue >= green_range.b_avg - RGB_RANGE && blue <= green_range.b_avg + RGB_RANGE))
    {
        printf("Цвет: Зелёный (Green)\n");
        light_led(2, 1);
        conveyor_belt_backward(5000);
        delay(5000);
        push_relay(1, 1);
        push_relay(2, 1);
        delay(2200);
        push_relay(1, 0);
        push_relay(2, 0);
        delay(3400);
        conveyor_belt_stop();
        move_to(0, 300, 40, 0);
        delay(2000);
        move_to(0, 200, 40, 0);
        delay(2000);
        move_to(0, 200, 30, 0);
        delay(2000);
        air_picker_pick();
        delay(2000);
        move_to(0, 200, 40, 0);
        delay(2000);
        move_to(0, 380, 40, 0);
        delay(7000);
        move_to(0, 380, -60, 0);
        delay(2000);
        air_picker_place();
        delay(1000);
        move_to(0, 380, 0, 0);
        delay(2000);
        air_picker_stop();
        go_home();
        light_led(2, 0);
        break;
    }
    else if ((red >= blue_range.r_avg - RGB_RANGE && red <= blue_range.r_avg + RGB_RANGE) &&
             (green >= blue_range.g_avg - RGB_RANGE && green <= blue_range.g_avg + RGB_RANGE) &&
             (blue >= blue_range.b_avg - RGB_RANGE && blue <= blue_range.b_avg + RGB_RANGE))
    {
        printf("Цвет: Синий (Blue)\n");
        light_led(3, 1);
        conveyor_belt_backward(5000);
        delay(5000);
        push_relay(1, 1);
        push_relay(2, 1);
        delay(2200);
        push_relay(1, 0);
        push_relay(2, 0);
        delay(3400);
        conveyor_belt_stop();
        arm_move();
        light_led(3, 0);
        break;
    }
    else
    {
        conveyor_belt_forward(5000);
        delay(4000);
        obstacle();
        printf("Цвет не определён.\n");
    }

    // Отключение всех лампочек после небольшой задержки
    }
    delay(500);
    light_led(1, 0);
    light_led(2, 0);
    light_led(3, 0);
    air_picker_stop();
    conveyor_belt_stop();
}

int main()
{
    init_lib();
    init_servomotor();
    init_relay(1);
    init_relay(2);
    init_arm();
    init_obstacle_sensor();
    init_color_module();
    init_led(1);
    init_led(2);
    init_led(3);

    calculate_color_ranges();
    go_home();
    set_module_type(2);
    air_picker_stop();

    for(int i = 0; i < 4; i++)
    {
        conveyor_belt_stop();
        magazin();
        obstacle();
        check_and_handle_color();
        delay(1000);
    }
    conveyor_belt_stop();

}

// gcc Demo_dop_manip+module.c -o Demo_dop_manip+module -lwiringPi -lpthread -lm -ldopLibc
// ./Demo_dop_manip+module