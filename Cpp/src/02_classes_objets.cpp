// Fichier 02_classes_objets.cpp
// Objectif : classes, constructeurs/destructeurs, encapsulation. Les bases de la POO en C++.
// Compiler : g++ -std=c++17 -Wall 02_classes_objets.cpp -o classes_objets && ./classes_objets

#include <iostream>
#include <string>
using namespace std;

class Personnage {
private:
    // "private" par défaut dans une class (contrairement à "struct" où c'est "public" par défaut !)
    string nom;
    int pv;
    static int compteurInstances; // membre "static" : partagé par TOUTES les instances (comme en Java)

public:
    // --- Constructeur : appelé automatiquement à la création de l'objet ---
    // Liste d'initialisation (après les ":") : façon idiomatique et plus efficace d'initialiser les champs
    Personnage(string nomPerso, int pvInitial) : nom(nomPerso), pv(pvInitial) {
        compteurInstances++;
        cout << "Constructeur appelé pour " << nom << endl;
    }

    // --- Destructeur : appelé automatiquement quand l'objet est détruit (fin de scope, delete...) ---
    // N'existe PAS en Java/C# (le Garbage Collector s'en charge, à un moment indéterminé).
    // En C++, la destruction est déterministe : c'est la base du pattern RAII (voir chapitre 4).
    ~Personnage() {
        compteurInstances--;
        cout << "Destructeur appelé pour " << nom << endl;
    }

    // --- Méthode "const" : garantit qu'elle ne modifie PAS l'objet (vérifié à la compilation) ---
    string decrire() const {
        return nom + " - " + to_string(pv) + " PV";
    }

    // --- Méthode normale : peut modifier l'objet ---
    void subirDegats(int degats) {
        pv -= degats;
        if (pv < 0) pv = 0;
    }

    bool estVivant() const {
        return pv > 0;
    }

    // --- Getter/Setter (comme en Java), utiles car "nom" et "pv" sont private ---
    string getNom() const { return nom; }
    int getPv() const { return pv; }

    // --- Méthode statique : appartient à la classe, pas à une instance ---
    static int getCompteurInstances() {
        return compteurInstances;
    }
};

// Les membres static doivent être définis une seule fois EN DEHORS de la classe
int Personnage::compteurInstances = 0;

int main() {
    cout << "Instances au départ : " << Personnage::getCompteurInstances() << endl;

    {
        // --- Création d'objets (deux syntaxes possibles) ---
        Personnage alice("Alice", 100); // sur la PILE : détruit automatiquement à la fin du bloc
        Personnage bob("Bob", 80);

        cout << "\n" << alice.decrire() << endl;
        cout << bob.decrire() << endl;

        bob.subirDegats(30);
        cout << "\nAprès dégâts : " << bob.decrire() << endl;
        cout << bob.getNom() << " est vivant : " << boolalpha << bob.estVivant() << endl;

        cout << "\nInstances actuelles : " << Personnage::getCompteurInstances() << endl;
    } // <- alice et bob sont détruits ICI (fin du bloc), leurs destructeurs s'exécutent automatiquement

    cout << "\nInstances après le bloc : " << Personnage::getCompteurInstances() << endl;

    cout << "\nNote : le destructeur s'exécute de façon DÉTERMINISTE à la fin du scope.\n"
         << "En Java/C#, un Garbage Collector s'en charge, mais on ne sait pas exactement QUAND." << endl;

    return 0;
}
