# 🔧 Méthodes Utiles en C++

## 🔡 `std::string`

📞 `#include <string>`

- `.length()` / `.size()` : longueur de la chaîne.
- `.substr(debut, longueur)` : extrait une sous-chaîne.
- `.find(sous_chaine)` : renvoie la position, ou `string::npos` si absente.
- `+=` / `+` : concaténation directe (contrairement au `char*` de C).
- `.c_str()` : convertit en `const char*` (utile pour interagir avec des API C).
- `to_string(nombre)` : convertit un nombre en `string`.
- `stoi(s)` / `stod(s)` / `stof(s)` : convertit une chaîne en `int`/`double`/`float` (lève une
  exception `invalid_argument` si la conversion échoue, contrairement à `atoi` en C).

## 📚 `std::vector<T>`

📞 `#include <vector>`

- `.push_back(valeur)` : ajoute à la fin. `.pop_back()` : retire le dernier élément.
- `.size()` / `.empty()` : taille / test si vide.
- `.at(index)` : accès sécurisé (exception `out_of_range` si invalide). `v[index]` : accès direct,
  comportement indéfini si hors limites (comme un tableau C).
- `.insert(iterateur, valeur)` / `.erase(iterateur)` : insertion/suppression à une position.
- `.begin()` / `.end()` : itérateurs de début/fin, utilisés par les algorithmes de `<algorithm>`.
- `.clear()` : vide le vecteur.

## 🗂️ `std::map<K, V>` / `std::unordered_map<K, V>`

📞 `#include <map>` / `#include <unordered_map>`

- `map` : trié par clé (arbre équilibré). `unordered_map` : non trié, basé sur une table de
  hachage (plus rapide en moyenne).
- `m[cle] = valeur` : insère ou modifie. ⚠️ `m[cle]` crée une entrée par défaut si la clé n'existe
  pas encore (même en lecture) !
- `.find(cle)` : renvoie un itérateur (`.end()` si absent), plus sûr que `[]` pour tester la
  présence sans créer d'entrée.
- `.count(cle)` : renvoie 0 ou 1 (une map n'a pas de doublons de clé).
- `.erase(cle)` : supprime une entrée.

## 🧮 `std::set<T>` / `std::unordered_set<T>`

📞 `#include <set>` / `#include <unordered_set>`

- Ensemble sans doublons. `set` trié, `unordered_set` basé sur une table de hachage.
- `.insert(valeur)`, `.count(valeur)` (0 ou 1), `.erase(valeur)`.

## 🧭 `<algorithm>` et `<numeric>` (fonctionnent sur des itérateurs `.begin()`/`.end()`)

- `sort(debut, fin)` / `sort(debut, fin, comparateur)` : trie (sur place).
- `find(debut, fin, valeur)` / `find_if(debut, fin, predicat)` : recherche.
- `count(debut, fin, valeur)` / `count_if(debut, fin, predicat)` : compte les occurrences.
- `for_each(debut, fin, fonction)` : applique une fonction/lambda à chaque élément.
- `accumulate(debut, fin, valeur_initiale)` (`<numeric>`) : équivalent de `.fold()`/`.sum()`.
- `min_element(debut, fin)` / `max_element(debut, fin)` : renvoient des itérateurs.
- `reverse(debut, fin)` : inverse l'ordre sur place.

## 🎯 Smart Pointers (`<memory>`)

- `make_unique<T>(args...)` : crée un `unique_ptr<T>` (propriétaire unique).
- `make_shared<T>(args...)` : crée un `shared_ptr<T>` (propriétaire partagé, compteur de refs).
- `.get()` : accède au pointeur brut sous-jacent (sans transférer la propriété).
- `.use_count()` (sur `shared_ptr`) : nombre de propriétaires actuels.
- `move(valeur)` (`<utility>`) : transforme une lvalue en rvalue pour forcer un déplacement plutôt
  qu'une copie (indispensable avec `unique_ptr`).

## 💣 Exceptions standards (`<stdexcept>`)

- `runtime_error`, `logic_error`, `invalid_argument`, `out_of_range`, `overflow_error`.
- `.what()` : message de l'exception (méthode héritée de `std::exception`).

## 🖨️ `<iostream>`

- `cout << valeur` : affiche. `cin >> variable` : lit une entrée.
- `endl` : retour à la ligne (et vide le buffer — `"\n"` est plus rapide si le vidage n'est pas
  nécessaire).
- `boolalpha` : affiche `true`/`false` au lieu de `1`/`0` pour un `bool`.
- `getline(cin, chaine)` : lit une ligne entière (contrairement à `cin >> chaine` qui s'arrête au
  premier espace).
