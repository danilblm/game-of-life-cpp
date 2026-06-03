# Jeu de la Vie (Conway) — C++

Implémentation **console et portable** du *Jeu de la Vie de Conway* en C++ : un automate cellulaire où chaque cellule naît, survit ou meurt selon le nombre de ses voisines vivantes.

Le rendu se fait avec des **codes ANSI** (pas de `windows.h` / `conio.h`), donc le programme tourne sous **Linux, macOS et tout terminal Windows moderne** (Windows Terminal).

## Aperçu

Sortie réelle du programme (`life 14 7 4 0 glider`) — un **planeur** qui se déplace en diagonale au fil des générations :

```text
generation 0          generation 1          generation 2          generation 3

. # . . . . .         . . . . . . .         . . . . . . .         . . . . . . .
. . # . . . .         # . # . . . .         . . # . . . .         . # . . . . .
# # # . . . .         . # # . . . .         # . # . . . .         . . # # . . .
. . . . . . .         . # . . . . .         . # # . . . .         . # # . . . .
. . . . . . .         . . . . . . .         . . . . . . .         . . . . . . .
```

Avec `random`, la grille s'anime à partir d'une configuration aléatoire et évolue selon les règles ci-dessous.

## Règles (B3/S23)

- Une cellule **morte** avec exactement **3 voisines vivantes** devient vivante (naissance).
- Une cellule **vivante** avec **2 ou 3 voisines** survit.
- Dans tous les autres cas, elle meurt (sous-population ou surpopulation).

## Fonctionnalités

- Grille de **taille paramétrable** (`std::vector`, plus de dimensions figées)
- **Initialisation aléatoire** ou motif **planeur (glider)**
- Animation en place via codes ANSI, vitesse réglable
- Tout en **C++17 standard**, multiplateforme

## Compilation

```bash
g++ -std=c++17 -O2 main.cpp -o life
```

> 🪟 **Sous Windows (MinGW)** : pour un exécutable autonome (sans DLL manquante au lancement), compilez en statique :
> ```bash
> g++ -std=c++17 -O2 -static main.cpp -o life
> ```

## Utilisation

```bash
life [largeur] [hauteur] [générations] [délai_ms] [motif]
```

| Argument | Défaut | Description |
| --- | --- | --- |
| `largeur` | `40` | Nombre de colonnes |
| `hauteur` | `20` | Nombre de lignes |
| `générations` | `300` | Nombre d'itérations |
| `délai_ms` | `120` | Pause entre deux images (ms) |
| `motif` | `random` | `random` (aléatoire) ou `glider` |

### Exemples

```bash
life                       # 40x20 aléatoire, 300 générations
life 60 30 500 80          # 60x30, 500 générations, 80 ms/image
life 40 20 400 120 glider  # anime un planeur
```

> 💡 Sous Windows, lancez le programme dans **Windows Terminal** pour un affichage ANSI correct.

## Stack

`C++17` · Standard Library · rendu console ANSI · multiplateforme
