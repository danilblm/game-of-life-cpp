# Jeu de la Vie (Conway) — C++

Implémentation **console** du *Jeu de la Vie de Conway* en C++ : un automate cellulaire où chaque cellule naît, survit ou meurt selon le nombre de ses voisines vivantes.

## Règles (B3/S23)

- Une cellule **morte** avec exactement **3 voisines vivantes** devient vivante.
- Une cellule **vivante** avec **2 ou 3 voisines** survit.
- Dans tous les autres cas, elle meurt (sous-population ou surpopulation).

## Fonctionnalités

- Grille **10×10** saisie cellule par cellule (`1` = vivante, `0` = morte)
- Simulation en temps réel
- Contrôles clavier pendant la simulation :
  - **P** — pause / reprise
  - **S** — arrêter
  - **E** — effacer la grille

## Compilation & exécution

> ⚠️ Projet **Windows** : utilise `windows.h` et `conio.h`.

```bash
g++ main.cpp -o jeu_de_la_vie.exe
jeu_de_la_vie.exe
```

Ou ouvrez `Jeu de la vie.cbp` dans **Code::Blocks**.

## Stack

`C++` · `Code::Blocks` · Console Windows
