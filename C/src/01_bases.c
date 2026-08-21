// Fichier 01_bases.c
// Objectif : variables, types, opérateurs, structures de contrôle, fonctions.
// Compiler : gcc 01_bases.c -o bases && ./bases

#include <stdio.h>
#include <stdbool.h> // nécessaire pour "bool" en C (pas natif comme en C++/C#/Java)

// --- Déclaration de fonction AVANT main (en C, il faut déclarer avant d'utiliser) ---
int addition(int a, int b);

int main(void) {
    // --- Variables et types de base ---
    // Contrairement à Rust, les variables sont MODIFIABLES par défaut en C.
    // "const" sert à les rendre immuables (l'inverse de Rust où "let" est immuable par défaut).
    int age = 25;
    const int MAX_JOUEURS = 4; // équivalent d'un "final" Java / d'une const Rust
    printf("Age : %d, max joueurs : %d\n", age, MAX_JOUEURS);

    // Types numériques : int, short, long, long long (signés par défaut)
    // unsigned int / unsigned char... pour les versions non signées
    unsigned char petit_nombre = 255; // 0 à 255
    float flottant_simple = 3.14f;    // simple précision (le "f" est important !)
    double flottant_double = 3.14159; // double précision (comme "double" en Java)
    char lettre = 'R';                // UN seul caractère, entre apostrophes
    bool vrai_ou_faux = true;         // nécessite #include <stdbool.h>

    printf("%hhu %.2f %.5f %c %d\n", petit_nombre, flottant_simple, flottant_double, lettre, vrai_ou_faux);

    // --- Tableaux : taille fixe, comme en Rust, mais SANS vérification de limites à l'exécution ! ---
    int nombres[5] = {1, 2, 3, 4, 5};
    int taille = sizeof(nombres) / sizeof(nombres[0]); // pas de .len() en C : calcul manuel !
    printf("\nTaille du tableau : %d\n", taille);

    for (int i = 0; i < taille; i++) {
        printf("nombres[%d] = %d\n", i, nombres[i]);
    }

    // ⚠️ nombres[10] compilerait sans erreur, mais lirait de la mémoire n'importe où
    // (comportement indéfini). En C, RIEN ne vous protège des débordements de tableau.

    // --- Opérateur ternaire (existe en C, contrairement à Rust) ---
    const char *majeur = (age >= 18) ? "majeur" : "mineur"; // condition ? siVrai : siFaux
    printf("\nÀ %d ans, on est %s\n", age, majeur);

    // --- Boucle for ---
    printf("\nBoucle for :\n");
    for (int p = 0; p < 3; p++) {
        printf("Iteration %d\n", p);
    }

    // --- Boucle while ---
    printf("\nBoucle while :\n");
    int compteur = 0;
    while (compteur < 3) {
        printf("Compteur : %d\n", compteur);
        compteur++;
    }

    // --- Boucle do...while (exécute au moins une fois, n'existe pas telle quelle en Rust) ---
    printf("\nBoucle do...while :\n");
    int x = 0;
    do {
        printf("x = %d\n", x);
        x++;
    } while (x < 3);

    // --- switch : comme Java, mais ATTENTION au "fall-through" si on oublie "break" ---
    printf("\nExemple de switch :\n");
    int jour = 2;
    switch (jour) {
        case 1:
            printf("Lundi\n");
            break; // sans ce break, l'exécution continuerait dans le case suivant !
        case 2:
            printf("Mardi\n");
            break;
        case 3:
            printf("Mercredi\n");
            break;
        default:
            printf("Autre jour\n");
    }

    // --- Quelques calculs ---
    printf("\n5 / 2 = %d\n", 5 / 2);       // division entière -> 2 (comme en Java)
    printf("5.0 / 2.0 = %f\n", 5.0 / 2.0); // division flottante -> 2.5
    printf("5 %% 2 = %d\n", 5 % 2);        // %% pour afficher un vrai % avec printf

    int y = 5;
    printf("y++ affiche %d (y devient 6 ensuite)\n", y++); // post-incrémentation
    printf("++y affiche %d (y était 6, incrémenté avant)\n", ++y); // pré-incrémentation

    // --- Fonction ---
    printf("\nSomme de 3 et 4 = %d\n", addition(3, 4));

    return 0; // 0 = succès (convention universelle en C, voir chapitre gestion d'erreurs)
}

// --- Définition de la fonction ---
int addition(int a, int b) {
    return a + b;
}
