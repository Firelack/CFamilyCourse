// Fichier 03_heritage_polymorphisme.cpp
// Objectif : héritage, virtual, polymorphisme, classes abstraites, héritage multiple.
// Compiler : g++ -std=c++17 -Wall 03_heritage_polymorphisme.cpp -o heritage && ./heritage

#include <iostream>
#include <string>
using namespace std;

// --- Classe abstraite : contient au moins une méthode "pure virtual" (= 0), ne peut pas être instanciée ---
// C'est l'équivalent d'une classe abstraite Java, mais la syntaxe "= 0" est spécifique à C++.
class Animal {
protected:
    // "protected" : accessible dans la classe ET ses sous-classes, mais pas depuis l'extérieur (comme Java)
    string nom;

public:
    Animal(string n) : nom(n) {}
    virtual ~Animal() {} // destructeur virtuel : OBLIGATOIRE dès qu'on a des méthodes virtuelles !

    // Méthode "pure virtual" : DOIT être redéfinie par toute classe fille (comme une méthode abstraite Java)
    virtual string crier() const = 0;

    // Méthode virtuelle "normale" : PEUT être redéfinie, mais a un comportement par défaut
    virtual string decrire() const {
        return nom + " fait : " + crier();
    }
};

class Chien : public Animal { // "public Animal" = héritage public (le plus courant, ~ "extends" Java)
public:
    Chien(string n) : Animal(n) {} // appelle le constructeur de la classe mère

    // "override" (C++11) : demande au compilateur de VÉRIFIER qu'on redéfinit bien une méthode
    // virtuelle existante (sécurité équivalente à @Override en Java, mais optionnelle en C++ !)
    string crier() const override {
        return "Wouf !";
    }
};

class Chat : public Animal {
public:
    Chat(string n) : Animal(n) {}
    string crier() const override {
        return "Miaou !";
    }
};

// --- Interfaces "à la C++" : une classe purement abstraite (que des méthodes = 0) ---
class Nageur {
public:
    virtual ~Nageur() {}
    virtual string nager() const = 0;
};

// --- Héritage MULTIPLE : possible en C++, contrairement à Java/C# qui limitent à une seule classe mère ---
class Canard : public Animal, public Nageur {
public:
    Canard(string n) : Animal(n) {}
    string crier() const override { return "Coin coin !"; }
    string nager() const override { return nom + " nage sur l'étang."; }
};

int main() {
    // --- Polymorphisme : manipuler des objets différents via un pointeur/référence sur la classe mère ---
    // Animal a; // ⚠️ interdit : Animal est abstraite, on ne peut pas l'instancier directement

    Chien chien("Rex");
    Chat chat("Whiskers");
    Canard canard("Donald");

    cout << chien.decrire() << endl;
    cout << chat.decrire() << endl;
    cout << canard.decrire() << endl;
    cout << canard.nager() << endl;

    // --- Polymorphisme dynamique via des pointeurs sur la classe de base ---
    cout << "\n--- Polymorphisme avec un tableau de pointeurs ---" << endl;
    Animal *animaux[] = {&chien, &chat, &canard};
    for (Animal *a : animaux) {
        // Le BON crier() est appelé pour chaque animal, grâce à "virtual" (résolution à l'exécution)
        cout << a->decrire() << endl;
    }

    // --- dynamic_cast : vérifier/convertir le type réel d'un objet via un pointeur de base ---
    // (équivalent de "instanceof" + cast en Java)
    cout << "\n--- dynamic_cast ---" << endl;
    for (Animal *a : animaux) {
        if (Nageur *nageur = dynamic_cast<Nageur *>(a)) { // renvoie nullptr si la conversion échoue
            cout << nageur->nager() << endl;
        }
    }

    cout << "\nNote : contrairement à Java/C#, C++ autorise l'héritage MULTIPLE de classes,\n"
         << "et le mot-clé 'virtual' est OBLIGATOIRE pour activer le polymorphisme dynamique\n"
         << "(sans lui, C++ utiliserait la méthode de la classe déclarée, pas celle de l'objet réel)." << endl;

    return 0;
}
