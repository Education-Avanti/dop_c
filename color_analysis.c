/*****************************************************************************
* | File      	:   Color_analisis.c
* | Author      :   AVANTI TEAM
* | Function    :
* | Info        :
*----------------
* |	This version:   V0.1
* | Date        :   2024-27-11
* | Info        :
******************************************************************************/
#include "include/Union.h"

#define pos_1 23
#define pos_2 131

void write_color_data(FILE *file, const char *color_name, int red, int green, int blue) {
    fprintf(file, "%s: R=%d, G=%d, B=%d\n", color_name, red, green, blue);
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

int main()
{
    init_lib();
    init_color_module();
    init_arm();
    init_obstacle_sensor();
    init_servomotor();

     // Проверка и подготовка файла color.txt
    FILE *file = fopen("color.txt", "w");
    if (file == NULL) {
        perror("Не удалось открыть файл");
        return 1;
    }

    // Массив имен цветов для терминальных сообщений
    const char *color_names[] = {"Y", "G", "B", "R"};
    const int num_colors = 4;

    // Основной цикл по всем цветам
    for (int color_idx = 0; color_idx < num_colors; ++color_idx) {
        for (int instance = 1; instance <= 3; ++instance) {
            if (instance == 1) {
                // Подача нового кубика из магазина
                printf("Подача нового кубика из магазина...\n");
                magazin();
                usleep(500000); // Задержка для падения кубика

                // Включение конвейера для подачи кубика к датчику
                printf("Конвейер движется вперед с полной скоростью...\n");
                conveyor_belt_backward(5000);

                // Снижение скорости и остановка при потере кубика из поля зрения
                while (get_obstacle_sensor() == 0) {
                    usleep(100000); // Ожидание появления кубика
                }

                printf("Кубик обнаружен. Уменьшение скорости конвейера...\n");
                conveyor_belt_backward(2000); // Уменьшение скорости

                while (get_obstacle_sensor() == 1) {
                    usleep(100000); // Ждем, пока датчик потеряет кубик
                }

                conveyor_belt_stop();
                printf("Кубик остановлен под датчиком.\n");
            }

            // Анализ кубика
            int red = get_color_red_RGB888();
            int green = get_color_green_RGB888();
            int blue = get_color_blue_RGB888();
            printf("Кубик %s (итерация %d) распознан: R=%d, G=%d, B=%d.\n", 
                   color_names[color_idx], instance, red, green, blue);

            // Запись данных в файл
            write_color_data(file, color_names[color_idx], red, green, blue);

            // Для повторного анализа (2-я и 3-я итерации)
            if (instance < 3) {
                printf("Отъезд кубика в обратную сторону для повторного анализа...\n");
                conveyor_belt_forward(5000); // Движение кубика в обратную сторону
                usleep(2000000); // Задержка для отъезда

                printf("Возвращение кубика для повторного анализа...\n");
                conveyor_belt_backward(2000); // Возвращение кубика на место

                while (get_obstacle_sensor() == 0) {
                    usleep(100000); // Ожидание возвращения кубика
                }

                while (get_obstacle_sensor() == 1) {
                    conveyor_belt_backward(2000); // Точная остановка на датчике
                    usleep(500000);
                }

                conveyor_belt_stop();
                printf("Кубик вернулся под датчик. Конвейер остановлен.\n");
            } else {
                // После третьей итерации убрать кубик с конвейера
                printf("Удаление кубика с конвейера после завершения анализа...\n");
                conveyor_belt_backward(2000); // Движение кубика с конвейера
                usleep(2000000); // Задержка для съезда кубика
                conveyor_belt_stop();
                printf("Кубик съехал с конвейера.\n");
            }
        }
    }

    printf("Все данные сохранены в color.txt\n");

    // Закрытие файла
    fclose(file);
    return 0;
}

//  gcc color_analysis.c src/*.c -o color_analysis -lwiringPi -lpthread -lm