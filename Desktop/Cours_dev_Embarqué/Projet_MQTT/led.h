#ifndef LED_H
#define LED_H

// Fonction pour allumer la LED
void led_on();

// Fonction pour éteindre la LED
void led_off();

// Clignotement court (point en morse)
void led_light_short();

// Clignotement long (trait en morse)
void led_light_long();

// Pause entre les lettres
void led_pause_between_letters();

// Pause entre les mots
void led_pause_between_words();

#endif
