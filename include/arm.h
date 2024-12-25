#ifndef	AVANTI_ARM
#define	AVANTI_ARM

#include "Config.h"

#define BAUDRATE B115200
#define BUFFER_SIZE 256
#define DEVICE_PREFIX "/dev/"
#define TIMEOUT_MS 3000


int configure_port(int fd);

int find_and_connect();

void init_arm();

void close_arm(); 

void set_arm_cmd(const char *command);

char *get_arm_response();

void print_arm_responce();

int XY_limit(int x, int y);

int Z_limit (int z);

void go_home();

void set_workorigin();

void go_to_max_poistion();

void set_module_type(int module_type);

void move_to(float x, float y, float z, int feedrate);

void fast_move_to(float x, float y, float z, int feedrate);

void delay_s(int value);

void delay_ms(int value);

void soft_gripper_pick();

void soft_gripper_place();

void soft_gripper_nature();

void soft_gripper_stop();

void air_picker_pick();

void air_picker_place();

void air_picker_nature();

void air_picker_stop();

void laser_on(int value);

void laser_off();

void conveyor_belt_forward(float speed);

void conveyor_belt_backward(float speed);

void conveyor_belt_stop();

void sliding_rail_init();

void rotary_relative_rotate(int angle);

void rotary_absolute_rotate(int angle);

void get_current_position();


#endif //AVANTI_ARM