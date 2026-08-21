# 💡 Concepts Clés en C# (en partant de Java)

Ce dossier suppose que tu connais déjà la POO (via Java) : on se concentre sur ce qui est
**différent ou spécifique à C#**, pas sur les bases de l'orienté objet déjà vues.

## 🧠 Philosophie du langage

C# fonctionne comme Java : compilé vers un bytecode (IL) exécuté par un runtime managé (.NET, comme
la JVM pour Java) avec **Garbage Collector**. La syntaxe est proche de C++, mais l'esprit général
(tout est objet, pas de pointeurs par défaut, sécurité mémoire) est très proche de Java. C# a
cependant intégré beaucoup plus vite des fonctionnalités modernes (LINQ, propriétés, pattern
matching, records...) que Java, qui les a rattrapées plus tard.

## ⚡ Différences de syntaxe immédiates

| Java | C# |
| :--- | :--- |
| `public class Main { public static void main(String[] args) {...} }` | Top-level statements : le code peut s'écrire directement dans `Program.cs`, sans classe/Main explicite |
| `tableau.length` | `tableau.Length` (propriété, avec majuscule, PAS de parenthèses) |
| `liste.size()` | `liste.Count` (propriété, pas une méthode !) |
| `for (X x : collection)` | `foreach (X x in collection)` |
| `"a" + b + "c"` | `$"a{b}c"` (interpolation de chaîne) |
| `Comparator<T>` / interface fonctionnelle | `Func<T, R>` / `Action<T>` (delegates génériques prédéfinis) |
| Streams (`.stream().filter()...`) | LINQ (`.Where()...` ou syntaxe `from...where...select`) |
| `record` (Java 16+, plus limité) | `record` (plus riche : `with`, égalité par valeur, déstructuration) |

## 🏷️ Propriétés : LA grande différence avec Java

```csharp
public class Personnage {
    public string Nom { get; private set; } // équivalent condensé de : champ privé + getter + setter
    public int Pv { get; private set; }
    public bool EstVivant => Pv > 0;          // propriété calculée, sans champ derrière
}
```

- On écrit `objet.Pv` comme un champ, mais ça passe par `get`/`set` en coulisses : plus besoin
  d'écrire `getPv()`/`setPv()` à la main comme en Java.
- `{ get; private set; }` : lisible partout, modifiable seulement dans la classe.
- `{ get; init; }` (C# 9+) : modifiable uniquement à la construction de l'objet, puis immuable.
- `=>` (expression-bodied member) : syntaxe compacte pour une propriété/méthode à une seule
  expression, sans `{ return ...; }`.

## 📦 `record` : type immuable centré sur les données

```csharp
record PointRecord(int X, int Y);
var p1 = new PointRecord(3, 4);
var p2 = p1 with { Y = 10 }; // copie modifiée, immuable
```

Génère automatiquement : constructeur, `ToString()`, égalité **par valeur** (`p1 == p2` compare le
contenu, pas la référence — contrairement à une `class` classique), et l'opérateur `with` pour
créer des copies modifiées.

## 🧱 `struct` vs `class` : type valeur vs type référence

- En Java, **tout objet** est un type référence.
- En C#, `struct` crée un vrai **type valeur** : copié à l'affectation et au passage en paramètre
  (comme les types `Copy` de Rust), alors que `class` reste un type référence (comme en Java).

## 🧬 Héritage et Interfaces

- Héritage simple uniquement (`class Fille : Mere`), comme Java — pas d'héritage multiple de
  classes (contrairement à C++).
- `override` est **obligatoire** pour redéfinir une méthode `virtual`/`abstract` (le compilateur
  refuse une redéfinition silencieuse, contrairement à C++ où `override` est optionnel).
- Depuis C# 8 : une interface peut avoir des méthodes avec un **corps par défaut**, comme les
  `default` methods de Java 8+.
- `sealed class` empêche l'héritage (~ `final class` en Java).

## 🧭 LINQ : la grosse spécificité de C#

Deux syntaxes équivalentes pour manipuler des collections, comme les Streams Java mais plus riche :

```csharp
// Syntaxe "méthode" (la plus courante)
var resultat = liste.Where(x => x > 0).Select(x => x * 2).ToList();

// Syntaxe "requête" (façon SQL, unique à C#)
var resultat2 = from x in liste where x > 0 select x * 2;
```

Opérateurs courants : `Where` (filter), `Select` (map), `OrderBy`/`OrderByDescending` (sort),
`GroupBy`, `Sum`/`Average`/`Count`, `First`/`FirstOrDefault`, `Any`/`All`.

## 🔔 Delegates et Events

- `Func<Entrées..., Retour>` et `Action<Entrées...>` : types prédéfinis pour représenter des
  fonctions/lambdas, à utiliser à la place des interfaces fonctionnelles Java.
- `event` : mécanisme natif d'abonnement/notification (pattern observateur), basé sur les
  delegates. En Java, on doit reconstruire ce pattern soi-même avec des interfaces de listener.

## 🔀 Pattern Matching moderne (C# 8-12)

```csharp
string resultat = valeur switch {
    int i => $"entier {i}",
    string s when s.Length > 5 => "chaîne longue",
    Cercle(var rayon) => $"cercle de rayon {rayon}", // déstructuration de record
    { Pv: 0 } => "mort",                              // pattern sur une propriété
    _ => "autre",
};
```

Très proche du `match` de Rust, surtout combiné avec les `record`. Java a rattrapé une partie de ce
terrain avec les switch expressions et record patterns (Java 21), mais plus tard que C#.

## 💣 Gestion d'erreurs

- `try`/`catch`/`finally` : quasiment identique à Java.
- **Pas de "checked exceptions"** : contrairement à Java, aucune signature `throws` à écrire, rien
  n'oblige à capturer une exception.
- **Nullable reference types** (C# 8+, `string?`) : le compilateur *avertit* (mais n'empêche pas
  totalement) les erreurs de référence nulle — un pas dans la direction d'`Option<T>` en Rust,
  sans en avoir la garantie stricte.
- `??` (valeur par défaut si `null`), `?.` (appel sécurisé, n'exécute que si non `null`).
