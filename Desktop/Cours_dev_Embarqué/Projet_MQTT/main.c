#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mqtt.h"
#include "morse.h"
#include "led.h"

// Callback appelé lorsque le client MQTT reçoit un message
void on_mqtt_message(const char *topic, const char *message) {
    printf("[MQTT] Nouveau message reçu sur le topic '%s': %s\n", topic, message);

    // Convertir le message en code Morse
    char morse_code[256];
    if (text_to_morse(message, morse_code, sizeof(morse_code)) == 0) {
        printf("[Morse] Code généré: %s\n", morse_code);
        play_morse(morse_code); // Afficher le code Morse avec les LEDs
    } else {
        fprintf(stderr, "[Erreur] Échec de la conversion en code Morse.\n");
    }
}

int main() {
    // Initialisation de la connexion MQTT
    if (mqtt_init("localhost", 1883) != EXIT_SUCCESS) {
        fprintf(stderr, "[Erreur] Échec de la connexion au broker MQTT.\n");
        return EXIT_FAILURE;
    }

    // Souscrire au topic "messages/morse"
    if (mqtt_subscribe("messages/morse") != EXIT_SUCCESS) {
        fprintf(stderr, "[Erreur] Échec de la souscription au topic MQTT.\n");
        mqtt_cleanup();
        return EXIT_FAILURE;
    }

    // Définir la fonction de callback pour les messages reçus
    mqtt_set_message_callback(on_mqtt_message);

    // Démarrer la boucle principale MQTT
    printf("[MQTT] En attente de messages...\n");
    mqtt_loop();

    // Nettoyer les ressources MQTT
    mqtt_cleanup();

    return EXIT_SUCCESS;
}
