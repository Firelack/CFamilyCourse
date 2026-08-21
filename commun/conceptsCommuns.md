# 🌐 Ce qui est commun à C, C++ et C#

Ces trois langages partagent une syntaxe "à la C" (accolades, points-virgules, types explicites),
mais ont des philosophies très différentes. Ce fichier résume ce qui est commun avant de plonger
dans les spécificités de chaque langage (voir `/C`, `/Cpp`, `/CSharp`).

## 🧬 D'où ça vient

```A
        C  (1972, procédural, bas niveau, pas de gestion mémoire automatique)
        │
        ├──> C++ (1985, ajoute l'objet, les templates, la STL... tout en restant compatible C)
        │
        └──> C# (2000, inspiré de C++ ET Java, mais 100% managé avec Garbage Collector)
```

## 📊 Vue d'ensemble comparative

| | **C** | **C++** | **C#** |
| :--- | :--- | :--- | :--- |
| Paradigme | Procédural | Multi-paradigme (procédural + POO + générique) | Orienté objet (comme Java) |
| Compilation | Compilé natif (gcc/clang) | Compilé natif (g++/clang++) | Compilé en bytecode IL, exécuté par le runtime .NET |
| Gestion mémoire | **Manuelle** (`malloc`/`free`) | Manuelle ou RAII/smart pointers | **Automatique** (Garbage Collector, comme Java) |
| `null` | Pointeur `NULL` (aucune sécurité) | `nullptr` (C++11+) | `null` (+ nullable reference types en C# 8+) |
| Point d'entrée | `int main()` | `int main()` | `static void Main()` |
| Fichier source | `.c` | `.cpp` / `.hpp` | `.cs` |
| Génériques | ❌ (macros ou `void*`) | ✅ Templates (résolus à la compilation) | ✅ Generics (résolus à l'exécution, réifiés) |
| POO (classes) | ❌ | ✅ | ✅ |
| Gestion d'erreurs | Codes retour + `errno` | Codes retour **ou** exceptions | Exceptions (comme Java) |

## 🔤 Syntaxe partagée (héritée de C)

Ces trois langages se ressemblent pour :

- Les blocs délimités par `{ }` et les instructions terminées par `;`.
- Les types de base : `int`, `float`/`double`, `char`, `bool` (natif en C++/C#, via `<stdbool.h>`
  en C).
- Les opérateurs : `+ - * / %`, `== != < > <= >=`, `&& || !`, `++ --`, `+= -= *= /=`.
- Les structures de contrôle : `if/else`, `for`, `while`, `do...while`, `switch`.
- Les commentaires : `//` (ligne) et `/* ... */` (bloc).
- Les fonctions : `TypeRetour nom(paramètres) { ... }`.

## 🔀 Ce qui diverge fondamentalement

- **C** n'a **ni classes, ni exceptions, ni génériques, ni gestion mémoire automatique** : tout est
  fonctions + structs + pointeurs. C'est le langage le plus "brut" de la famille.
- **C++** ajoute les classes, l'héritage, les templates, la bibliothèque standard (STL), les
  exceptions, TOUT en gardant la possibilité de faire du C "brut" (pointeurs, `malloc`...). C'est
  pour ça qu'on dit que C++ est multi-paradigme.
- **C#** ressemble à Java dans son fonctionnement (compilé en bytecode, ramasse-miettes, tout est
  objet), mais reprend une syntaxe proche de C++ et ajoute beaucoup de sucre syntaxique moderne
  (propriétés, LINQ, pattern matching, `var`, chaînes interpolées `$"..."`).

## 🚀 Comment lire ce projet

- `/commun` (ce dossier) : les bases communes, à lire en premier.
- `/C` : bases procédurales, **pointeurs et mémoire manuelle** (LE concept central de C).
- `/Cpp` : tout ce que C++ ajoute par-dessus C (classes, templates, STL, RAII, exceptions).
- `/CSharp` : en supposant que tu connais déjà la POO (via Java), on couvre surtout ce qui est
  **différent ou spécifique à C#** (propriétés, LINQ, generics à la C#, pattern matching moderne).

Chaque dossier de langage a sa propre structure de chapitres et ses propres fiches de révision dans
un sous-dossier `infoTexte/`, sur le même principe que le projet `JavaCourseReview` /
`RustCourseReview`.
