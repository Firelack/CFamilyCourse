# 🔧 Fonctions Utiles en C

## 🖨️ `<stdio.h>` — Entrées/sorties

- `printf(format, ...)` : affiche du texte formaté. Spécificateurs courants : `%d` (int), `%f`
  (float/double), `%c` (char), `%s` (chaîne), `%p` (pointeur/adresse), `%%` (le caractère `%`).
- `scanf(format, ...)` : lit une entrée utilisateur (attend des **pointeurs** en paramètre, ex :
  `scanf("%d", &age);`).
- `fopen(chemin, mode)` : ouvre un fichier. Modes courants : `"r"` (lecture), `"w"` (écriture,
  écrase), `"a"` (ajout). Renvoie `NULL` en cas d'échec.
- `fprintf(fichier, format, ...)` / `fscanf(fichier, format, ...)` : comme `printf`/`scanf` mais
  vers/depuis un fichier.
- `fgets(buffer, taille, fichier)` : lit une ligne (plus sûr que `gets`, qui ne vérifie pas la
  taille et est déconseillé).
- `fclose(fichier)` : ferme un fichier, à ne jamais oublier après un `fopen`.

## 🧮 `<stdlib.h>` — Utilitaires généraux

- `malloc(taille)` : alloue `taille` octets sur le tas, non initialisés. Renvoie `NULL` si échec.
- `calloc(nombre, taille)` : comme `malloc`, mais initialise tout à zéro.
- `realloc(pointeur, nouvelle_taille)` : redimensionne un bloc déjà alloué.
- `free(pointeur)` : libère un bloc alloué avec `malloc`/`calloc`/`realloc`.
- `atoi(chaine)` / `atof(chaine)` : convertit une chaîne en `int`/`double` (pas de gestion d'erreur
  propre — préférer `strtol`/`strtod` si on doit détecter les erreurs de conversion).
- `exit(code)` : arrête immédiatement le programme avec un code de sortie.

## 🔤 `<string.h>` — Manipulation de chaînes

- `strlen(s)` : longueur d'une chaîne (sans compter le `\0` final).
- `strcpy(dest, src)` / `strncpy(dest, src, n)` : copie une chaîne (la version `n` limite la taille
  copiée, plus sûre).
- `strcat(dest, src)` / `strncat(dest, src, n)` : concatène une chaîne à la fin d'une autre.
- `strcmp(s1, s2)` : compare deux chaînes (0 si égales, négatif/positif sinon selon l'ordre
  lexicographique).
- `strchr(s, c)` / `strstr(s, sous_chaine)` : recherche un caractère / une sous-chaîne.
- `memset(ptr, valeur, taille)` / `memcpy(dest, src, taille)` : manipulation brute de blocs mémoire.

## 🧪 `<math.h>` — Fonctions mathématiques

- `sqrt(x)`, `pow(x, y)`, `fabs(x)` (valeur absolue pour les flottants), `floor(x)`, `ceil(x)`.
- Nécessite souvent de compiler avec `-lm` : `gcc fichier.c -o programme -lm`.

## ⚠️ `<errno.h>` et `<assert.h>` — Gestion d'erreurs

- `errno` : code d'erreur rempli par les fonctions système en cas d'échec.
- `strerror(errno)` : convertit `errno` en message lisible.
- `assert(condition)` : arrête le programme si `condition` est fausse (détection de bugs en
  développement).

## 📏 Opérateur `sizeof`

- `sizeof(type)` ou `sizeof(variable)` : donne la taille en octets. Indispensable avec `malloc` :
  `malloc(taille * sizeof(int))`, et pour calculer la taille d'un tableau statique :
  `sizeof(tableau) / sizeof(tableau[0])`.
