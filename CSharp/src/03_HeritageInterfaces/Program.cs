// Fichier Program.cs (chapitre 3)
// Objectif : héritage, interfaces (avec méthodes par défaut), sealed, abstract, en C#.
// Exécuter : dotnet run

Animal[] animaux = { new Chien("Rex"), new Chat("Whiskers"), new Canard("Donald") };

foreach (var a in animaux) {
    Console.WriteLine(a.Decrire()); // comme en Java, TOUT est virtuel par défaut (contrairement à C++ !)
}

// --- Utilisation d'une interface avec méthode par défaut ---
Console.WriteLine("\n--- Interface INageur ---");
foreach (var a in animaux) {
    if (a is INageur nageur) { // "is" + pattern matching : équivalent d'instanceof + cast en une fois
        Console.WriteLine(nageur.Nager());
        Console.WriteLine(nageur.Info()); // méthode par défaut de l'interface, pas redéfinie par Canard
    }
}

Console.WriteLine(
    "\nNote : contrairement à C++, C# (comme Java) ne permet PAS l'héritage multiple de classes.\n" +
    "Mais une classe peut implémenter PLUSIEURS interfaces, et depuis C# 8, une interface peut\n" +
    "avoir des méthodes avec un corps par défaut (comme les 'default methods' de Java 8+)."
);

// --- Définitions ---

abstract class Animal {
    protected string Nom { get; }

    protected Animal(string nom) { Nom = nom; }

    // Méthode abstraite : DOIT être redéfinie (comme en Java, pas de "= 0" comme en C++)
    public abstract string Crier();

    // Méthode "virtual" : PEUT être redéfinie (équivalent d'une méthode normale Java, "virtual"
    // par défaut ; en C#, il FAUT écrire "virtual" explicitement pour AUTORISER la redéfinition)
    public virtual string Decrire() => $"{Nom} fait : {Crier()}";
}

class Chien : Animal {
    public Chien(string nom) : base(nom) {} // "base(...)" appelle le constructeur parent (= "super" en Java)
    public override string Crier() => "Wouf !"; // "override" est OBLIGATOIRE en C# (contrairement à C++)
}

class Chat : Animal {
    public Chat(string nom) : base(nom) {}
    public override string Crier() => "Miaou !";
}

// --- Interface avec méthode par défaut (C# 8+), comme "default" en Java ---
interface INageur {
    string Nager();

    string Info() => "Cet animal sait nager."; // implémentation par défaut, redéfinissable
}

// "sealed" empêcherait toute classe d'hériter de Canard (équivalent de "final class" en Java)
class Canard : Animal, INageur {
    public Canard(string nom) : base(nom) {}
    public override string Crier() => "Coin coin !";
    public string Nager() => $"{Nom} nage sur l'étang.";
    // Info() de INageur n'est pas redéfini : garde l'implémentation par défaut de l'interface
}
