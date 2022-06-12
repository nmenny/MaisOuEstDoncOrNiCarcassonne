# OùEstDoncOrNiCarcassonne

Ce projet a consiste en l’implémentation d'une version complète du jeu de plateau Carcassonne.   
Réalisé dans le cadre du cours "LO21 : conception et programmation orientée objet" à l'UTC.

## Auteur·rices

- Bigotte Adrien
- Lemkhali Bilal
- Maistre Elise
- Menny Nathan

## Installation

### Dépendances

Le projet a été conçu en C++ à l'aide de la bibliothèque Qt6. Il est donc nécessaire d'installer toutes ces dépendances.

#### Sous Ubuntu 22

1) Ajouter le dépôt apt suivant : 
```
sudo add-apt-repository ppa:ubuntuhandbook1/ppa
```
2) Installer les packages nécessaires : 
```
sudo apt install build-essential qt6-dev-tools libopenal-dev qt6-default libhidapi-dev
```

#### Solution générale

Il est possible d'utiliser **QT Creator**.

### Compiler l'application

Le fichier [Projet_carcassonne.pro](#Projet_carcassonne.pro) contient les instructions afin de créer le Makefile qui permettra de compiler l'application. Pour ce faire, il faut faire appel à la commande suivante :

```
qmake6
```

Puis, une fois le fichier `Makefile` créé, il suffit de taper la commande suivante pour compiler l'entièreté de l'application :

```
make
```

### Lancer le jeu

Une fois le projet compilé, il suffit d’exécuter le fichier `jeu` créé.

## Déroulement d'une partie

Lorsqu'une partie se lance, une fenêtre s'ouvre proposant à l'utilisateur·rice de spécifier :   

- le nombre de joueur·euses
- les extensions à utiliser lors de la partie

Par la suite, le vrai jeu se lance. Le système pose automatiquement une Tuile au milieu du plateau.    
Les emplacements apparaissant en blanc dans le plateau correspondent aux emplacements qui sont autorisés pour la tuile courante et dans l'orientation courante (visible dans la vue en bas à droite).   
Pour voir si cette Tuile recèle d'autres possibilités de placement, il suffit de la faire tourner en cliquant sur les boutons droite / gauche dans l'interface de la pile. Le bouton "repiocher" permet à
l'utilisation de reposer sa tuile et d'en prendre une nouvelle; cela peut être utile pour ne pas être coincé.   
En cliquant sur l'emplacement vide proposé par le jeu, l'utilisateur·rice pose la tuile de sa pioche; a partir de là plusieurs possibilités s'offrent à lui/elle :

- il/elle peut poser un meeple en cliquant dans les environnements de même couleur adjacents à ceux présentant des carrés violet ;
- il/elle peut récupérer un de ses meeples en cliquant sur l'environnement dans lequel est situé les siens ;
- il/elle peut décider de ne rien faire et de passer au tour du/de la prochain·e joueur·euse à l'aide du bouton "passer" en haut à droite.

Et ce procédé se répète jusqu'à ce qu'il n'y ait plus de Tuile en stock.   
Lorsque cela se produit, les utilisateur·rices peuvent modifier les scores des différents joueur·euses.
