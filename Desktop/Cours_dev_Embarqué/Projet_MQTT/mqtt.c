#include "mqtt.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mosquitto.h>

struct mosquitto *mqtt_client = NULL;

// Callback de connexion
void on_connect(struct mosquitto *mosq, void *obj, int rc) {
    if (rc == 0) {
        printf("Connecté au broker MQTT.\n");
        // S'abonner aux sujets nécessaires
        mosquitto_subscribe(mosq, NULL, MQTT_TOPIC_INPUT, 0);
    } else {
        printf("Erreur de connexion : %d\n", rc);
    }
}

// Callback de réception des messages
void on_message(struct mosquitto *mosq, void *obj, const struct mosquitto_message *msg) {
    if (msg->payloadlen) {
        printf("Message reçu sur le sujet '%s' : %s\n", msg->topic, (char *)msg->payload);

        // Logique pour convertir en Morse (ou autre traitement)
        char morse_output[512];
        convert_to_morse((char *)msg->payload, morse_output, sizeof(morse_output));
        printf("Code Morse : %s\n", morse_output);

        // Publier la réponse en Morse
        mosquitto_publish(mosq, NULL, MQTT_TOPIC_OUTPUT, strlen(morse_output), morse_output, 0, false);
    }
}

// Initialiser MQTT
int mqtt_init(const char *broker_address, int port) {
    // Initialiser la bibliothèque Mosquitto
    mosquitto_lib_init();

    // Créer un client MQTT
    mqtt_client = mosquitto_new(NULL, true, NULL);
    if (!mqtt_client) {
        fprintf(stderr, "Erreur : Impossible de créer un client MQTT.\n");
        return EXIT_FAILURE;
    }

    // Définir les callbacks
    mosquitto_connect_callback_set(mqtt_client, on_connect);
    mosquitto_message_callback_set(mqtt_client, on_message);

    // Connexion au broker
    if (mosquitto_connect(mqtt_client, broker_address, port, 60) != MOSQ_ERR_SUCCESS) {
        fprintf(stderr, "Erreur : Impossible de se connecter au broker MQTT.\n");
        mosquitto_destroy(mqtt_client);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

// Lancer la boucle principale MQTT
void mqtt_loop() {
    if (mosquitto_loop_forever(mqtt_client, -1, 1) != MOSQ_ERR_SUCCESS) {
        fprintf(stderr, "Erreur : Boucle MQTT terminée de manière inattendue.\n");
    }
}

// Nettoyer MQTT
void mqtt_cleanup() {
    mosquitto_disconnect(mqtt_client);
    mosquitto_destroy(mqtt_client);
    mosquitto_lib_cleanup();
}
