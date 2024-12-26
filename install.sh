#!/bin/bash 

# Убедитесь, что передается ссылка на репозиторий
if [ -z "https://github.com/Education-Avanti/dop_c.git" ]; then
  echo "Ошибка: не указана ссылка на репозиторий."
  exit 1
fi

# Скачивание репозитория в директорию Desktop
echo "Скачиваю репозиторий с ссылки https://github.com/Education-Avanti/dop_c.git"
cd /home/admin/Desktop
git clone https://github.com/Education-Avanti/dop_c.git

# Переход в директорию репозитория
cd /home/admin/Desktop/dop_c || { echo "Ошибка: не удалось зайти в директорию dop_c"; exit 1; }

if [ -z "git clone https://github.com/WiringPi/WiringPi.git" ]; then
  echo "Ошибка: не указана ссылка на репозиторий."
  exit 1
fi

echo "Скачиваю репозиторий с ссылки git clone git clone https://github.com/WiringPi/WiringPi.git"
git clone https://github.com/WiringPi/WiringPi.git

# Выполнение устоновки
echo "Запуск установки библиотеки WiringPi"
cd WiringPi
./build
cd ../

echo "Запуск установки дополнительных библиотек..."
make || { echo "Ошибка: make не удалось выполнить."; exit 1; }

# Установка с правами суперпользователя
echo "Запуск sudo make install..."
sudo make install || { echo "Ошибка: не удалось выполнить sudo make install."; exit 1; }

# Удаление лишних файлов
echo "Удаляю лишние файлы..."
rm -rf wiringPi/ include/ src/ Makefile || { echo "Ошибка: не удалось выполнить удаление файлов"; exit 1; }

# Скрипт завершен
echo "Задачи выполнены успешно."
