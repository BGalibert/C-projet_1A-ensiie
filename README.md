
# Projet de Programmation Impérative, en C 

Voici mon projet de fin de 1er semestre à l'ensIIE, dans l'UE "Programamtion Impérative".  
Le but de ce projet était d'implémenter en C un interpréteur capable de "lire" une image donnée en entrée et d'exécuter des actions selon les couleurs de ses pixels.  
L'énoncé intégral dans le fichier enonce-projet-C.html .   

> Note obtenue : **20/20** 


## Contenu du dépôt

Ce dépôt contient les fichiers tels que je les avais rendus à l'époque.   
En plus de ce README.md, vous trouverez donc :   
1. l'énoncé du sujet du projet,
2. le répertoire `src` contenant tous les fichiers `.c`,   
    RQ : chaque fichier est abondemment commenté, en anglais.
3. le répertoire `include` contenant tous les fichiers `.h`,
4. un `Makefile`,
5. le répertoire `build` dans lequel sont créés tous les fichiers `.o` lors de l'appel `make`,
6. le répertoire `images_tests` contenant différentes images au format .ppm fournies par notre professeur pour tester notre programme,
7. `exec`, l'exécutable obtenu par l'appel `make`,  
8. le `rapport.pdf` dans lequel je détaille mes choix d'implémentation.  
    RQ : ce rapport est en français.



## Petit manuel de l'exécutable.

Le programme s'appelle `exec`.  
Comme demandé, il est possible d'entrer la commande :   
```bash
$ ./exec image.ppm
```
tant que `image.ppm` est dans le même répertoire que `exec`.

De plus, en raison des questions BONUS, il est possible :  

1.  de fournir comme argument une image au format JPEG. La commande est donc :   
    ```bash
    $ ./exec image.jpeg
    ``` 
    /!\  le format doit bien être .jpeg, et non .jpg !

2.  d'exécuter l'image dans un **ENVIRONNEMENT de DÉBOGAGE**, en ajoutant `-debog` à la commande :   
    ```bash
    $ ./exec image.ppm -debog
    ```
    /!\  "-debog' doit bien être placé en dernier, et non avant le fichier PPM (ou JPEG)


