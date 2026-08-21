// Fichier Program.cs (chapitre 2)
// Objectif : les propriétés (LA grande différence avec Java), records, classes vs structs.
// Exécuter : dotnet run

// --- Utilisation avant définition : en C#, l'ordre des déclarations dans le fichier n'a pas
// d'importance (contrairement à C), donc on peut utiliser Personnage ici même s'il est plus bas.
var alice = new Personnage("Alice", 100);
var bob = new Personnage("Bob", 80);

Console.WriteLine(alice.Decrire());
Console.WriteLine(bob.Decrire());

// --- Propriétés : on écrit "objet.Pv" comme un champ, mais ça passe par get/set en coulisses ---
Console.WriteLine($"\nPv de Bob (via la propriété) : {bob.Pv}");
bob.SubirDegats(30);
Console.WriteLine($"Après dégâts : {bob.Decrire()}");

// --- Propriété en lecture seule calculée (comme un getter Java sans setter) ---
Console.WriteLine($"Bob est vivant : {bob.EstVivant}"); // pas de parenthèses : c'est une propriété, pas une méthode !

// --- Propriété auto-implémentée avec un setter "init" : modifiable seulement à la création ---
var config = new Configuration { Volume = 80, Difficulte = "Normal" };
Console.WriteLine($"\nConfiguration : Volume={config.Volume}, Difficulté={config.Difficulte}");
// config.Volume = 100; // ⚠️ interdit : "init" ne permet la modification qu'à la construction

// --- record (C# 9+) : type immuable centré sur les DONNÉES, avec égalité par valeur automatique ---
// N'existe pas en Java (les "records" Java 16+ sont proches, mais record C# est plus riche).
var point1 = new PointRecord(3, 4);
var point2 = new PointRecord(3, 4);
Console.WriteLine($"\npoint1 = {point1}"); // ToString() généré automatiquement, affiche les champs !
Console.WriteLine($"point1 == point2 ? {point1 == point2}"); // égalité par VALEUR, pas par référence !

// "with" : crée une COPIE modifiée d'un record (pattern très utilisé en C# moderne)
var point3 = point1 with { Y = 10 };
Console.WriteLine($"point3 (copie modifiée) = {point3}");

// --- struct vs class : en C#, "struct" est un TYPE VALEUR (comme en C++), "class" un TYPE RÉFÉRENCE ---
// C'est une différence majeure avec Java, où TOUT objet est un type référence.
var v1 = new VecteurStruct(1, 2);
var v2 = v1; // copie de LA VALEUR (struct), contrairement à une class où ce serait la même référence !
v2.X = 99;
Console.WriteLine($"\nv1.X = {v1.X} (inchangé), v2.X = {v2.X} (modifié séparément)");

Console.WriteLine(
    "\nNote : en Java, TOUT objet est un type référence (deux variables peuvent pointer\n" +
    "vers le même objet). En C#, 'struct' donne un vrai type valeur, copié à l'affectation,\n" +
    "un peu comme les types Copy de Rust."
);

// --- Définitions des types utilisés ci-dessus ---

class Personnage {
    // --- Propriété auto-implémentée : équivalent condensé d'un champ privé + getter/setter Java ---
    public string Nom { get; private set; } // lisible partout, modifiable seulement dans la classe
    public int Pv { get; private set; }

    public Personnage(string nom, int pv) {
        Nom = nom;
        Pv = pv;
    }

    public string Decrire() => $"{Nom} - {Pv} PV"; // expression-bodied member

    public void SubirDegats(int degats) {
        Pv = Math.Max(0, Pv - degats);
    }

    // --- Propriété calculée (get uniquement, pas de champ derrière) ---
    public bool EstVivant => Pv > 0;
}

class Configuration {
    // "init" (C# 9+) : la propriété ne peut être définie qu'à la construction de l'objet,
    // via la syntaxe d'initialisation d'objet { Prop = valeur }, puis devient immuable.
    public int Volume { get; init; }
    public string Difficulte { get; init; } = "Normal"; // valeur par défaut possible
}

// --- record : génère automatiquement constructeur, ToString(), égalité par valeur, et "with" ---
record PointRecord(int X, int Y);

// --- struct : type VALEUR, copié à chaque affectation/passage en paramètre ---
struct VecteurStruct {
    public double X;
    public double Y;
    public VecteurStruct(double x, double y) { X = x; Y = y; }
}
