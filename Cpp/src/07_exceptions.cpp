// Fichier 07_exceptions.cpp
// Objectif : try/catch/throw en C++. Similaire à Java, avec quelques différences importantes.
// Compiler : g++ -std=c++17 -Wall 07_exceptions.cpp -o exceptions && ./exceptions

#include <iostream>
#include <stdexcept> // exceptions standard : runtime_error, invalid_argument, out_of_range...
#include <string>
using namespace std;

// --- Exception personnalisée : hérite de std::exception (comme "extends Exception" en Java) ---
class SoldeInsuffisantException : public runtime_error {
public:
    SoldeInsuffisantException(double manque)
        : runtime_error("Solde insuffisant : il manque " + to_string(manque) + " EUR") {}
};

class CompteBancaire {
    double solde;
public:
    CompteBancaire(double soldeInitial) : solde(soldeInitial) {}

    // "throw" lève une exception, comme en Java. Contrairement à Java, PAS de "throws" obligatoire
    // dans la signature : le compilateur C++ n'oblige jamais à déclarer/gérer les exceptions.
    void debiter(double montant) {
        if (montant < 0) {
            throw invalid_argument("Le montant doit être positif");
        }
        if (montant > solde) {
            throw SoldeInsuffisantException(montant - solde);
        }
        solde -= montant;
    }

    double getSolde() const { return solde; }
};

double diviser(double a, double b) {
    if (b == 0) {
        throw runtime_error("Division par zéro impossible");
    }
    return a / b;
}

int main() {
    // --- try/catch classique ---
    cout << "--- try/catch simple ---" << endl;
    try {
        cout << "10 / 2 = " << diviser(10, 2) << endl;
        cout << "10 / 0 = " << diviser(10, 0) << endl; // lève une exception ici
        cout << "Cette ligne ne s'exécute jamais" << endl;
    } catch (const runtime_error &e) {
        // .what() : méthode standard pour récupérer le message d'une exception (~ getMessage() en Java)
        cout << "Erreur attrapée : " << e.what() << endl;
    }

    // --- Plusieurs types d'exceptions, catch du plus spécifique au plus général ---
    cout << "\n--- Compte bancaire avec exception personnalisée ---" << endl;
    CompteBancaire compte(100.0);
    try {
        compte.debiter(30.0);
        cout << "Débit réussi, solde : " << compte.getSolde() << endl;
        compte.debiter(1000.0); // lève une SoldeInsuffisantException
    } catch (const SoldeInsuffisantException &e) {
        cout << "Erreur spécifique : " << e.what() << endl;
    } catch (const invalid_argument &e) {
        cout << "Argument invalide : " << e.what() << endl;
    } catch (const exception &e) {
        // catch générique : filet de sécurité pour toute autre exception standard
        cout << "Erreur générique : " << e.what() << endl;
    }

    // --- catch(...) : attrape absolument TOUT, même des types qui ne sont pas des exceptions std ---
    cout << "\n--- catch(...) ---" << endl;
    try {
        throw 42; // en C++, on peut techniquement "throw" n'importe quel type (pas seulement une exception) !
    } catch (...) {
        cout << "Quelque chose a été levé (catch générique, on ne sait pas quoi précisément)" << endl;
    }

    cout << "\nNote : contrairement à Java, C++ n'a PAS de 'checked exceptions' (rien n'oblige à\n"
         << "déclarer ou gérer une exception). Beaucoup de code C++ moderne préfère d'ailleurs\n"
         << "std::optional/std::expected (proches d'Option/Result en Rust) aux exceptions pour\n"
         << "les erreurs 'attendues', et réserve les exceptions aux cas vraiment exceptionnels." << endl;

    return 0;
}
