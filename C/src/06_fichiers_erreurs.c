// Fichier 06_fichiers_erreurs.c
// Objectif : lecture/écriture de fichiers (FILE*), gestion d'erreurs "à la C" (codes retour, errno, assert).
// Compiler : gcc 06_fichiers_erreurs.c -o fichiers_erreurs && ./fichiers_erreurs

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>  // errno : code d'erreur global rempli par les fonctions système
#include <string.h> // strerror : traduit errno en message lisible
#include <assert.h> // assert : vérifie une condition qui DOIT être vraie (sinon plante volontairement)

// --- Gestion d'erreur "à la C" : pas d'exceptions, on renvoie un CODE pour signaler un succès/échec ---
// Convention très répandue : 0 = succès, != 0 = erreur (parfois l'inverse, ça dépend des projets !).
int diviser(int a, int b, int *resultat) {
    if (b == 0) {
        return -1; // code d'erreur : division par zéro
    }
    *resultat = a / b; // le résultat "réel" est renvoyé via un pointeur, pas via "return"
    return 0; // succès
}

int main(void) {
    // --- Écriture dans un fichier ---
    printf("--- Écriture de fichier ---\n");
    FILE *fichier = fopen("notes.txt", "w"); // "w" = write (écrase le fichier s'il existe)
    if (fichier == NULL) {
        // fopen peut échouer (droits, disque plein...) : il FAUT toujours vérifier !
        fprintf(stderr, "Erreur à l'ouverture : %s\n", strerror(errno));
        return 1;
    }
    fprintf(fichier, "Ligne 1 : Bonjour\n");
    fprintf(fichier, "Ligne 2 : %d\n", 42);
    fclose(fichier); // ⚠️ toujours fermer, sinon les données peuvent ne pas être écrites sur le disque
    printf("Fichier 'notes.txt' écrit avec succès\n");

    // --- Lecture d'un fichier ---
    printf("\n--- Lecture de fichier ---\n");
    FILE *lecture = fopen("notes.txt", "r"); // "r" = read
    if (lecture == NULL) {
        fprintf(stderr, "Erreur à l'ouverture : %s\n", strerror(errno));
        return 1;
    }
    char ligne[100];
    while (fgets(ligne, sizeof(ligne), lecture) != NULL) { // lit ligne par ligne jusqu'à la fin
        printf("Lu : %s", ligne); // fgets garde le \n, pas besoin d'en rajouter
    }
    fclose(lecture);

    // --- Tentative d'ouverture d'un fichier inexistant : exemple de gestion d'erreur ---
    printf("\n--- Erreur volontaire ---\n");
    FILE *inexistant = fopen("ce_fichier_n_existe_pas.txt", "r");
    if (inexistant == NULL) {
        printf("Erreur attendue : %s\n", strerror(errno)); // ex: "No such file or directory"
    } else {
        fclose(inexistant);
    }

    // --- Utilisation du code retour + pointeur pour renvoyer un résultat ---
    printf("\n--- Codes retour ---\n");
    int resultat;
    if (diviser(10, 2, &resultat) == 0) {
        printf("10 / 2 = %d\n", resultat);
    } else {
        printf("Erreur : division impossible\n");
    }
    if (diviser(10, 0, &resultat) != 0) {
        printf("Erreur : division par zéro détectée (comme prévu)\n");
    }

    // --- assert : vérifie une condition qui DOIT toujours être vraie (bug de programmation sinon) ---
    // Si la condition est fausse, le programme s'arrête immédiatement avec un message d'erreur.
    // Utile en développement ; souvent désactivé en production (compilation avec -DNDEBUG).
    int age = 25;
    assert(age >= 0); // si jamais age était négatif, ce serait un bug à corriger, pas une erreur "normale"
    printf("\nassert(age >= 0) passé sans problème (age = %d)\n", age);

    printf(
        "\nNote : contrairement à Rust (Result<T, E>) ou Java (exceptions), le code C 'classique'\n"
        "utilise des codes retour + errno. Rien n'oblige à vérifier ces codes : les oublier est\n"
        "une source très fréquente de bugs.\n"
    );

    return 0;
}
