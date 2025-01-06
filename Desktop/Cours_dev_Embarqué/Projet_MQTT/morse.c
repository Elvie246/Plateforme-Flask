#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "morse.h"
#include "led.h"

// Dictionnaire de code Morse
static const char *morse_dict[36] = {
    ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",  // A-J
    "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",   // K-T
    "..-", "...-", ".--", "-..-", "-.--", "--..",                         // U-Z
    "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", // 0-7
    "---..", "----."                                                       // 8-9
};

// Fonction pour convertir un caractère en code Morse
static const char* char_to_morse(char c) {
    if (isalpha(c)) {
        return morse_dict[toupper(c) - 'A'];
    } else if (isdigit(c)) {
        return morse_dict[c - '0' + 26];
    } else if (isspace(c)) {
        return " "; // Séparateur pour les mots
    }
    return NULL; // Caractère non pris en charge
}

// Fonction pour convertir une chaîne de texte en code Morse
int text_to_morse(const char *text, char *morse, size_t max_len) {
    size_t pos = 0;

    for (size_t i = 0; text[i] != '\0'; ++i) {
        const char *code = char_to_morse(text[i]);
        if (code == NULL) {
            fprintf(stderr, "[Erreur] Caractère non pris en charge: '%c'\n", text[i]);
            return -1;
        }

        size_t code_len = strlen(code);
        if (pos + code_len + 1 >= max_len) { // +1 pour l'espace ou le \0
            fprintf(stderr, "[Erreur] Longueur du message Morse trop grande.\n");
            return -1;
        }

        strcpy(&morse[pos], code);
        pos += code_len;

        // Ajouter un espace entre les lettres (sauf après le dernier caractère)
        if (text[i + 1] != '\0' && !isspace(text[i])) {
            morse[pos++] = ' ';
        }
    }

    morse[pos] = '\0'; // Terminer la chaîne
    return 0;
}

// Fonction pour afficher un code Morse avec les LEDs
void play_morse(const char *morse) {
    for (size_t i = 0; morse[i] != '\0'; ++i) {
        switch (morse[i]) {
            case '.': // Point : LED courte
                led_light_short();
                break;
            case '-': // Trait : LED longue
                led_light_long();
                break;
            case ' ': // Pause : LED éteinte
                led_light_pause();
                break;
            default:
                fprintf(stderr, "[Erreur] Symbole Morse non pris en charge: '%c'\n", morse[i]);
                break;
        }
    }
}
