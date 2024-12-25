/*****************************************************************************
* | File      	:   Button_lib.c
* | Author      :   AVANTI TEAM
* | Function    :   ПОКА НЕ ПРИДУМАЛ
* | Info        :
*                Надо
*                подумать
*----------------
* |	This version:   V0.1
* | Date        :   2024-27-11
* | Info        :

#
#
#
#
#
#
#                   НАПИСАТЬ ЧТО_ТО УМНОЕ
#
#
#
#
#
******************************************************************************/
#include "../include/Button_lib.h"

// Настройки
#define DEBOUNCE_DELAY 50  // Задержка для устранения дребезга (мс)
unsigned int BUTTON[4] = {0, BUTTON_1, BUTTON_2, BUTTON_3};

unsigned long lastDebounceTime[4] = {0, 0, 0, 0};
unsigned int time_hold_button = 0;
bool buttonState[4] = {false, false, false, false};
bool buttonToggle[4] = {false, false, false, false};

/* Функция антидребезга */
bool debounce(unsigned int num) {
    unsigned long currentTime = millis();
    bool currentState = !digitalRead(BUTTON[num]);

    if (currentState != buttonState[num]) {
        lastDebounceTime[num] = currentTime;
        buttonState[num] = currentState;
    }

    return buttonState[num];
}

/* Функция инициализации кнопки */
void init_button(unsigned int num) {
    if (num >= 1 && num <= 3) {
        pinMode(BUTTON[num], INPUT);
    } else {
        printf(RED"Check the BUTTON device number!"END);
    }
}

/*Функция получения состояния кнопки*/
int button_push(unsigned int num) 
{
    if (num >= 1 && num <= 3)
    {
        return(debounce(num));
    }
    else
    {
        printf(RED"Check the BUTTON device number!"END);
        return(-1);
    }
}

/*Функция получения состояния кнопки по времени*/
int button_hold(unsigned int num, unsigned int holding_time) {
    if (num >= 1 && num <= 3) {
        unsigned long start_time = millis();
        while (debounce(num)) {
            if ((millis() - start_time) >= holding_time) {
                return 1;
            }
        }

        return 0;
    } else {
        printf(RED"Check the BUTTON device number!"END);
        return -1;
    }
}

/* Функция переключения состояния кнопки */
bool button_push_hold(unsigned int num) {
    if (num >= 1 && num <= 3) {
        if (debounce(num)) {
            while (debounce(num)) {
                delay(1);
            }
            buttonToggle[num] = !buttonToggle[num];
        }
        return buttonToggle[num];
    }
    else {
        printf(RED"Check the BUTTON device number!"END);
        return -1;
    }
    return false;
}