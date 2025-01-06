#include <stddef.h>
#ifndef MQTT_H
#define MQTT_H

// Constantes MQTT
#define MQTT_TOPIC_INPUT "morse/input"
#define MQTT_TOPIC_OUTPUT "morse/output"

// Fonctions pour gérer MQTT
int mqtt_init(const char *broker_address, int port);
void mqtt_loop();
void mqtt_cleanup();

// Fonction de conversion Morse (doit être définie ailleurs)
void convert_to_morse(const char *input, char *output, size_t output_size);

#endif

