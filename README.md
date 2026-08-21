# 🧭 Projet de Révision - Famille C (C, C++, C#)

Ce projet regroupe des notes et des exemples de code pour réviser **C**, **C++** et **C#**, sur le
même principe que `JavaCourseReview` et `RustCourseReview` : du code commenté en français, organisé
par chapitres, avec des fiches de révision à la fin.

## 📂 Structure

```A
CFamilyCourseReview/
├── commun/                    <- à lire en premier : ce qui est commun aux 3 langages
│   └── conceptsCommuns.md
├── C/                          <- bases procédurales, pointeurs, mémoire manuelle
│   ├── src/*.c                 (6 chapitres)
│   ├── infoTexte/*.md
│   └── Makefile
├── Cpp/                        <- tout ce que C++ ajoute par-dessus C (POO, templates, STL...)
│   ├── src/*.cpp                (8 chapitres)
│   ├── infoTexte/*.md
│   └── Makefile
└── CSharp/                     <- en supposant Java connu : ce qui est spécifique à C#
    ├── src/<Chapitre>/          (7 mini-projets .NET, un par chapitre)
    ├── infoTexte/*.md
    └── CSharpCourseReview.sln
```

---

## 🛠️ Installation

Trois outils différents sont nécessaires (un par langage). Chaque partie (`C/`, `Cpp/`, `CSharp/`) est indépendante des deux autres.

### Pour C et C++ → `gcc` / `g++`

**Windows**
Deux options :

1. **WSL** (recommandé) : installer Ubuntu via WSL (`wsl --install` dans PowerShell), puis suivre
   les instructions Linux ci-dessus à l'intérieur de WSL.
2. **MSYS2/MinGW-w64** : installer [MSYS2](https://www.msys2.org/), puis dans le terminal MSYS2 :

   ```bash
   pacman -S mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-make
   ```

**Linux (Debian/Ubuntu)**

```bash
sudo apt update
sudo apt install build-essential
```

`build-essential` installe `gcc`, `g++` et `make` d'un coup.

**macOS**

```bash
xcode-select --install
```

Installer les outils de compilation en ligne de commande d'Apple (inclut `gcc`/`g++`, qui pointent
en réalité vers Clang, compatible).

**Vérifier l'installation :**

```bash
gcc --version
g++ --version
make --version
```

### Pour C# → SDK .NET 8

**Windows**
Télécharger et lancer l'installeur du SDK .NET 8 depuis
[dotnet.microsoft.com/download](https://dotnet.microsoft.com/download) (choisir "SDK", pas
"Runtime").

**Linux (Debian/Ubuntu)**

```bash
sudo apt update
sudo apt install dotnet-sdk-8.0
```

(Si le paquet n'est pas trouvé, il faut d'abord ajouter le dépôt Microsoft — voir
[le guide officiel](https://learn.microsoft.com/dotnet/core/install/linux).)

**macOS**

```bash
brew install --cask dotnet-sdk
```

ou télécharger l'installeur depuis [dotnet.microsoft.com/download](https://dotnet.microsoft.com/download).

**Vérifier l'installation :**

```bash
dotnet --version
```

(doit afficher `8.0.x`)

### 💻 Éditeur / IDE

- **VS Code** avec les extensions *C/C++* (Microsoft), *C#* (Microsoft ou l'extension C# Dev Kit),
  fonctionne bien pour les trois langages.
- **CLion** ou **Visual Studio** pour C/C++.
- **Visual Studio** ou **Rider** pour C# (peuvent ouvrir directement `CSharp/CSharpCourseReview.sln`).

---

## 🚀 Comment lancer chaque partie

### 🔵 C

```bash
cd C
make                     # compile TOUS les chapitres -> exécutables dans C/build/
make run-bases           # compile ET exécute un seul chapitre (ex: 01_bases.c)
make clean               # supprime les fichiers compilés
```

Chapitres disponibles pour `make run-<nom>` (retirer le préfixe numérique, `01_bases.c` -> `bases`).

Sans `make` (compilation manuelle d'un seul fichier) :

```bash
gcc -Wall -Wextra -std=c11 src/01_bases.c -o bases && ./bases
```

### 🟣 C++

```bash
cd Cpp
make                       # compile TOUS les chapitres -> exécutables dans Cpp/build/
make run-templates         # compile ET exécute un seul chapitre (ex: 05_templates.cpp)
make clean                 # supprime les fichiers compilés
```

Sans `make` :

```bash
g++ -Wall -Wextra -std=c++17 src/02_classes_objets.cpp -o classes && ./classes
```

### 🟢 C#

Chaque chapitre est un **mini-projet .NET séparé** (nécessaire en C#, contrairement à C/C++, car un
exécutable C# ne peut avoir qu'un seul point d'entrée).

**Compiler tous les chapitres d'un coup** (vérifie que tout compile, sans rien exécuter) :

```bash
cd CSharp
dotnet build
```

**Lancer un chapitre précis** — se placer dans son dossier et faire `dotnet run` :

```bash
cd CSharp/src/01_BasesEtDifferences && dotnet run
```

Ou, depuis n'importe où, en ciblant le projet directement :

```bash
dotnet run --project CSharp/src/05_LinqEtDelegates
```

Alternative : ouvrir `CSharp/CSharpCourseReview.sln` dans Visual Studio / Rider / VS Code, et lancer
le projet voulu comme n'importe quel programme .NET (clic droit -> "Définir comme projet de
démarrage" puis lancer, ou sélectionner le projet dans la liste déroulante).

---

## 📚 Résumé des chapitres

| # | C | C++ | C# |
| :--- | :--- | :--- | :--- |
| 1 | Bases (types, contrôle de flux, `switch`) | Bases & différences avec C (`string`, références, `auto`) | Bases & différences avec Java (`var`, top-level statements) |
| 2 | Pointeurs et adresses mémoire | Classes, constructeurs/destructeurs | Propriétés, `record`, `struct` vs `class` |
| 3 | Tableaux et chaînes (`char*`) | Héritage, `virtual`, polymorphisme, héritage multiple | Héritage, interfaces à méthodes par défaut |
| 4 | Mémoire dynamique (`malloc`/`free`) | Mémoire moderne (RAII, smart pointers) | Génériques avec contraintes, collections |
| 5 | Structs, pointeurs de fonctions | Templates | LINQ, delegates, events |
| 6 | Fichiers, codes retour, `errno`, `assert` | STL (vector, map, set, algorithms) | Gestion d'erreurs, nullable reference types |
| 7 | — | Exceptions | Pattern matching moderne (`switch` expressions, records) |
| 8 | — | Surcharge d'opérateurs | — |

Chaque dossier de langage a aussi ses propres fiches `infoTexte/conceptsCles*.md` et
`infoTexte/methodesUtiles*.md`.

### This projet was made with IA and is only for learning bases as entertainement
