// Fichier Program.cs (chapitre 4)
// Objectif : génériques avec contraintes ("where"), et les collections standards de C#.
// Exécuter : dotnet run

using System.Collections.Generic;

// --- Boite<T> générique ---
var boiteEntier = new Boite<int>(42);
var boiteTexte = new Boite<string>("Bonjour");
Console.WriteLine($"Contenu (int) : {boiteEntier.Contenu}");
Console.WriteLine($"Contenu (string) : {boiteTexte.Contenu}");

// --- Méthode générique avec contrainte "where T : IComparable<T>" ---
// Équivalent C# de "<T extends Comparable<T>>" en Java / "T: PartialOrd" en Rust.
int[] nombres = { 3, 7, 2, 9, 4 };
Console.WriteLine($"\nPlus grand nombre : {Maximum(nombres)}");

string[] mots = { "pomme", "zebre", "abricot" };
Console.WriteLine($"Plus grand (alphabétique) : {Maximum(mots)}");

// --- List<T> : l'équivalent d'ArrayList/Vec, mais TYPÉ dès le départ (contrairement à l'ArrayList Java historique) ---
Console.WriteLine("\n--- List<T> ---");
var fruits = new List<string> { "Pomme", "Banane", "Kiwi" };
fruits.Add("Mangue");
fruits.Remove("Banane");
Console.WriteLine($"Fruits : {string.Join(", ", fruits)}"); // string.Join ~ .join() de Java

// --- Dictionary<K, V> : l'équivalent de HashMap ---
Console.WriteLine("\n--- Dictionary<K, V> ---");
var ages = new Dictionary<string, int> {
    ["Alice"] = 25, // syntaxe d'initialisation façon "indexeur"
    ["Bob"] = 30
};
ages["Charlie"] = 22;

if (ages.TryGetValue("Alice", out int ageAlice)) { // TryGetValue : évite l'exception si absent
    Console.WriteLine($"Alice a {ageAlice} ans");
}
foreach (var (nom, age) in ages) { // déstructuration façon Rust/C++17, sur les KeyValuePair
    Console.WriteLine($"{nom} -> {age} ans");
}

// --- HashSet<T> : ensemble sans doublons ---
Console.WriteLine("\n--- HashSet<T> ---");
var set = new HashSet<int> { 1, 2, 2, 3 }; // le doublon "2" est ignoré
Console.WriteLine($"Set : {{{string.Join(", ", set)}}} (taille = {set.Count})");

// --- Generics avec plusieurs contraintes ---
Console.WriteLine("\n--- Generics avec contrainte de constructeur ---");
var chien = CreerInstance<Chien>(); // "where T : new()" garantit qu'on peut faire new T()
Console.WriteLine(chien.Aboyer());

Console.WriteLine(
    "\nNote : contrairement aux generics Java (qui disparaissent à l'exécution par 'type erasure'),\n" +
    "les generics C# sont RÉIFIÉS : le type réel est conservé à l'exécution, ce qui les rend un peu\n" +
    "plus proches des templates C++ / génériques Rust en termes de performance."
);

// --- Fonctions locales (doivent apparaître avant les déclarations de types ci-dessous) ---

// "where T : IComparable<T>" : contrainte de type, comme "T: PartialOrd" en Rust
static T Maximum<T>(T[] tableau) where T : IComparable<T> {
    T plusGrand = tableau[0];
    foreach (var element in tableau) {
        if (element.CompareTo(plusGrand) > 0) {
            plusGrand = element;
        }
    }
    return plusGrand;
}

static T CreerInstance<T>() where T : new() => new T(); // contrainte "new()" : T doit avoir un constructeur sans paramètre

// --- Définitions de types ---

class Boite<T> {
    public T Contenu { get; }
    public Boite(T contenu) { Contenu = contenu; }
}

class Chien {
    public string Aboyer() => "Wouf !";
}
