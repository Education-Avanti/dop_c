#!/bin/bash

# Установите необходимые пакеты (например, build-essential)
sudo apt-get update
sudo apt-get install -y build-essential

git clone https://github.com/WiringPi/WiringPi.git
cd WiringPi
./build
cd ..

# Создайте директорию для сборки
mkdir -p build
cd build

# Компилируем библиотеку
# gcc -c ../src/my_library.c -o my_library.o
gcc -c ../src/Accel_gyro_lib.c ../src/arm.c ../src/Button_lib.c ../src/Color_module_lib.c ../src/Config.c ../src/DEV_Config.c ../src/Joystick_lib.c ../sr../src/Led_lib.c ../src/Obstacle_lib.c ../src/Relay_lib.c ../src/Servo_lib.c ../src/TCS34725.c -o avanti_arm_lib.o
gcc -shared -o avanti_arm_lib.so avanti_arm_lib.o

# Установите библиотеку в системные директории
sudo cp avanti_arm_lib.so /usr/local/lib/
sudo ldconfig

# Установите заголовочный файл
sudo cp ../include/Union.h /usr/local/include/

echo "Библиотека успешно установлена!"
