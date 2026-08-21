// Fichier Program.cs (chapitre 7)
// Objectif : switch expressions, pattern matching moderne (C# 8-12), records + pattern matching.
// Exécuter : dotnet run

// --- switch expression : version "expression" du switch, renvoie une valeur (comme match en Rust) ---
int note = 15;
string mention = note switch {
    >= 16 => "Très bien",       // pattern de comparaison (C# 9+)
    >= 14 => "Bien",
    >= 12 => "Assez bien",
    >= 10 => "Passable",
    _ => "Insuffisant",
};
Console.WriteLine($"Note {note} -> {mention}");

// --- Pattern matching sur le TYPE (comme "is Type variable") ---
object[] valeurs = { 42, "texte", 3.14, true, null! };
Console.WriteLine("\n--- Pattern matching sur le type ---");
foreach (var valeur in valeurs) {
    string description = valeur switch {
        int i => $"C'est un entier : {i}",
        string s => $"C'est une chaîne de {s.Length} caractères",
        double d => $"C'est un flottant : {d}",
        bool b => $"C'est un booléen : {b}",
        null => "C'est null",
        _ => "Type inconnu",
    };
    Console.WriteLine(description);
}

// --- Pattern matching sur les records (déstructuration), très proche du match Rust sur un enum ---
Console.WriteLine("\n--- Pattern matching sur des records ---");
Forme[] formes = { new Cercle(3.0), new Rectangle(4.0, 5.0), new Triangle(6.0, 2.0) };
foreach (var forme in formes) {
    double aire = forme switch {
        Cercle(var rayon) => Math.PI * rayon * rayon,               // déstructuration positionnelle
        Rectangle(var largeur, var hauteur) => largeur * hauteur,
        Triangle(var baseF, var hauteur) => baseF * hauteur / 2,
        _ => throw new ArgumentException("Forme inconnue"),
    };
    Console.WriteLine($"{forme} -> aire = {aire:F2}");
}

// --- Pattern "property" : filtre sur les propriétés d'un objet directement dans le pattern ---
Console.WriteLine("\n--- Pattern matching sur des propriétés ---");
var personnages = new[] {
    new Personnage("Alice", 100),
    new Personnage("Bob", 0),
    new Personnage("Charlie", 15),
};
foreach (var p in personnages) {
    string etat = p switch {
        { Pv: 0 } => $"{p.Nom} est mort",
        { Pv: < 20 } => $"{p.Nom} est en danger critique",
        { Pv: >= 20 } => $"{p.Nom} va bien",
    };
    Console.WriteLine(etat);
}

// --- Combinaison de patterns avec "and" / "or" / "not" (C# 9+) ---
Console.WriteLine("\n--- Combinaison de patterns ---");
foreach (int n in new[] { -5, 0, 5, 50, 150 }) {
    string categorie = n switch {
        < 0 => "négatif",
        0 => "zéro",
        > 0 and <= 100 => "positif, entre 1 et 100",
        > 100 => "positif, supérieur à 100",
    };
    Console.WriteLine($"{n} -> {categorie}");
}

Console.WriteLine(
    "\nNote : le pattern matching C# moderne (surtout depuis C# 8/9) se rapproche beaucoup de\n" +
    "'match' en Rust, notamment avec les records. Java a rattrapé une partie de ce terrain avec\n" +
    "les 'switch expressions' et 'record patterns' (Java 21), mais plus récemment que C#."
);

// --- Types utilisés (records = équivalent des enums Rust à données pour ce genre de pattern) ---
abstract record Forme;
record Cercle(double Rayon) : Forme;
record Rectangle(double Largeur, double Hauteur) : Forme;
record Triangle(double Base, double Hauteur) : Forme;

record Personnage(string Nom, int Pv);
