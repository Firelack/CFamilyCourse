// Fichier 02_pointeurs.c
// Objectif : LE concept central de C. Un pointeur est une variable qui contient une ADRESSE mémoire.
// Compiler : gcc 02_pointeurs.c -o pointeurs && ./pointeurs

#include <stdio.h>

void incrementer(int *p);          // prend un pointeur -> peut modifier la variable d'origine
void echanger(int *a, int *b);     // "passage par pointeur" = équivalent du &mut Rust / passage par référence

int main(void) {
    // --- L'opérateur & : "adresse de" ---
    int age = 25;
    int *pointeur_age = &age; // pointeur_age contient l'ADRESSE de age, pas sa valeur

    printf("Valeur de age : %d\n", age);
    printf("Adresse de age (via &age) : %p\n", (void *)&age);
    printf("Contenu de pointeur_age : %p (la même adresse)\n", (void *)pointeur_age);

    // --- L'opérateur * : "déréférencement" (accéder à la valeur pointée) ---
    printf("Valeur pointée par pointeur_age (*pointeur_age) : %d\n", *pointeur_age);

    // Modifier la valeur À TRAVERS le pointeur
    *pointeur_age = 26;
    printf("Après *pointeur_age = 26, age vaut maintenant : %d\n", age);

    // --- Pourquoi c'est utile : passer une variable par pointeur à une fonction ---
    // En C, un paramètre de fonction est TOUJOURS passé par valeur (copie), SAUF si on passe
    // explicitement un pointeur. C'est l'équivalent du "&mut" en Rust / passage par référence en C++.
    printf("\n--- Passage par pointeur ---\n");
    int compteur = 0;
    printf("Avant : compteur = %d\n", compteur);
    incrementer(&compteur); // on passe l'ADRESSE de compteur
    printf("Après incrementer(&compteur) : compteur = %d\n", compteur);

    int a = 1, b = 2;
    printf("\nAvant échange : a = %d, b = %d\n", a, b);
    echanger(&a, &b);
    printf("Après échange : a = %d, b = %d\n", a, b);

    // --- Pointeur NULL : l'équivalent (dangereux) du "null" Java ---
    // Contrairement à Option<T> en Rust, RIEN ne force à vérifier un pointeur avant de l'utiliser.
    int *pointeur_vide = NULL;
    if (pointeur_vide == NULL) {
        printf("\npointeur_vide ne pointe vers rien (NULL), on ne le déréférence pas !\n");
    }
    // *pointeur_vide; // ⚠️ Déréférencer NULL provoque un crash (segmentation fault)

    // --- Arithmétique de pointeurs : un pointeur sur un tableau peut être "déplacé" ---
    printf("\n--- Arithmétique de pointeurs ---\n");
    int tableau[5] = {10, 20, 30, 40, 50};
    int *p = tableau; // le nom d'un tableau "se comporte" comme un pointeur vers son premier élément

    for (int i = 0; i < 5; i++) {
        printf("*(p + %d) = %d  (équivalent de tableau[%d] = %d)\n", i, *(p + i), i, tableau[i]);
    }

    // --- Pointeur vers pointeur (utile mais avancé, juste pour montrer que ça existe) ---
    int valeur = 100;
    int *p1 = &valeur;
    int **p2 = &p1; // p2 pointe vers p1, qui pointe vers valeur
    printf("\nValeur via **p2 : %d\n", **p2);

    printf(
        "\nNote : en C, AUCUNE vérification à la compilation n'empêche un pointeur invalide.\n"
        "C'est tout l'inverse du borrow checker de Rust, qui interdit ces erreurs AVANT l'exécution.\n"
    );

    return 0;
}

void incrementer(int *p) {
    (*p)++; // on incrémente la valeur pointée, pas le pointeur lui-même
}

void echanger(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
