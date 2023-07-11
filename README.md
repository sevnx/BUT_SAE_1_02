# Jeu du quart de singe / Quarter monkey game

## IMPORTANT
- FR - Ceci est un projet universitaire, uniquement à but éducatif. 
- EN - This is a university project, serving only educational purposes.

## Informations
- FR - Le programme permet à au moins 2 joueurs (robot ou humain) de jouer au jeu du quart de singe, où chaque joueur annonce une lettre à son tour, pour se rapprocher d’un mot existant, sans le compléter, à défaut de se prendre un quart de singe. Un joueur peut également demandé au joueur précédent le mot auquel il pensait lors de la saisie de la dernière lettre, si le mot est correct, le joueur demandant se prend un quart de singe, sinon l’autre. 
Enfin, un joueur peut     abandonner la manche. Le jeu se termine lorsqu’un joueur récolte 4 quarts de singe.
- EN - The goal of the project was to recreate the quarter monkey game, a game where at each turn a player says a letter to continue an existing word without finishing it, if they do end a word with this letter, they will lose the turn and get a quarter monkey. Also a player can ask the previous player what word they were thinking about, in this case if the answer is a valid word, the one who asked will lose the turn, ottherwise the one who answered wrong. The game ends when a player has 4 quarter monkeys 

## Contraintes / Constraints 
- FR - Pas le droit à l'utilisation de librairie C++ comme `vector`, `string` (quasiment du C en C++)
- EN - The whole project had to be written without the use of C++ librairies like `vector`, `string` (basically limited to writing C in C++)

## Développement

- FR - Toutes les recherches dans le dictionnaire sont basés sur la recherche dichotomique, ce qui permet une bonne efficacité du programme. - Le robot n'est pas parfiat il y a des points à améliorer (première lettre aléatoire) mais toujours très performant - Plusieurs tests uniaires sont inclus dans le sous-répertoire "ComponentTest"
- EN - All dictionary searches are done with binary search - The AI is not perfect, it has room to improve (first letter is always random) but still really good and almost unbeatable - Unitary tests are included in the "ComponentTest" directory


## How to play / Comment jouer

- FR - Afin de jouer au jeu, il faut compilé le dossier avec le code source, ouvrir un CMD à partir du dossier avec le `.exe` et puis entré en ligne de commande son nom et le type des joueurs (par exemple pour 2 humains : `HH`).
- EN - In order to play the game, we need to first compile the source code, then open a CMD in the folder with the `.exe` file and then enter its name and the type of players (for example for 2 humans : `HH`)
