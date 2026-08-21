// Fichier 05_structs_pointeurs_fonctions.c
// Objectif : struct (pas de classes en C !), pointeurs sur struct (->), pointeurs de fonctions.
// Compiler : gcc 05_structs_pointeurs_fonctions.c -o structs && ./structs

#include <stdio.h>
#include <string.h>

// --- struct : regroupe des données, mais AUCUNE méthode ne peut être définie dedans (pas de "impl") ---
struct Personne {
    char nom[30];
    int age;
};

// typedef : évite d'avoir à écrire "struct Personne" à chaque fois, juste "Personne"
typedef struct {
    double x;
    double y;
} Point;

// --- "Méthodes" simulées : en C, on écrit des fonctions séparées qui prennent la struct en paramètre ---
// Par VALEUR : la fonction reçoit une COPIE de la struct (comme un int), les modifications ne sont
// pas répercutées à l'extérieur.
void afficher_personne(struct Personne p) {
    printf("%s a %d ans\n", p.nom, p.age);
}

// Par POINTEUR : la fonction reçoit l'ADRESSE de la struct, elle peut donc la modifier.
// C'est la façon idiomatique de "passer un objet" efficacement en C (évite de copier toute la struct).
void vieillir(struct Personne *p) {
    p->age += 1; // "->" déréférence ET accède au champ en une seule opération (raccourci de (*p).age)
}

double distance_origine(const Point *p) {
    // "const" ici garantit que la fonction ne modifiera pas *p (bonne pratique pour les paramètres en lecture seule)
    return p->x * p->x + p->y * p->y; // (racine carrée omise pour l'exemple)
}

// --- Pointeur de fonction : une variable qui "pointe" vers une fonction, un peu comme une closure Rust ---
int addition(int a, int b) { return a + b; }
int soustraction(int a, int b) { return a - b; }

int appliquer_operation(int a, int b, int (*operation)(int, int)) {
    return operation(a, b); // appelle la fonction pointée
}

int main(void) {
    // --- Création et utilisation d'une struct ---
    struct Personne alice;
    strcpy(alice.nom, "Alice"); // pas d'affectation directe possible sur un tableau de char !
    alice.age = 25;
    afficher_personne(alice);

    // --- Passage par pointeur pour modifier ---
    printf("Avant vieillir : %d ans\n", alice.age);
    vieillir(&alice);
    printf("Après vieillir : %d ans\n", alice.age);

    // --- typedef struct ---
    Point origine_a = {3.0, 4.0}; // initialisation par accolades, dans l'ordre des champs
    printf("\nDistance au carré : %.1f\n", distance_origine(&origine_a));

    // --- Tableau de struct ---
    printf("\n--- Tableau de personnes ---\n");
    struct Personne equipe[2];
    strcpy(equipe[0].nom, "Bob");
    equipe[0].age = 30;
    strcpy(equipe[1].nom, "Charlie");
    equipe[1].age = 22;
    for (int i = 0; i < 2; i++) {
        afficher_personne(equipe[i]);
    }

    // --- Pointeur de fonction ---
    printf("\n--- Pointeur de fonction ---\n");
    int (*mon_operation)(int, int) = addition; // "mon_operation" pointe vers addition
    printf("addition(3, 4) via pointeur : %d\n", mon_operation(3, 4));

    mon_operation = soustraction; // on peut le faire pointer vers une autre fonction !
    printf("soustraction(10, 4) via pointeur : %d\n", mon_operation(10, 4));

    printf("\nRésultat via appliquer_operation(5, 2, addition) : %d\n", appliquer_operation(5, 2, addition));
    printf("Résultat via appliquer_operation(5, 2, soustraction) : %d\n", appliquer_operation(5, 2, soustraction));

    printf(
        "\nNote : pas d'héritage ni de classes en C. Pour organiser du code réutilisable,\n"
        "on combine des struct (données) + des fonctions qui les prennent en paramètre (comportement).\n"
    );

    return 0;
}
