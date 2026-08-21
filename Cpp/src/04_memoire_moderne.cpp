// Fichier 04_memoire_moderne.cpp
// Objectif : new/delete, RAII, et les smart pointers (unique_ptr, shared_ptr) qui rendent
// la gestion mémoire C++ moderne beaucoup plus sûre que le malloc/free du C.
// Compiler : g++ -std=c++17 -Wall 04_memoire_moderne.cpp -o memoire_moderne && ./memoire_moderne

#include <iostream>
#include <memory> // unique_ptr, shared_ptr
#include <string>
using namespace std;

class Ressource {
    string nom;
public:
    Ressource(string n) : nom(n) { cout << "Ressource '" << nom << "' créée" << endl; }
    ~Ressource() { cout << "Ressource '" << nom << "' détruite" << endl; }
    void utiliser() const { cout << "Utilisation de '" << nom << "'" << endl; }
};

int main() {
    // --- new / delete : l'équivalent C++ "à l'ancienne" de malloc/free ---
    // Contrairement à malloc, "new" appelle aussi le CONSTRUCTEUR de l'objet.
    cout << "--- new / delete (à éviter en C++ moderne) ---" << endl;
    Ressource *r = new Ressource("Manuelle");
    r->utiliser();
    delete r; // ⚠️ toujours obligatoire, exactement comme free() en C : mêmes risques d'oubli !

    // --- RAII (Resource Acquisition Is Initialization) : LE principe central du C++ moderne ---
    // On lie la durée de vie d'une ressource à celle d'un objet : le destructeur s'en occupe
    // automatiquement, même en cas d'exception. Plus besoin de "delete" manuel !
    cout << "\n--- RAII avec un objet sur la pile ---" << endl;
    {
        Ressource surPile("Automatique");
        surPile.utiliser();
    } // <- destructeur appelé automatiquement ici, garanti même si une exception avait été levée

    // --- unique_ptr : pointeur intelligent, UN SEUL propriétaire (équivalent de l'ownership Rust !) ---
    cout << "\n--- unique_ptr ---" << endl;
    {
        unique_ptr<Ressource> up = make_unique<Ressource>("Unique");
        up->utiliser();
        // unique_ptr<Ressource> up2 = up; // ⚠️ erreur de compilation : pas de copie possible !
        unique_ptr<Ressource> up2 = move(up); // mais on peut le DÉPLACER (move), comme en Rust
        if (!up) { // up est maintenant "vide" (nullptr) après le move
            cout << "up est maintenant vide après le move" << endl;
        }
        up2->utiliser();
    } // <- la Ressource est automatiquement détruite ici, pas besoin de delete !

    // --- shared_ptr : pointeur intelligent, PLUSIEURS propriétaires (compteur de références) ---
    cout << "\n--- shared_ptr ---" << endl;
    {
        shared_ptr<Ressource> sp1 = make_shared<Ressource>("Partagée");
        cout << "Compteur de références : " << sp1.use_count() << endl;
        {
            shared_ptr<Ressource> sp2 = sp1; // copie AUTORISÉE : incrémente le compteur
            cout << "Compteur après copie : " << sp1.use_count() << endl;
            sp2->utiliser();
        } // <- sp2 est détruit ici, le compteur redescend à 1 (mais la Ressource survit encore)
        cout << "Compteur après le bloc interne : " << sp1.use_count() << endl;
    } // <- sp1 est détruit ici, le compteur tombe à 0 : LÀ la Ressource est enfin détruite

    cout << "\nNote : en C++ moderne, on n'utilise quasiment plus jamais new/delete directement.\n"
         << "unique_ptr ~ ownership exclusif de Rust (Box<T>). shared_ptr ~ Rc<T>/Arc<T> de Rust.\n"
         << "Contrairement à Java/C#, il n'y a PAS de Garbage Collector : la libération est\n"
         << "déterministe, basée sur le comptage de références et la portée (scope)." << endl;

    return 0;
}
