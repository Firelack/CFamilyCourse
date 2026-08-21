# 💡 Concepts Clés en C++

## 🧠 Philosophie du langage

C++ est **compatible avec C** (on peut compiler du code C quasiment tel quel) mais ajoute la
programmation orientée objet, les génériques (templates), une bibliothèque standard riche (STL),
et des outils pour une gestion mémoire plus sûre. C'est un langage **multi-paradigme** : on peut
y faire du C "brut", de l'objet à la Java, ou du générique très abstrait.

## 🆕 Nouveautés par rapport à C

| | C | C++ |
| :--- | :--- | :--- |
| Entrées/sorties | `printf`/`scanf` | `cout`/`cin` (`<iostream>`) |
| Chaînes | `char*` (terminée par `\0`) | `std::string` (vrai type, avec méthodes) |
| Booléen | `<stdbool.h>` | `bool` natif |
| Alias de variable | Pointeur (`int *p`) | Référence (`int &r`), ne peut jamais être `NULL` |
| Génériques | ❌ (macros, `void*`) | ✅ Templates |
| Classes | ❌ | ✅ `class` / `struct` (même chose, sauf visibilité par défaut) |
| Surcharge de fonctions | ❌ | ✅ Plusieurs fonctions, même nom, paramètres différents |
| Gestion d'erreurs | Codes retour + `errno` | Codes retour **ou** exceptions (`try`/`catch`/`throw`) |

## 🔗 Référence vs Pointeur

```cpp
int x = 5;
int &r = x;   // référence : un AUTRE NOM pour x, ne peut pas être NULL, ne se réassigne pas
int *p = &x;  // pointeur : peut être NULL, peut être réassigné, doit être déréférencé avec *
```

En pratique, on préfère les références pour les paramètres de fonction "obligatoires" (pas de
risque de `NULL`), et les pointeurs (ou mieux, les smart pointers) quand la ressource peut être
absente ou doit être réaffectée.

## 🏛️ Classes : `class` vs `struct`

- Identiques en C++, à un détail près : dans une `class`, les membres sont **`private` par
  défaut** ; dans une `struct`, ils sont **`public` par défaut**. Par convention, on utilise
  `struct` pour des données pures et `class` dès qu'il y a un comportement / une invariance à
  protéger.
- **Constructeur** : initialise l'objet. **Destructeur** (`~NomClasse()`) : appelé
  automatiquement et de façon **déterministe** à la fin de la portée (contrairement à Java/C# où
  le Garbage Collector s'en charge à un moment indéterminé).
- Liste d'initialisation : `Classe(int x) : champ(x) {}` — plus efficace qu'assigner dans le corps.

## 🧬 Héritage et Polymorphisme

- `class Fille : public Mere { ... }` : héritage public (le plus courant, équivalent d'`extends`).
- **Héritage multiple** possible (`class C : public A, public B`), contrairement à Java/C#.
- `virtual` : rend une méthode redéfinissable avec résolution **à l'exécution** (polymorphisme
  dynamique). Sans `virtual`, C++ appelle la méthode du type déclaré, pas du type réel — piège
  classique pour qui vient de Java, où tout est virtuel par défaut !
- `= 0` (méthode "pure virtual") : rend la classe abstraite (non instanciable), comme une méthode
  abstraite Java.
- `override` (C++11) : mot-clé optionnel qui fait vérifier par le compilateur qu'on redéfinit bien
  une méthode virtuelle existante.
- **Toujours** rendre le destructeur `virtual` dès qu'une classe a au moins une méthode virtuelle,
  sinon la destruction via un pointeur de base peut ne pas appeler le bon destructeur.

## 🧺 Mémoire : `new`/`delete` et RAII

- `new`/`delete` : comme `malloc`/`free`, mais appellent aussi le constructeur/destructeur. Mêmes
  risques d'oubli qu'en C !
- **RAII** (Resource Acquisition Is Initialization) : le principe central du C++ moderne. On lie
  la durée de vie d'une ressource à celle d'un objet ; le destructeur s'en charge automatiquement,
  y compris en cas d'exception.
- **Smart pointers** (`<memory>`) : rendent `new`/`delete` manuels quasiment obsolètes.
  - `unique_ptr<T>` : un seul propriétaire, pas de copie possible, seulement un déplacement
    (`move`). Équivalent de l'ownership Rust / `Box<T>`.
  - `shared_ptr<T>` : plusieurs propriétaires, compteur de références ; la ressource est détruite
    quand le compteur tombe à zéro. Équivalent de `Rc<T>`/`Arc<T>` en Rust.

## 🧬 Templates (Génériques)

- `template <typename T> T f(T a, T b) { ... }` : fonction générique, résolue **à la
  compilation** (un code spécialisé est généré pour chaque type utilisé — zero-cost abstraction).
- `template <typename T> class Boite { ... };` : classe générique.
- Pas de contraintes de type aussi explicites qu'en Rust (`T: PartialOrd`) avant C++20 (qui
  introduit les *concepts*) : une utilisation invalide d'un template produit une erreur de
  compilation souvent longue, au niveau du point d'instanciation.

## 💣 Exceptions

- `try { ... } catch (const Type &e) { ... }`, `throw expression;` : syntaxe proche de Java.
- Pas de "checked exceptions" : rien n'oblige à déclarer ou capturer une exception.
- `e.what()` (sur `std::exception` et ses dérivées) : récupère le message, équivalent de
  `getMessage()` en Java.
- Une exception personnalisée hérite généralement de `std::exception` ou `std::runtime_error`.
- Le C++ moderne utilise aussi `std::optional<T>` (proche d'`Option<T>`) pour les absences de
  valeur "normales", et réserve les exceptions aux erreurs vraiment exceptionnelles.

## ➕ Surcharge d'opérateurs

- Spécificité forte de C++ (absente en Java, limitée en C#) : on peut redéfinir `+`, `-`, `==`,
  `[]`, `<<`... pour ses propres types, afin qu'ils se comportent comme des types natifs.
  `operator<<` (pour `cout << monObjet`) se définit **en dehors** de la classe.
