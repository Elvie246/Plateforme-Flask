#ifndef MORSE_H
#define MORSE_H

#include <stddef.h>

// Convertit une chaîne de texte en code Morse
// - text : le texte à convertir (entrée)
// - morse : le buffer pour le code Morse résultant (sortie)
// - max_len : la taille maximale du buffer
// Retourne 0 en cas de succès, -1 en cas d'erreur
int text_to_morse(const char *text, char *morse, size_t max_len);

// Joue un message en code Morse (affichage via LEDs)
// - morse : la chaîne contenant le message en code Morse
void play_morse(const char *morse);

#endif // MORSE_H

