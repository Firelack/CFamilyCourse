// Fichier 08_operateurs_surcharge.cpp
// Objectif : la surcharge d'opérateurs, une spécificité de C++ qui n'existe pas (de la même
// façon) en Java ni en C. Permet de faire fonctionner +, -, ==, <<... sur ses propres types.
// Compiler : g++ -std=c++17 -Wall 08_operateurs_surcharge.cpp -o operateurs && ./operateurs

#include <iostream>
using namespace std;

class Vecteur2D {
public:
    double x, y;

    Vecteur2D(double x = 0, double y = 0) : x(x), y(y) {}

    // --- Surcharge de l'opérateur + : permet d'écrire "v1 + v2" au lieu de "v1.additionner(v2)" ---
    Vecteur2D operator+(const Vecteur2D &autre) const {
        return Vecteur2D(x + autre.x, y + autre.y);
    }

    // --- Surcharge de l'opérateur - ---
    Vecteur2D operator-(const Vecteur2D &autre) const {
        return Vecteur2D(x - autre.x, y - autre.y);
    }

    // --- Surcharge de l'opérateur * pour une multiplication par un scalaire (Vecteur2D * double) ---
    Vecteur2D operator*(double facteur) const {
        return Vecteur2D(x * facteur, y * facteur);
    }

    // --- Surcharge de l'opérateur == : permet d'écrire "v1 == v2" ---
    bool operator==(const Vecteur2D &autre) const {
        return x == autre.x && y == autre.y;
    }

    // --- Surcharge de l'opérateur [] : accès façon tableau, v[0] = x, v[1] = y ---
    double operator[](int index) const {
        if (index == 0) return x;
        if (index == 1) return y;
        throw out_of_range("Index invalide pour Vecteur2D");
    }
};

// --- Surcharge de << (en dehors de la classe, car l'opérande de gauche est "cout", pas un Vecteur2D) ---
// C'est ce qui permet d'écrire "cout << monVecteur" directement, comme pour un type natif.
ostream &operator<<(ostream &os, const Vecteur2D &v) {
    os << "(" << v.x << ", " << v.y << ")";
    return os;
}

int main() {
    Vecteur2D a(1.0, 2.0);
    Vecteur2D b(3.0, 4.0);

    // --- Grâce à la surcharge, on manipule Vecteur2D comme un type numérique natif ---
    Vecteur2D somme = a + b;
    Vecteur2D difference = a - b;
    Vecteur2D mise_a_echelle = a * 2.5;

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "a + b = " << somme << endl;
    cout << "a - b = " << difference << endl;
    cout << "a * 2.5 = " << mise_a_echelle << endl;

    cout << "\na == b ? " << boolalpha << (a == b) << endl;
    cout << "a == a ? " << boolalpha << (a == a) << endl;

    cout << "\na[0] = " << a[0] << ", a[1] = " << a[1] << endl;

    cout << "\nNote : Java et C# n'autorisent PAS la surcharge d'opérateurs arbitraires (C# autorise\n"
         << "une liste limitée d'opérateurs à surcharger ; Java ne l'autorise pas du tout, sauf pour\n"
         << "+ sur les String, câblé dans le langage). C'est une spécificité forte de C++, puissante\n"
         << "mais à utiliser avec parcimonie pour ne pas rendre le code moins lisible." << endl;

    return 0;
}
