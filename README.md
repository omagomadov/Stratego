# Stratego

### Ce dépôt contient le jeu **Stratego** codé en C++ pour l'UE DEV4 à l'ESI. 

## Introduction

Le **Stratego** se joue à 2 joueurs (un joueur avec les pièces rouges, l'autre avec les pièces bleues) sur un plateau carré de 92 cases (10 cases de côté moins 2 lacs carrés de 4 cases chacun). Chaque joueur possède 40 pièces.

<p><img src="https://stoysnetcdn.com/patc/patc7476/patc7476_7.jpg"></p>

---
## Les règles du jeu

Le jeu est composé de pions qui possèdent une couleur et un numéro. Chaque joueur possède 40 pions et le but est d'arriver à attraper le drapeau adverse en premier pour gagner la partie. Les pions de rang plus haut peuvent éliminer ceux qui leur sont inférieurs. Une exception s'impose pour certains pions, comme par exemple : l'espionne (n°1) peut éliminer le maréchal et la bombe (B) peut éliminer tous les pions sauf le démineur (n°3). De plus, les pions de même rangs qui entre en bataille sont éliminés.

## Comment lancer le jeu

Pour lancer le jeu, il faut l'éxecuter (run) sur Qt Creator.

## Démonstration

- Il faut tout d'abord spécifier le niveau

```bash
###################################
#       Welcome on Stratego       #
#          version: v1.0          #
###################################
>> Which level do you want :
[1] Easy
[2] Normal
```
- Il faut spécifier le type d'initialisation du plateau de jeu qu'on veut effectuer.

```bash
==============================
Current player is blue
==============================
>> Which type of initialization do you want to do?
[1] Manual
[2] File
```
- Si l'option choisi est la 2, il faut spécifier le nom du fichier au format .txt pour remplir le plateau. Il est possible de choisir un fichier déjà configurer qui s'apppelle "default.txt". Dans le cas contraire, il est possible de créer un fichier personnalisé. Le fichier doit être placer dans le répertoire **setup-board** qui se trouve dans le projet **Stratego**. <span style="color:red">Attention, il faut bien espacer chaque valeur du pion et mettre 10 pions par lignes. Dans le cas contraire, le fichier est refuser (voir fichier default.txt). De plus, si le fichier est modifier depuis Qt Creator, celui-ci pourra être considèrer comme invalide. Car Qt Creator fait un passage à ligne lorsque le fichier est enregistrer. Il faudra alors le modifier hors Qt Creator.</span>. 

```bash
>> What is the name of the file? [or type default.txt]
default.txt
```
- Pour bouger un pion, il faut spécifier la position sur le plateau. Et ensuite indiquer dans quel direction, le pion doit aller. La position doit être spécifier telle quelle comme sur le plateau, c'est-à-dire la ligne (row) est un nombre et la colonne (column) est un caractère alphabétique en majuscule.

```bash
==============================
Current player is red
==============================

     A  B  C  D  E  F  G  H  I  J
  1  B  B  B  B  B  B  B  B  B  B
  2  B  B  B  B  B  B  B  B  B  B
  3  B  B  B  B  B  B  B  B  B  B
  4  B  B  B  B  B  B  B  B  B  B
  5  .  .  x  x  .  .  x  x  .  .
  6  .  .  x  x  .  .  x  x  .  .
  7  2  2  2  2  3  5  2  2  2  2
  8  B  B  B  F  3  3  3  B  B  B
  9  1  5  4  4  6  6  4  4  5  5
 10 10  9  3  6  6  7  7  7  8  8

>> Choose your pawn
Enter the position of your pawn
Row : 7
Column : E
>> Where do you want to move this pawn
Enter the direction of your pawn :
F -> Forward | B -> Backward | L -> Left | R -> Right
F
```

- Quand le joueur adverse attrape le drapeau, celui-ci gagne la partie.

```bash
############ BATTLE ! ############

     A  B  C  D  E  F  G  H  I  J
  1  B  B  B  B  B  B  B  B  B  B
  2  B  B  B  B  B  B  B  B  B  B
  3  B  B  B  B  B  B  B  B  B  B
  4  B  B  B  B  F  .  B  B  B  B
  5  .  .  x  x  5  .  x  x  .  .
  6  .  .  x  x  .  .  x  x  .  .
  7  B  B  B  2  F  B  2  B  B  B
  8  2  2  2  3  3  3  3  2  2  2
  9  1  5  4  4  6  6  4  4  5  5
 10 10  9  3  6  6  7  7  7  8  8

##################################
==============================
The winner is red
==============================
The game is finished
```

## Modélisation technique

<p><img src="https://add.pics/images/2022/03/24/Stratego.png"></p>

---
## Structure de dépôt

```bash
.
├── README.md
└── Stratego
    ├── Stratego.pro
    ├── Stratego.pro.user
    ├── config.pri
    ├── model
    │   ├── Board.cpp
    │   ├── Board.h
    │   ├── Color.h
    │   ├── Direction.h
    │   ├── Game.cpp
    │   ├── Game.h
    │   ├── Pawn.cpp
    │   ├── Pawn.h
    │   ├── Position.cpp
    │   ├── Position.h
    │   ├── Role.h
    │   ├── State.h
    │   └── model.pro
    ├── setup-board
    │   └── default.txt
    ├── tests
    │   ├── Catch.h
    │   ├── main.cpp
    │   ├── model_test.cpp
    │   └── tests.pro
    └── tui
        ├── main.cpp
        ├── tui.cpp
        ├── tui.h
        └── tui.pro
```
---
## Estimation du temps

- Remise **Modélisation** :<br>
travail personnel : 6 heures<br>
travail binôme : 10 heures<br>
- Remise **console** :<br>
travail personnel : 8 heures<br>
travail binôme : 72 heures<br>
- Remise **graphique**:<br>
/<br>

---
## Les technologies utilisées 
- C++
- Qt Creator
- Git
- Markdown

---

## Éventuels bogues rencontrés
**/**

---

## Les écarts par rapport à l'énoncé
**/**

---

## Auteurs
Ce jeu est codé par [Oumar Magomadov](https://git.esi-bru.be/54516) et [Ahmed Ghazouani](https://git.esi-bru.be/56366).




