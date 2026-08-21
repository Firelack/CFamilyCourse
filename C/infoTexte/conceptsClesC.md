# 💡 Concepts Clés en C

## 🧠 Philosophie du langage

C est un langage **procédural** et **bas niveau** : pas de classes, pas d'exceptions, pas de
génériques, pas de gestion mémoire automatique. Le programmeur a un contrôle total... et donc
aussi l'entière responsabilité des erreurs. C'est le langage le plus proche du fonctionnement réel
de la machine dans cette famille.

## 📍 Pointeurs : LE concept central

| Symbole | Rôle |
| :--- | :--- |
| `&variable` | "Adresse de" : donne l'adresse mémoire de `variable`. |
| `*pointeur` | "Déréférencement" : accède à la valeur stockée à l'adresse pointée. |
| `int *p` | Déclare `p` comme un pointeur vers un `int`. |
| `p->champ` | Raccourci de `(*p).champ` : accède à un champ à travers un pointeur de struct. |
| `NULL` | Pointeur qui ne pointe vers rien. Le déréférencer plante le programme. |

- Un tableau se comporte comme un pointeur vers son premier élément (`tableau` ≈ `&tableau[0]`).
- Un paramètre de fonction est **toujours passé par valeur** (copié), sauf si on passe un pointeur :
  c'est la seule façon de "modifier" une variable depuis une fonction.
- Aucune vérification à la compilation (ni à l'exécution par défaut) : un pointeur invalide,
  un tableau dépassé, ou un pointeur NULL déréférencé provoquent un **comportement indéfini**
  (souvent un crash, parfois pire : une faille de sécurité silencieuse).

## 🧺 Mémoire : pile (stack) vs tas (heap)

| | Pile (stack) | Tas (heap) |
| :--- | :--- | :--- |
| Allocation | Automatique (`int x = 5;`) | Manuelle (`malloc`, `calloc`, `realloc`) |
| Libération | Automatique, à la fin du bloc `{}` | **Manuelle**, avec `free()` — sinon fuite mémoire |
| Taille | Doit être connue à la compilation | Peut être décidée à l'exécution |
| Vitesse | Très rapide | Plus lente (gestion par l'OS) |

Les 3 pièges classiques de la mémoire manuelle :

1. **Fuite mémoire** (memory leak) : oublier `free()`.
2. **Use-after-free** : utiliser un pointeur après l'avoir libéré.
3. **Double free** : appeler `free()` deux fois sur le même pointeur.

C'est exactement ce que Rust élimine à la compilation (ownership) et ce que Java/C# éliminent à
l'exécution (Garbage Collector).

## 🔤 Chaînes de caractères

- Pas de type `String` natif : une chaîne C est un `char[]` (ou `char*`) terminé par un octet nul
  `'\0'`.
- `strlen`, `strcpy`, `strcat`, `strcmp` (dans `<string.h>`) remplacent les méthodes de `String`.
- Aucune protection contre les dépassements de buffer : `strcpy` peut écrire au-delà de la taille du
  tableau de destination si on ne fait pas attention (`strncpy` est une version plus sûre).

## 🏗️ Struct : des données, pas de comportement

```c
struct Personne { char nom[30]; int age; };
void afficher(struct Personne p);      // par valeur : copie, ne modifie pas l'original
void vieillir(struct Personne *p);     // par pointeur : peut modifier l'original via p->age
```

- Pas de méthodes DANS la struct : on écrit des fonctions séparées qui la prennent en paramètre.
- `typedef struct { ... } NomCourt;` évite de répéter `struct` à chaque utilisation.

## 💣 Gestion d'erreurs "à la C"

Pas d'exceptions ! Deux mécanismes principaux, à combiner :

- **Code retour** : convention (pas une règle imposée par le langage) où une fonction renvoie
  `0` pour succès et une valeur `!= 0` pour signaler une erreur. Le "vrai" résultat est souvent
  renvoyé via un pointeur passé en paramètre.
- **`errno`** (`<errno.h>`) : variable globale remplie par les fonctions système en cas d'erreur.
  `strerror(errno)` donne un message lisible.
- **`assert(condition)`** (`<assert.h>`) : arrête le programme si la condition est fausse. Sert à
  détecter des bugs de programmation (pas des erreurs "normales" comme un fichier manquant).

⚠️ Rien n'oblige à vérifier un code retour ou `errno` : les oublier est l'une des causes de bugs
les plus fréquentes en C.

## 🔧 Pointeurs de fonctions

```c
int (*operation)(int, int) = addition; // operation "pointe" vers la fonction addition
operation(3, 4); // appelle addition(3, 4)
```

C'est l'ancêtre des closures Rust / lambdas Java : on peut passer une fonction en paramètre d'une
autre fonction, mais sans pouvoir "capturer" de variables environnantes comme le fait une vraie
closure.
