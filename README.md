# Space Invaders (C & SDL2) 🚀

Un clone du célèbre jeu d'arcade rétro *Space Invaders*, développé en langage C avec la bibliothèque graphique SDL2. 

*(Ajoute ici une capture d'écran de ton jeu en action !)*
`![Screenshot du jeu](chemin/vers/image.png)`

## 🎯 Fonctionnalités actuelles

- Déplacement fluide du vaisseau (avec gestion des collisions et limites de l'écran).
- Essaim d'aliens avec système de descente et d'animation.
- Système de tirs (missiles du joueur et bombes ennemies).
- Gestion des boucliers destructibles.
- Animations des dégâts et de destruction.
- **Support Manette** (Plug & Play) et Clavier.
- Écrans de victoire, de défaite et menu interactif.

## 🛠️ Prérequis et Installation

Ce projet est conçu pour être compilé sous environnement Linux. Il nécessite le compilateur `gcc`, l'utilitaire `make`, et les bibliothèques de développement SDL2.

**Installation des dépendances :**

*Sous Arch Linux / Manjaro :*
```bash
sudo pacman -S base-devel sdl2 sdl2_ttf

```

*Sous Debian / Ubuntu :*

```bash
sudo apt update
sudo apt install build-essential libsdl2-dev libsdl2-ttf-dev

```

## 🚀 Compilation et Exécution

Le projet utilise un Makefile classique pour faciliter la compilation.
Placez-vous à la racine du projet et exécutez :

```bash
make clean && make
```

## 🎮 Contrôles

Le jeu est jouable au clavier ou à la manette (détectée automatiquement au démarrage).

| Action | Clavier | Manette (Type Xbox/Generic) |
| --- | --- | --- |
| **Aller à gauche** | `Q` | Joystick Gauche |
| **Aller à droite** | `D` | Joystick Gauche |
| **Tirer** | `P` | Bouton `A` / Croix |
| **Lancer la partie** | `S` | Bouton `Start` |
| **Menu Principal** | `M` | - |
| **Quitter le jeu** | `W` | Bouton `Select` / Retour |

## 🗺️ Roadmap (Améliorations futures)

Ce dépôt est un projet vivant. Voici les prochaines étapes de développement prévues :
* [ ] Faire fonctionner les mannettes connues (playstation/Xbox...) 
* [ ] Ajouts de pouvoirs activables via des bonus (qui tombes du ciel / temps sans se prendre de bombes ...)

* [ ] Création d'un exécutable portable (AppImage) pour Linux.
* [ ] Compilation croisée pour créer une version `.exe` pour Windows.
* [ ] Ajout d'effets sonores et de musique de fond (avec SDL_mixer).
* [ ] Ajout d'un système de score et d'un "High Score" sauvegardé dans un fichier.
* [ ] Ajout de différents types d'aliens et d'un boss final.

## 📝 Licence

Ce projet a été réalisé dans un cadre pédagogique. Sentez-vous libre de forker, d'explorer le code et de proposer des améliorations via des *Pull Requests*.
