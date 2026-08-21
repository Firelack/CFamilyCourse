// Fichier Program.cs (chapitre 5)
// Objectif : delegates, events, lambdas, et LINQ (l'une des plus grosses différences avec Java).
// Exécuter : dotnet run

using System.Linq;
using System.Collections.Generic;

// --- Delegate : un type qui représente une "signature de fonction" (comme un pointeur de fonction
// typé, ou un peu comme les traits Fn/FnMut/FnOnce de Rust). Func<> et Action<> sont des delegates
// génériques prédéfinis, à utiliser 95% du temps plutôt que d'en déclarer un nouveau.
Func<int, int, int> addition = (a, b) => a + b; // Func<Entrée1, Entrée2, ..., Retour>
Action<string> afficher = message => Console.WriteLine($"[LOG] {message}"); // Action<...> = pas de retour

Console.WriteLine($"addition(3, 4) = {addition(3, 4)}");
afficher("Delegate Action exécuté");

// --- Passer une fonction en paramètre, comme un Comparator Java ou une closure Rust ---
int Appliquer(int valeur, Func<int, int> f) => f(valeur);
Console.WriteLine($"\nAppliquer(5, x => x * x) = {Appliquer(5, x => x * x)}");

// --- LINQ : la façon idiomatique de manipuler des collections en C#, comme les Streams Java
// ou les itérateurs Rust, mais avec DEUX syntaxes possibles ---
List<int> nombres = new() { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

// Syntaxe "méthode" (la plus utilisée, ressemble aux Streams Java / iterateurs Rust)
var carresDesPairs = nombres
    .Where(n => n % 2 == 0)   // équivalent de .filter()
    .Select(n => n * n)        // équivalent de .map()
    .ToList();                 // équivalent de .collect()
Console.WriteLine($"\nCarrés des nombres pairs : {string.Join(", ", carresDesPairs)}");

// Syntaxe "requête" (façon SQL, unique à C#, n'existe dans aucun des 3 autres langages étudiés)
var carresDesPairsSql =
    from n in nombres
    where n % 2 == 0
    select n * n;
Console.WriteLine($"Même résultat en syntaxe requête : {string.Join(", ", carresDesPairsSql)}");

// --- Autres opérateurs LINQ courants ---
Console.WriteLine($"\nSomme : {nombres.Sum()}");
Console.WriteLine($"Moyenne : {nombres.Average():F2}");
Console.WriteLine($"Premier > 5 : {nombres.First(n => n > 5)}");
Console.WriteLine($"Il y en a un > 100 ? {nombres.Any(n => n > 100)}");
Console.WriteLine($"Tous positifs ? {nombres.All(n => n > 0)}");

var trie = nombres.OrderByDescending(n => n).Take(3); // les 3 plus grands
Console.WriteLine($"Top 3 : {string.Join(", ", trie)}");

// --- GroupBy : regrouper des éléments par une clé (très utilisé, pas d'équivalent direct simple en Java) ---
var motsGroupesParLongueur = new[] { "chat", "chien", "vache", "rat", "loup" }
    .GroupBy(mot => mot.Length);
Console.WriteLine("\nMots groupés par longueur :");
foreach (var groupe in motsGroupesParLongueur) {
    Console.WriteLine($"  {groupe.Key} lettres : {string.Join(", ", groupe)}");
}

// --- Events : le mécanisme "abonnement/notification" natif de C#, basé sur les delegates ---
// Pas d'équivalent direct en Java (on simule ça avec des interfaces de listener).
Console.WriteLine("\n--- Events ---");
var alarme = new Alarme();
alarme.Declenchee += (nomAlarme) => Console.WriteLine($"Réaction 1 : l'alarme '{nomAlarme}' sonne !");
alarme.Declenchee += (nomAlarme) => Console.WriteLine($"Réaction 2 : on prévient la sécurité ({nomAlarme})");
alarme.Declencher("Incendie");

Console.WriteLine(
    "\nNote : LINQ n'a pas de VRAI équivalent en Java (les Streams Java 8+ s'en rapprochent, mais\n" +
    "sans la syntaxe 'requête' façon SQL). Les 'events' C# formalisent nativement le pattern\n" +
    "observateur, alors qu'en Java on doit le recréer soi-même avec des interfaces."
);

class Alarme {
    // event : une liste de delegates auxquels on peut s'abonner avec +=
    public event Action<string>? Declenchee;

    public void Declencher(string nom) {
        Declenchee?.Invoke(nom); // "?." : n'appelle que s'il y a au moins un abonné (sinon Declenchee est null)
    }
}
