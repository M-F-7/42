# cub3D

Petit moteur de raycasting façon Wolfenstein 3D en C avec MiniLibX. Le programme charge une scène `.cub`, effectue un rendu texturé des murs, et propose une minimap avec déplacements fluides.

- Point d’entrée: [src/main.c](src/main.c)
- Défs/structures: [include/cub3D.h](include/cub3D.h)

## Construire et lancer

- Prérequis: Linux, X11, Make, GCC
- Compilation:
```sh
make
```
- Exécution:
```sh
./cub3D path/to/map.cub
```

## Notions abordées

- Raycasting 2D→3D:
  - DDA, distance au mur, hauteur de colonne, projection
- Vecteurs et trigonométrie:
  - Direction caméra, plan de vue, rotations
- Parsing de format:
  - Fichier `.cub` (textures NO/SO/WE/EA, couleurs F/C, carte fermée)
- Rendu et textures:
  - Chargement XPM, sampling des textures, dessin pixel par pixel
- Événements temps réel:
  - Clavier/souris (X11), boucle de jeu
- Minimap/HUD:
  - Échelle ajustable, affichage joueur et direction
- Gestion mémoire et erreurs:
  - Nettoyage ressources MLX, free des structures, messages d’erreur
- Architecture modulaire:
  - Séparation parsing, rendu, mouvements, utilitaires
