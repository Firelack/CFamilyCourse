// Fichier 04_memoire_dynamique.c
// Objectif : malloc/calloc/realloc/free. La gestion mémoire manuelle, ce que Rust automatise
// avec l'ownership et que Java/C# automatisent avec un Garbage Collector.
// Compiler : gcc 04_memoire_dynamique.c -o memoire_dynamique && ./memoire_dynamique

#include <stdio.h>
#include <stdlib.h> // malloc, calloc, realloc, free

int main(void) {
    // --- La pile (stack) vs le tas (heap) ---
    // Les variables locales classiques (int x = 5;) vivent sur la PILE : elles sont libérées
    // automatiquement à la fin de leur bloc. Mais leur durée de vie est limitée à ce bloc.
    // Pour une donnée qui doit survivre plus longtemps, ou dont la taille n'est connue qu'à
    // l'exécution, on alloue sur le TAS avec malloc(), et on doit la libérer nous-même avec free().

    // --- malloc : alloue un bloc de mémoire brut (non initialisé) ---
    printf("--- malloc ---\n");
    int *nombre = malloc(sizeof(int)); // demande la place pour UN int
    if (nombre == NULL) {
        // malloc peut échouer (mémoire insuffisante) : il FAUT vérifier le résultat !
        fprintf(stderr, "Échec de l'allocation mémoire\n");
        return 1;
    }
    *nombre = 42;
    printf("Valeur allouée dynamiquement : %d\n", *nombre);
    free(nombre); // ⚠️ OBLIGATOIRE : sans ça, c'est une fuite mémoire (memory leak)
    nombre = NULL; // bonne pratique : évite d'utiliser un pointeur déjà libéré ("use after free")

    // --- Tableau dynamique (taille connue seulement à l'exécution, impossible avec un tableau classique) ---
    printf("\n--- Tableau dynamique avec malloc ---\n");
    int taille;
    printf("(Simulation : taille = 5)\n");
    taille = 5; // dans un vrai programme, viendrait par ex. d'une saisie utilisateur

    int *tableau_dynamique = malloc(taille * sizeof(int));
    if (tableau_dynamique == NULL) {
        fprintf(stderr, "Échec de l'allocation\n");
        return 1;
    }
    for (int i = 0; i < taille; i++) {
        tableau_dynamique[i] = i * i;
    }
    printf("Contenu : ");
    for (int i = 0; i < taille; i++) {
        printf("%d ", tableau_dynamique[i]);
    }
    printf("\n");
    free(tableau_dynamique);

    // --- calloc : comme malloc, mais initialise tout à zéro ---
    printf("\n--- calloc ---\n");
    int *zeros = calloc(5, sizeof(int)); // 5 éléments, tous initialisés à 0
    printf("Contenu (tout à 0) : ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", zeros[i]);
    }
    printf("\n");
    free(zeros);

    // --- realloc : agrandit ou réduit un bloc déjà alloué ---
    printf("\n--- realloc ---\n");
    int *dynamique = malloc(3 * sizeof(int));
    dynamique[0] = 1;
    dynamique[1] = 2;
    dynamique[2] = 3;

    int *agrandi = realloc(dynamique, 5 * sizeof(int)); // passe de 3 à 5 éléments
    if (agrandi == NULL) {
        fprintf(stderr, "Échec du realloc\n");
        free(dynamique);
        return 1;
    }
    dynamique = agrandi; // ⚠️ toujours réaffecter : realloc peut déplacer le bloc en mémoire
    dynamique[3] = 4;
    dynamique[4] = 5;
    printf("Après realloc : ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", dynamique[i]);
    }
    printf("\n");
    free(dynamique);

    // --- Les 3 pièges classiques de la mémoire manuelle ---
    printf(
        "\n--- Les pièges classiques (à éviter, non exécutés ici) ---\n"
        "1. Fuite mémoire (memory leak)   : oublier free() -> la mémoire n'est jamais rendue.\n"
        "2. Use-after-free                : utiliser un pointeur après l'avoir libéré.\n"
        "3. Double free                   : appeler free() deux fois sur le même pointeur.\n"
        "\n"
        "C'est exactement ce que le système d'ownership de Rust élimine à la COMPILATION,\n"
        "et ce que le Garbage Collector de Java/C# élimine à l'EXÉCUTION (au prix de performances\n"
        "un peu moins prévisibles).\n"
    );

    return 0;
}
