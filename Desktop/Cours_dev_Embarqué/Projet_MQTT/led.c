#include "led.h"
#include <stdio.h>
#include <unistd.h> // Pour usleep

void led_on() {
    printf("[LED] Allumée\n");
}

void led_off() {
    printf("[LED] Éteinte\n");
}

void led_light_short() {
    led_on();
    usleep(200000); // Pause de 200 ms pour un point
    led_off();
    usleep(200000); // Pause entre les éléments
}

void led_light_long() {
    led_on();
    usleep(600000); // Pause de 600 ms pour un trait
    led_off();
    usleep(200000); // Pause entre les éléments
}

void led_pause_between_letters() {
    usleep(600000); // Pause entre les lettres
}

void led_pause_between_words() {
    usleep(1400000); // Pause entre les mots
}
