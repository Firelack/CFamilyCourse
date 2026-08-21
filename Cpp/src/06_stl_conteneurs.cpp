// Fichier 06_stl_conteneurs.cpp
// Objectif : la STL (Standard Template Library) : vector, map, set, string, algorithmes.
// Compiler : g++ -std=c++17 -Wall 06_stl_conteneurs.cpp -o stl && ./stl

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <algorithm> // sort, find, for_each...
#include <numeric>   // accumulate
using namespace std;

int main() {
    // --- vector<T> : tableau dynamique, l'équivalent de Vec<T> Rust / ArrayList Java ---
    cout << "--- vector<T> ---" << endl;
    vector<string> fruits;
    fruits.push_back("Pomme");
    fruits.push_back("Banane");
    fruits.push_back("Kiwi");
    cout << "Fruits : ";
    for (const auto &f : fruits) cout << f << " ";
    cout << "\nTaille : " << fruits.size() << endl;

    vector<int> nombres = {5, 3, 8, 1, 9};
    sort(nombres.begin(), nombres.end()); // tri via l'algorithme générique <algorithm>
    cout << "\nNombres triés : ";
    for (int n : nombres) cout << n << " ";
    cout << endl;

    // .at(index) : accès sécurisé (lève une exception si hors limites), contrairement à [index]
    cout << "fruits.at(0) = " << fruits.at(0) << endl;
    // fruits.at(10); // lèverait std::out_of_range

    fruits.erase(fruits.begin() + 1); // supprime "Banane" (via un itérateur)
    cout << "Après suppression : ";
    for (const auto &f : fruits) cout << f << " ";
    cout << endl;

    // --- algorithmes avec des lambdas C++11 (comme les closures Rust) ---
    cout << "\n--- Algorithmes + lambdas ---" << endl;
    int somme = accumulate(nombres.begin(), nombres.end(), 0); // équivalent de .sum() / .fold()
    cout << "Somme : " << somme << endl;

    auto it = find_if(nombres.begin(), nombres.end(), [](int n) { return n > 5; });
    if (it != nombres.end()) {
        cout << "Premier nombre > 5 : " << *it << endl;
    }

    int nbPairs = count_if(nombres.begin(), nombres.end(), [](int n) { return n % 2 == 0; });
    cout << "Nombre de pairs : " << nbPairs << endl;

    // --- map<K, V> : dictionnaire ordonné par clé, l'équivalent de TreeMap Java ---
    cout << "\n--- map<K, V> ---" << endl;
    map<string, int> ages;
    ages["Alice"] = 25; // syntaxe [] pour insérer/modifier, comme un dictionnaire
    ages["Bob"] = 30;
    ages.insert({"Charlie", 22});

    for (const auto &[nom, age] : ages) { // "structured bindings" (C++17), déstructure la paire
        cout << nom << " -> " << age << " ans" << endl;
    }

    if (ages.count("Alice")) { // .count() renvoie 0 ou 1 (une map n'a pas de doublons de clé)
        cout << "\nAlice a " << ages["Alice"] << " ans" << endl;
    }

    // --- set<T> : ensemble trié sans doublons ---
    cout << "\n--- set<T> ---" << endl;
    set<int> ensemble = {3, 1, 4, 1, 5, 9, 2, 6}; // les doublons sont automatiquement ignorés
    cout << "Ensemble (trié automatiquement) : ";
    for (int n : ensemble) cout << n << " ";
    cout << endl;

    // --- unordered_map / unordered_set : versions basées sur une table de hachage (plus rapides,
    // non triées), équivalent des HashMap/HashSet Rust/Java ---
    cout << "\nNote : map/set sont TRIÉS (arbre équilibré, O(log n)).\n"
         << "unordered_map/unordered_set sont basés sur une table de hachage (O(1) en moyenne),\n"
         << "comme HashMap en Rust/Java, mais sans garantie d'ordre." << endl;

    return 0;
}
