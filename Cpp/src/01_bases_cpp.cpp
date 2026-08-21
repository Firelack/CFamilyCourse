// Fichier 01_bases_cpp.cpp
// Objectif : ce que C++ change par rapport à C, dès la syntaxe de base.
// Compiler : g++ -std=c++17 -Wall 01_bases_cpp.cpp -o bases_cpp && ./bases_cpp

#include <iostream> // remplace <stdio.h> : flux d'entrée/sortie orientés objet
#include <string>   // std::string : un vrai type chaîne, contrairement au char* de C !

// namespace : évite les conflits de noms entre bibliothèques (n'existe pas en C)
using namespace std; // pour ne pas avoir à écrire std:: partout (dans un vrai projet, à utiliser avec parcimonie)

// --- Surcharge de fonctions (overloading) : IMPOSSIBLE en C, deux fonctions peuvent avoir le même nom ---
int addition(int a, int b) { return a + b; }
double addition(double a, double b) { return a + b; } // le compilateur choisit selon les types des arguments

// --- Valeurs de paramètres par défaut : impossible en C ---
void saluer(string nom, string civilite = "cher") {
    cout << "Bonjour, " << civilite << " " << nom << " !" << endl;
}

int main() {
    // --- bool est un type NATIF en C++ (pas besoin de <stdbool.h> comme en C) ---
    bool vrai_ou_faux = true;

    // --- iostream : cout/cin remplacent printf/scanf ---
    int age = 25;
    cout << "Age : " << age << ", vrai_ou_faux : " << vrai_ou_faux << endl;

    // --- auto : déduction automatique de type (comme "var" en C#, ou l'inférence de Rust) ---
    auto x = 42;       // déduit : int
    auto y = 3.14;      // déduit : double
    auto nom = string("Alice"); // déduit : std::string
    cout << "auto : " << x << " " << y << " " << nom << endl;

    // --- std::string : un vrai type chaîne, avec des méthodes, contrairement au char* de C ---
    string message = "Bonjour";
    message += ", le monde"; // concaténation directe avec +=, pas besoin de strcat !
    cout << "\nMessage : " << message << " (longueur : " << message.length() << ")" << endl;
    cout << "Majuscule du premier caractère... enfin bref, .substr(0, 7) = " << message.substr(0, 7) << endl;

    // --- Les RÉFÉRENCES (&) : un alias sur une variable existante, différent d'un pointeur ---
    // Contrairement à un pointeur, une référence ne peut JAMAIS être NULL et ne peut pas être
    // réaffectée à autre chose une fois initialisée. C'est plus sûr et plus simple à utiliser.
    int valeur = 10;
    int &reference = valeur; // "reference" est un AUTRE NOM pour la variable "valeur"
    reference = 20; // modifie directement "valeur"
    cout << "\nvaleur après modification via la référence : " << valeur << endl;

    // --- Passage par référence à une fonction (équivalent plus simple du passage par pointeur en C) ---
    auto incrementer = [](int &n) { n++; }; // lambda C++11 (voir aussi les fonctions normales)
    incrementer(valeur);
    cout << "valeur après incrementer(valeur) : " << valeur << endl;

    // --- Surcharge de fonctions ---
    cout << "\naddition(3, 4) = " << addition(3, 4) << endl;         // appelle la version int
    cout << "addition(3.5, 4.2) = " << addition(3.5, 4.2) << endl;   // appelle la version double

    // --- Paramètres par défaut ---
    saluer("Bob");            // utilise "cher" par défaut
    saluer("Charlie", "estimé");

    // --- Structures de contrôle : identiques à C ---
    for (int i = 0; i < 3; i++) {
        cout << "Iteration " << i << endl;
    }

    // --- Range-based for (C++11), équivalent du for-each Java/Rust ---
    string mots[] = {"un", "deux", "trois"};
    cout << "\nParcours range-based for : ";
    for (const auto &mot : mots) { // "const auto&" : lecture seule, pas de copie inutile
        cout << mot << " ";
    }
    cout << endl;

    cout << "\nNote : C++ garde TOUT ce qui existe en C (pointeurs, malloc...) tout en ajoutant\n"
         << "des alternatives plus sûres et plus expressives (références, string, auto...)." << endl;

    return 0;
}
