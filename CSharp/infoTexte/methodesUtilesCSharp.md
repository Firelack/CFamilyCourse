# 🔧 Méthodes et Opérateurs Utiles en C#

## 🔡 `string`

- `.Length` : longueur (propriété, pas une méthode — pas de parenthèses !).
- `$"texte {variable}"` : interpolation de chaîne (équivalent de `String.format`/concat Java).
- `.Substring(debut, longueur)` : extrait une sous-chaîne.
- `.Contains(s)` / `.StartsWith(s)` / `.EndsWith(s)` : tests de présence.
- `.Replace(ancien, nouveau)` : remplacement.
- `.Split(separateur)` : découpe en tableau. `string.Join(separateur, collection)` : l'inverse.
- `.ToUpper()` / `.ToLower()` : conversion de casse.
- `.Trim()` : enlève les espaces au début/à la fin.
- `int.Parse(s)` / `int.TryParse(s, out var n)` : conversion en nombre (`TryParse` ne lève pas
  d'exception, renvoie `true`/`false` — préférable pour une entrée utilisateur non fiable).

## 📚 `List<T>`

📞 `using System.Collections.Generic;`

- `.Add(valeur)` / `.Remove(valeur)` / `.RemoveAt(index)`.
- `.Count` : taille (propriété, pas `.size()` comme en Java !).
- `[index]` : accès direct (lève `ArgumentOutOfRangeException` si invalide).
- `.Contains(valeur)` : teste la présence.
- `.Sort()` / `.Sort((a, b) => ...)` : tri sur place / avec comparateur personnalisé.
- `.ToArray()` : convertit en tableau.

## 🗂️ `Dictionary<K, V>`

- `dico[cle] = valeur` : insère ou modifie.
- `.TryGetValue(cle, out var valeur)` : accès sécurisé, `true`/`false` sans exception.
- `.ContainsKey(cle)` : teste la présence d'une clé.
- `.Remove(cle)` : supprime une entrée.
- `foreach (var (cle, valeur) in dico)` : parcours avec déstructuration (C# 7+).

## 🧮 `HashSet<T>`

- `.Add(valeur)` (renvoie `false` si déjà présent), `.Contains(valeur)`, `.Remove(valeur)`.

## 🧭 LINQ (`using System.Linq;`)

Utilisable sur n'importe quel `IEnumerable<T>` (tableaux, `List<T>`, `Dictionary<T>`...) :

- `.Where(predicat)` : filtre (≈ `.filter()`).
- `.Select(transformation)` : transforme chaque élément (≈ `.map()`).
- `.OrderBy(cle)` / `.OrderByDescending(cle)` : tri croissant/décroissant.
- `.GroupBy(cle)` : regroupe les éléments par clé.
- `.Sum()` / `.Average()` / `.Min()` / `.Max()` / `.Count()` : agrégations.
- `.First()` / `.FirstOrDefault()` : premier élément (lève une exception / renvoie `default` si
  absent).
- `.Any(predicat)` / `.All(predicat)` : au moins un / tous vérifient la condition.
- `.ToList()` / `.ToArray()` / `.ToDictionary(cleFn, valeurFn)` : matérialise le résultat (LINQ est
  paresseux par défaut, comme les itérateurs Rust : rien n'est calculé avant `.ToList()` ou un
  `foreach`).
- `.Take(n)` / `.Skip(n)` : garde/saute les `n` premiers éléments.

## 🎯 Delegates

- `Func<T1, T2, TRetour>` : fonction avec paramètres et une valeur de retour.
- `Action<T1, T2>` : fonction sans valeur de retour (`void`).
- `Predicate<T>` : équivalent de `Func<T, bool>`, utilisé par certaines méthodes historiques.

## 💣 Exceptions courantes (`System`)

- `Exception`, `ArgumentException`, `ArgumentNullException`, `InvalidOperationException`,
  `IndexOutOfRangeException`, `DivideByZeroException`, `NullReferenceException`.
- `.Message` : message de l'exception (≈ `getMessage()` en Java).
- `throw new MonException("message");` : lève une exception.

## 🔀 Opérateurs pratiques liés au `null`

- `??` : `valeur ?? valeurParDefaut` — renvoie `valeur` si non `null`, sinon `valeurParDefaut`.
- `??=` : `variable ??= valeur` — assigne `valeur` seulement si `variable` est `null`.
- `?.` : `objet?.Methode()` — appelle seulement si `objet` n'est pas `null`, sinon renvoie `null`
  sans lever d'exception.
- `is not null` / `is null` : test explicite (préféré à `!= null` / `== null` en C# moderne).

## 🖨️ Console

- `Console.WriteLine(...)` / `Console.Write(...)` : affichage avec/sans retour à la ligne.
- `Console.ReadLine()` : lit une ligne au clavier (renvoie `string?`, peut être `null`).
- `:F2` (dans une interpolation `$"{valeur:F2}"`) : formate un nombre avec 2 décimales.
