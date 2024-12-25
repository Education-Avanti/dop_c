/*****************************************************************************
* | File      	:   Arm.c
* | Author      :   AVANTI TEAM
* | Function    :
* | Info        :
*----------------
* |	This version:   V0.1
* | Date        :   2024-27-11
* | Info        :
******************************************************************************/

#include "../include/Arm.h"

int serial_port = 0; // Глобальный дескриптор порта

// Обработчик сигнала для завершения программы
void handle_signal(int signo) {
    if (serial_port > 0) {
        close(serial_port);
        printf("\nСоединение с DexArm закрыто.\n");
    }

    if (signo == SIGINT) {
        printf("Программа завершена (Ctrl+C).\n");
        exit(0);
    }

    if (signo == SIGTSTP) {
        printf("Программа завершена (Ctrl+Z).\n");
        exit(0);
    }
}

void handle_continue(int signo) {
    if (serial_port > 0) {
        printf("Возобновление работы программы. Переподключение к DexArm...\n");
        configure_port(serial_port);
    }
}

// Функция для настройки последовательного порта
int configure_port(int fd) {
    struct termios options;
    tcgetattr(fd, &options);
    cfsetispeed(&options, BAUDRATE);
    cfsetospeed(&options, BAUDRATE);
    options.c_cflag |= (CLOCAL | CREAD);  // Включаем прием и локальное соединение
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;              // 8 бит данных
    options.c_cflag &= ~PARENB;          // Без проверки четности
    options.c_cflag &= ~CSTOPB;          // 1 стоп-бит
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // Отключение канонического ввода
    options.c_iflag &= ~(IXON | IXOFF | IXANY);         // Отключение управления потоком
    options.c_oflag &= ~OPOST;                         // Без постобработки вывода
    tcsetattr(fd, TCSANOW, &options);
    return 0;
}

// Функция для поиска и подключения к порту DexArm
int find_and_connect() {
    struct dirent *entry;
    DIR *dp = opendir(DEVICE_PREFIX);

    if (dp == NULL) {
        perror("Ошибка открытия каталога /dev");
        return -1;
    }

    char device_path[256];
    int fd;

    while ((entry = readdir(dp))) {
        if (strstr(entry->d_name, "ttyUSB") || strstr(entry->d_name, "ttyACM")) {
            snprintf(device_path, sizeof(device_path), "%s%s", DEVICE_PREFIX, entry->d_name);
            fd = open(device_path, O_RDWR | O_NOCTTY | O_NDELAY);
            if (fd == -1) {
                perror("Ошибка открытия порта");
                continue;
            }

            if (configure_port(fd) == -1) {
                close(fd);
                continue;
            }

            // Тестовая команда
            char test_command[] = "M114\n";
            write(fd, test_command, strlen(test_command));

            // Ожидание ответа
            char response[100];
            usleep(500000); // Небольшая задержка
            int n = read(fd, response, sizeof(response) - 1);
            if (n > 0) {
                response[n] = '\0';
                if (strstr(response, "X:")) { // Проверяем, что ответ валидный
                    printf("Подключено к DexArm на порту: %s\n", device_path);
                    closedir(dp);
                    return fd;
                }
            }
            close(fd);
        }
    }

    closedir(dp);
    printf("DexArm не найден.\n");
    return -1;
}

// Инициализация DexArm
void init_arm() {
    signal(SIGINT, handle_signal);  // Обработчик для Ctrl+C
    signal(SIGTSTP, handle_signal); // Обработчик для Ctrl+Z
    signal(SIGCONT, handle_continue);

    serial_port = find_and_connect();
    if (serial_port == -1) {
        printf("Не удалось подключиться к DexArm.\n");
        exit(1);
    }
    printf("DexArm успешно инициализирован.\n");
}

// Функция для отправки команды
void set_arm_cmd(const char *command) {
    char full_command[strlen(command) + 2];
    snprintf(full_command, sizeof(full_command), "%s\n", command);
    write(serial_port, full_command, strlen(full_command));
}

// Функция для получения ответа от DexArm
char *get_arm_response() {
    char response[256];
    int num_bytes = read(serial_port, response, sizeof(response) - 1);

    if (num_bytes < 0) {
        return strdup("Ошибка при чтении данных\n");
    }
    char *full_response = (char *)malloc(num_bytes + 1);
    if (!full_response) {
        return strdup("Ошибка выделения памяти\n");
    }
    memcpy(full_response, response, num_bytes);
    full_response[num_bytes] = '\0';
    return full_response;
}

// Функция завершения работы
void close_arm() {
    if (serial_port > 0) {
        close(serial_port);
        printf("Соединение с DexArm закрыто.\n");
    }
}

void print_arm_responce()
{
    char response[256];
    int num_bytes = read(serial_port, &response, sizeof(response));

    if (num_bytes < 0) {
        printf("Ошибка при чтении данных\n");
    } else {
        printf("Ответ: %s\n", response);
    }
}

int XY_limit(int x, int y){
    if (((x*x+y*y)>52900)&&((x*x+y*y)<144300)&&(y>0)) 
        return 0;
    else {
        printf("XY limit");
        return 1;
    }
}

int Z_limit (int z){
    if ((z>-126)&&(z<165)) return 0;
    else{
         printf("Z limit");
         return 1;
    }
}

// def XY_limit(self, x,y):
//         if x**2 + y**2 >52900 and x**2 + y**2 < 144300 and y>0:
//             return 0
//         else:
//             print("XY limit")
//             return 1
    
//     def Z_limit(self,z):
//         if z> -126 and z<165:
//             return 0
//         else:
//             print("Z limit")
//             return 1


void go_home()
{
    set_arm_cmd("M1112");
}

void set_workorigin()
{
    set_arm_cmd("G92 X0 Y0 Z0");
}

void go_to_max_poistion()
{
    set_arm_cmd("M1111");
}

void set_module_type(int module_type)
{
    char send_buffer[200];
    snprintf(send_buffer, 200, "M880 P%d", module_type);
    set_arm_cmd(send_buffer);
}

void move_to(float x, float y, float z, int feedrate)
{   
    // if (!XY_limit(x,y)&&!Z_limit(z))
    // {
        char buffer[BUFFER_SIZE];
        bool wait;
        char send_buffer[200];
        snprintf(send_buffer, 200, "G1 F%d X%f Y%f Z%f", feedrate, x, y, z);
        set_arm_cmd(send_buffer);
    // }
}

void fast_move_to(float x, float y, float z, int feedrate)
{
    char send_buffer[200];
    snprintf(send_buffer, 200, "G0 F%d X%f Y%f Z%f", feedrate, x, y, z);
    set_arm_cmd(send_buffer);
}

void delay_s(int value)
{
    char send_buffer[200];
    snprintf(send_buffer, 200, "G4 S%d", value);
    set_arm_cmd(send_buffer);
}

void delay_ms(int value)
{
    char send_buffer[200];
    snprintf(send_buffer, 200, "G4 P%d", value);
    set_arm_cmd(send_buffer);    
}

void soft_gripper_pick()
{
    set_arm_cmd("M1001"); 
}

void soft_gripper_place()
{
    set_arm_cmd("M1000");
}

void soft_gripper_nature()
{
    set_arm_cmd("M1002");
}

void soft_gripper_stop()
{
    set_arm_cmd("M1003");
}

void air_picker_pick()
{
    set_arm_cmd("M1000");
}

void air_picker_place()
{
    set_arm_cmd("M1001");
}

void air_picker_nature()
{
    set_arm_cmd("M1002");
}

void air_picker_stop()
{
    set_arm_cmd("M1003");
}

void laser_on(int value)
{
    char send_buffer[200];
    snprintf(send_buffer, 200, "M3 S%d", value);
    set_arm_cmd(send_buffer);   
}

void laser_off()
{
    set_arm_cmd("M3 S0");
}

void conveyor_belt_forward(float speed)
{
    char send_buffer[200];
    snprintf(send_buffer, 200, "M2012 F%f D0", speed);
    // printf(send_buffer);
    set_arm_cmd(send_buffer); 
}

void conveyor_belt_backward(float speed)
{
    char send_buffer[200];
    snprintf(send_buffer, 200, "M2012 F%f D1", speed);
    // printf(send_buffer);
    set_arm_cmd(send_buffer);
}

void conveyor_belt_stop()
{
    set_arm_cmd("M2013");
}

void sliding_rail_init()
{
    set_arm_cmd("M2005");
}

void rotary_relative_rotate(int angle)
{
    char send_buffer[200];
    snprintf(send_buffer, 200, "M2101 R%d", angle);
    printf(send_buffer);
    set_arm_cmd(send_buffer);
}

void rotary_absolute_rotate(int angle)
{
    char send_buffer[200];
    snprintf(send_buffer, 200, "M2101 P%d", angle);
    printf(send_buffer);
    set_arm_cmd(send_buffer);
}

void get_current_position()
{
    set_arm_cmd("M114");
}