// Fichier Program.cs (chapitre 1)
// Objectif : syntaxe de base de C#, et ce qui diffère de Java dès le départ.
// Exécuter : dotnet run

// --- "Top-level statements" (C# 9+) : pas besoin d'écrire "class Program { static void Main() }" !
// C'est LA première différence visible avec Java, qui impose toujours une classe + Main.
// (Le compilateur génère cette classe/méthode automatiquement en coulisses.)

// --- var : inférence de type, comme "auto" en C++ ou l'inférence Rust ---
var age = 25;              // déduit : int
var nom = "Alice";         // déduit : string
var taille = 1.68;         // déduit : double
Console.WriteLine($"{nom} a {age} ans et mesure {taille} m");
// ^ Interpolation de chaîne ($"...") : équivalent plus lisible de "nom + " a " + age + ..." en Java

// --- Types de base : proches de Java, avec quelques différences de nommage ---
int entier = 10;
double flottant = 3.14;
bool vraiOuFaux = true;
char lettre = 'C';
string texte = "Bonjour"; // ATTENTION : "string" (minuscule) est un alias de "String", les deux existent
Console.WriteLine($"{entier} {flottant} {vraiOuFaux} {lettre} {texte}");

// --- Constantes ---
const int MAX_JOUEURS = 4; // "const" en C# ~ "final" en Java, mais résolu à la compilation
Console.WriteLine($"\nMax joueurs : {MAX_JOUEURS}");

// --- Tableaux ---
int[] nombres = { 1, 2, 3, 4, 5 }; // syntaxe différente de Java (int[] nombres = {1,2,3,4,5};  identique en fait !)
Console.WriteLine($"\nTaille du tableau : {nombres.Length}"); // .Length (propriété, PAS .length() comme en Java !)
foreach (int n in nombres) { // foreach au lieu de "for (int n : nombres)"
    Console.Write($"{n} ");
}
Console.WriteLine();

// --- Structures de contrôle : identiques à Java dans l'ensemble ---
Console.WriteLine("\nBoucle for :");
for (int i = 0; i < 3; i++) {
    Console.WriteLine($"Iteration {i}");
}

// --- switch expression (C# 8+) : bien plus concis que le switch classique de Java ---
int jour = 2;
string nomJour = jour switch {
    1 => "Lundi",
    2 => "Mardi",
    3 => "Mercredi",
    _ => "Autre jour" // "_" = joker, comme en Rust !
};
Console.WriteLine($"\nJour : {nomJour}");

// --- Méthodes locales : une fonction définie à l'intérieur d'un bloc de code (impossible en Java) ---
int Addition(int a, int b) => a + b; // "expression-bodied member" : syntaxe compacte sans accolades ni "return"
Console.WriteLine($"\nSomme de 3 et 4 = {Addition(3, 4)}");

// --- Paramètres par défaut (comme C++, impossible en Java) ---
void Saluer(string nom, string civilite = "cher") {
    Console.WriteLine($"Bonjour, {civilite} {nom} !");
}
Saluer("Bob");
Saluer("Charlie", "estimé");

// --- Nullable reference types (C# 8+) : le "?" rend explicite qu'une variable peut être null ---
string? peutEtreNull = null; // sans "?", le compilateur avertirait qu'assigner null est dangereux
Console.WriteLine($"\npeutEtreNull est null ? {peutEtreNull is null}");

// L'opérateur ?? donne une valeur par défaut si la variable est null (comme unwrap_or en Rust)
string valeurSure = peutEtreNull ?? "valeur par défaut";
Console.WriteLine($"Valeur sûre : {valeurSure}");

Console.WriteLine(
    "\nNote : C# ressemble beaucoup à Java dans son fonctionnement (compilé en bytecode IL,\n" +
    "Garbage Collector, tout est objet), mais la syntaxe a beaucoup évolué : var, string\n" +
    "interpolation, switch expressions, nullable reference types... Le reste de ce dossier se\n" +
    "concentre sur ce qui est VRAIMENT différent de Java."
);
