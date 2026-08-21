// Fichier 05_templates.cpp
// Objectif : templates de fonction et de classe. L'équivalent C++ des génériques (résolus
// à la COMPILATION, contrairement aux generics C#/Java qui existent aussi à l'exécution).
// Compiler : g++ -std=c++17 -Wall 05_templates.cpp -o templates && ./templates

#include <iostream>
#include <string>
using namespace std;

// --- Fonction template : fonctionne avec n'importe quel type qui supporte les opérations utilisées ---
template <typename T>
T maximum(T a, T b) {
    return (a > b) ? a : b; // nécessite que T supporte l'opérateur >
}

// --- Classe template : équivalent de Boite<T> en Rust/Java ---
template <typename T>
class Boite {
private:
    T contenu;
public:
    Boite(T valeur) : contenu(valeur) {}
    T getContenu() const { return contenu; }
    void setContenu(T valeur) { contenu = valeur; }
};

// --- Template avec plusieurs paramètres de type ---
template <typename K, typename V>
class Paire {
public:
    K cle;
    V valeur;
    Paire(K c, V v) : cle(c), valeur(v) {}
    void afficher() const {
        cout << cle << " -> " << valeur << endl;
    }
};

// --- Contrainte "à l'ancienne" (avant les concepts C++20) : simplement documentée en commentaire ---
// En C++20, on pourrait écrire : template <typename T> requires totally_ordered<T> ...
// Ici, si T ne supporte pas ">", l'erreur apparaît seulement à la COMPILATION du point d'appel
// (message d'erreur souvent long, contrairement à l'erreur claire d'un trait bound Rust).
template <typename T>
T plusGrandDansTableau(T tableau[], int taille) {
    T plusGrand = tableau[0];
    for (int i = 1; i < taille; i++) {
        if (tableau[i] > plusGrand) {
            plusGrand = tableau[i];
        }
    }
    return plusGrand;
}

int main() {
    // --- Fonction template : le type T est déduit automatiquement selon les arguments ---
    cout << "maximum(3, 7) = " << maximum(3, 7) << endl;             // T = int
    cout << "maximum(3.5, 2.1) = " << maximum(3.5, 2.1) << endl;     // T = double
    cout << "maximum(string(\"a\"), string(\"b\")) = " << maximum(string("a"), string("b")) << endl; // T = string

    // --- Classe template ---
    cout << "\n--- Boite<T> ---" << endl;
    Boite<int> boiteEntier(42);
    Boite<string> boiteTexte("Bonjour");
    cout << "Contenu (int) : " << boiteEntier.getContenu() << endl;
    cout << "Contenu (string) : " << boiteTexte.getContenu() << endl;

    // --- Template à deux paramètres ---
    cout << "\n--- Paire<K, V> ---" << endl;
    Paire<string, int> age("Alice", 25);
    age.afficher();

    // --- Fonction template sur un tableau ---
    int nombres[] = {3, 7, 2, 9, 4};
    cout << "\nPlus grand nombre : " << plusGrandDansTableau(nombres, 5) << endl;

    double flottants[] = {1.1, 5.5, 2.2};
    cout << "Plus grand flottant : " << plusGrandDansTableau(flottants, 3) << endl;

    cout << "\nNote : les templates C++ sont résolus à la COMPILATION (comme les génériques Rust) :\n"
         << "chaque utilisation avec un type différent génère du code spécialisé (pas de coût à\n"
         << "l'exécution), mais les erreurs de contrainte sont souvent moins claires qu'en Rust." << endl;

    return 0;
}
