// Fichier 03_tableaux_chaines.c
// Objectif : tableaux multidimensionnels et chaînes de caractères "à la C" (char*, terminées par \0).
// Compiler : gcc 03_tableaux_chaines.c -o tableaux_chaines && ./tableaux_chaines

#include <stdio.h>
#include <string.h> // fonctions de manipulation de chaînes
#include <stdlib.h> // atoi

int main(void) {
    // --- Tableau de tableaux (matrice) ---
    printf("--- Matrice ---\n");
    int matrice[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    printf("matrice[1][2] = %d\n", matrice[1][2]); // ligne 1, colonne 2 (valeur 6)
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", matrice[i][j]);
        }
        printf("\n");
    }

    // --- Chaînes de caractères en C : PAS de type String natif ! ---
    // Une chaîne C est un tableau de "char" terminé par un caractère spécial '\0' (octet nul).
    printf("\n--- Chaînes de caractères ---\n");
    char message[20] = "Bonjour"; // le compilateur ajoute automatiquement le '\0' final
    printf("Message : %s (longueur affichée par printf, pas stockée)\n", message);
    printf("Longueur réelle (strlen) : %zu\n", strlen(message)); // ne compte PAS le '\0'

    // Un char* peut aussi pointer vers un littéral de chaîne (ne pas le modifier !)
    const char *salutation = "Salut"; // "const" car modifier un littéral est un comportement indéfini
    printf("Salutation (littéral) : %s\n", salutation);

    // --- Fonctions de <string.h> : équivalent des méthodes de String en Java ---
    char destination[50];
    strcpy(destination, message);      // copie message dans destination
    strcat(destination, ", le monde"); // concatène (ATTENTION aux dépassements de buffer !)
    printf("\nAprès strcpy + strcat : %s\n", destination);

    printf("Comparaison strcmp(\"abc\", \"abd\") = %d (négatif car 'c' < 'd')\n", strcmp("abc", "abd"));
    printf("strcmp(message, \"Bonjour\") = %d (0 = égal)\n", strcmp(message, "Bonjour"));

    // Parcourir une chaîne caractère par caractère (jusqu'au '\0')
    printf("\nParcours caractère par caractère : ");
    for (int i = 0; message[i] != '\0'; i++) {
        printf("[%c]", message[i]);
    }
    printf("\n");

    // --- Conversion chaîne <-> nombre ---
    char texte_nombre[] = "42";
    int nombre_converti = atoi(texte_nombre); // atoi = "ASCII to integer" (pas de gestion d'erreur !)
    printf("\n'%s' converti en entier : %d\n", texte_nombre, nombre_converti);

    char buffer[20];
    sprintf(buffer, "%d", 123); // équivalent inverse : nombre -> chaîne
    printf("123 converti en chaîne : \"%s\"\n", buffer);

    // ⚠️ Piège classique : dépassement de tableau (buffer overflow)
    // char petit[5];
    // strcpy(petit, "Ceci est bien trop long"); // écrit AU-DELÀ du tableau -> comportement indéfini,
    //                                            // source n°1 de failles de sécurité en C !

    printf(
        "\nNote : contrairement à un String Java ou Rust, une chaîne C n'a AUCUNE protection\n"
        "intégrée contre les dépassements de mémoire. La rigueur est entièrement laissée au développeur.\n"
    );

    return 0;
}
