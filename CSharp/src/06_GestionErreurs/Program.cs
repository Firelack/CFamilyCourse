// Fichier Program.cs (chapitre 6)
// Objectif : try/catch/finally, exceptions personnalisées, nullable reference types.
// Exécuter : dotnet run

// --- try/catch/finally : très proche de Java ---
Console.WriteLine("--- try/catch/finally ---");
try {
    Console.WriteLine($"10 / 2 = {Diviser(10, 2)}");
    Console.WriteLine($"10 / 0 = {Diviser(10, 0)}"); // lève une exception ici
    Console.WriteLine("Cette ligne ne s'exécute jamais");
} catch (DivideByZeroException e) {
    Console.WriteLine($"Erreur attrapée : {e.Message}");
} finally {
    // s'exécute TOUJOURS, qu'il y ait eu une exception ou non (comme en Java)
    Console.WriteLine("Bloc finally exécuté");
}

// --- Exception personnalisée : hérite d'Exception, comme "extends Exception" en Java ---
Console.WriteLine("\n--- Compte bancaire avec exception personnalisée ---");
var compte = new CompteBancaire(100.0);
try {
    compte.Debiter(30.0);
    Console.WriteLine($"Débit réussi, solde : {compte.Solde}");
    compte.Debiter(1000.0); // lève une SoldeInsuffisantException
} catch (SoldeInsuffisantException e) {
    Console.WriteLine($"Erreur spécifique : {e.Message}");
} catch (ArgumentException e) {
    // catch plus général : filet de sécurité pour d'autres erreurs d'argument
    Console.WriteLine($"Argument invalide : {e.Message}");
}

// --- Pas de "checked exceptions" en C# (contrairement à Java) : aucune signature "throws" à écrire ---
// Rien n'oblige à entourer un appel de try/catch, ni à déclarer les exceptions possibles.

// --- Nullable reference types (C# 8+) : le compilateur AIDE à éviter les NullReferenceException ---
Console.WriteLine("\n--- Nullable reference types ---");
string? peutEtreNull = TrouverUtilisateur(99); // peut renvoyer null, le "?" le rend explicite
if (peutEtreNull is not null) {
    Console.WriteLine($"Utilisateur trouvé : {peutEtreNull}");
} else {
    Console.WriteLine("Aucun utilisateur avec cet id");
}

// --- Opérateurs pratiques pour gérer le null sans exception ---
string valeurSure = TrouverUtilisateur(99) ?? "Invité"; // ?? = valeur par défaut si null
Console.WriteLine($"Valeur sûre : {valeurSure}");

// L'opérateur "!" (null-forgiving) : dit au compilateur "je te promets que ce n'est pas null"
// (à utiliser avec précaution : aucune vérification réelle à l'exécution, juste un silence du compilateur)
// string dangereux = TrouverUtilisateur(99)!; // supprime l'avertissement, mais RISQUE de planter quand même

Console.WriteLine(
    "\nNote : contrairement à Java, C# n'a pas de 'checked exceptions'. En revanche, les nullable\n" +
    "reference types (C# 8+) rapprochent C# de l'esprit d'Option<T> en Rust : le compilateur\n" +
    "PRÉVIENT (mais n'empêche pas complètement) les erreurs de référence nulle."
);

// --- Fonctions et types utilisés ---

double Diviser(double a, double b) {
    if (b == 0) throw new DivideByZeroException("Division par zéro impossible");
    return a / b;
}

string? TrouverUtilisateur(int id) => id switch {
    1 => "Alice",
    2 => "Bob",
    _ => null,
};

class SoldeInsuffisantException : Exception {
    public double Manque { get; }
    public SoldeInsuffisantException(double manque)
        : base($"Solde insuffisant : il manque {manque:F2} €") {
        Manque = manque;
    }
}

class CompteBancaire {
    public double Solde { get; private set; }
    public CompteBancaire(double soldeInitial) { Solde = soldeInitial; }

    public void Debiter(double montant) {
        if (montant < 0) throw new ArgumentException("Le montant doit être positif");
        if (montant > Solde) throw new SoldeInsuffisantException(montant - Solde);
        Solde -= montant;
    }
}
