Démineur par Raphaël SCHARFF (raphael.scharff8@etu.univ-lorraine.fr) et Alexis NUSS (alexis.nuss8@etu.univ-lorraine.fr) - Groupe 9 



Nous avons recrée le célèbre jeu du démineur



Pour jouer, la première étape est de compiler le projet grâce au Makefile de celui-ci.



# Lancement du jeu :

Le jeu peut être lancé en plusieurs modes : le mode classique pour jouer (./demineur), le mode debug (./demineur debug) et le mode automatique (./demineur auto).  
Dans ce dernier mode, les cases à ouvrir sont choisies aléatoirement. 



# Les étapes du jeu :

Après avoir lancé le jeu, l'utilisateur choisit une taille de grille de jeu comprise entre 5 et 25.

Le programme crée ensuite deux grilles de la taille demandée, la première est la grille active (celle qui est visible) et la seconde la grille background (cachée)
avec 10% de bombes et des indicateurs signalant des bombes dans les cases adjacentes qui seront dévoilées lorsque le joueur saisira les coordonnées de la 
case correspondante.


Si le joueur entre les coordonées d'une bombe, cela marque la fin d'une partie, le joueur sera invité à en recommencer une nouvelle et si son score fait partie des
meilleurs, il sera invité à saisir son pseudo pour enregistrer ce score.


Dans le cas contraire, si le joueur selectionne une case vide, alors toutes les cases vides adjacentes seront dévoilées jusqu'à trouver les indicateurs adjacents 
à ces cases vides et former une bordure d'indicateurs.
Dans le cas où la case selectionnée est une case contenant un indicateur, seule celle-ci sera affichée.

L'utilisateur a également la possibilité de déposer des drapeaux
sur les cases qu'il soupçonne être des bombes.


A la fin du jeu, les drapeaux bien positionnés rapportent des points au joueur.



# Description du code : 



Le code source est segmenté en plusieurs parties dans le fichier source.



Les fichiers "affichage.h" "et affichage.c" contiennent le code nécessaire à l'affichage du jeu dans la console.



	- fonction entrer : gère l'interaction avec l'utilisateur en l'invitant à fournir des coordonnées pour jouer, placer des drapeaux ou quitter le jeu.



	- fonction draw : dessine et gère l'affichage dans la console

	

	- fonction select : vérifie le contenu de la case sélectionnée pour continuer ou arrêter le jeu

	

	- fonction drapeau : recherche la case demandée et indique si on peut placer (ou enlever un drapeau s'il y en a un) dans cette case, 
sur la grille affichée dans la console.

	

	- fonction case_restante : retourne le nombre de case qu'il reste à découvrir et ne contienne pas de bombe

	

	- fonction score : calcule le score du joueur.

	

	- fonction clean_buffer : chargée de nettoyer les entrées saisies dans la fonction entrer



Les fichiers "grille.h" et "grille.c" sont chargés de créer des tableaux dynamiques représentant les deux terrains (visible et caché).



Les fichiers "liste.h" et "liste.c" gèrent les listes de scores utiles à la fin du jeu pour contenir les scores déjà enregistrés et si besoin inclure le 
score du joueur actuel.

	

	- Structure : chaque élément de la liste contient un pseudo et le score qui lui est attribué.

	

	- Primitives : ConsVide(), estVide(), Cons(Liste, pseudo, score) ajoute les paramètres pseudo et score à la liste, Tete_pseudo(Liste) retourne le pseudo en 
première position de la liste, Tete_score(Liste) retourne le premier score de la liste, Reste(Liste) retourne la liste à partir du successeur du premier élément, 
longeur(Liste) retourne la longueur de la liste, inserer(Liste, pseudo, score, position) insère le pseudo et le score dans la Liste à la position indiquée, 
afficher(Liste) permet l'affichage de la liste.

	

	- free_liste(Liste) : permet de libérer la mémoire occupée par la liste



Les fichiers "save.h" et "save.c" sont constitués des fonctions qui agissent sur l'écriture et la lecture des scores dans le fichier "score.txt"



Les fichiers "setup.h" et "setup.c" :

	
	- Menu : affiche le message d'accueil et demande à l'utilisateur de saisir la taille de la grille sur laquelle il veut jouer



	- Quitter : gère la fin du jeu, une fois la fin de la partie, affiche le score, propose la sauvegarde de celui-ci (si besoin) et invite le joueur à recommencer.



	- build : constitue la grille cachée avec le remplissage des cases (bombes, indicateur de bombes)


	
	- random : utile pour le mode automatique du démineur, permet d'ouvrir les cases grâce à des coordonnées aléatoires

