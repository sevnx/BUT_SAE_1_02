# BUT - SAE 1_02


Projet C++ - BUT Informatique - 1ere année - Jeu du quart de singe

## Description

Le programme permet à au moins 2 joueurs (robot ou humain) de jouer au jeu du quart de singe, où chaque joueur annonce une lettre à son tour, pour se rapprocher d’un mot existant, sans le compléter, à défaut de se prendre un quart de singe. Un joueur peut également demandé au joueur précédent le mot auquel il pensait lors de la saisie de la dernière lettre, si le mot est correct, le joueur demandant se prend un quart de singe, sinon l’autre. Enfin, un joueur peut abandonner la manche.

Le jeu se termine lorsqu’un joueur récolte 4 quarts de singe.

La totalité du projet (documentations, commentaires, noms de fonctions etc.) a été écrit en anglais.

## Développement

Tous les recherches dans le dictionnaire sont basés sur la recherche dichotomique, ce qui permet une bonne efficacité du programme.

Le robot n’est pas parfait (choix de la première lettre est aléatoire), mais à part cela il est très performant et quasiment impossible à battre.

Plusieurs tests unitaires des composants sont inclus dans le sous-répertoire “ComponentTest”.

## Jouer au jeu

Afin de jouer au jeu, il faut ouvrir un CMD dans le dossier où se trouve le jeu compilé avec le `.exe` et puis entré en ligne de commande le type des joueurs (par exemple 2 humains : `HH`).
