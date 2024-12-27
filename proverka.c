#include <Doplib_c.h>

int main()
{
    init_lib();
    init_relay(1);

    push_relay(1, 1);
    delay(1000);
    push_relay(1, 0);
    delay(1000);
    return 0;
}
// gcc proverka.c -o proverka -lm -lwiringPi -lptrhread -ldopLibc
// ./proverka