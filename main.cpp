
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <fstream>

// Dimension de mon jeu
const int kLargeur=40;
const int kHauteur=20;

// valeur des cases
const int kbordure=0;
const int kpion=2;
const int kvide=1 ;

// Longueur maximum du serpent
const int kLongeurMaxSerpent=10

type tSerpent{
    int longeur=0;
    int tabCoordonnees [kLongeurMaxSerpent][kLongeurMaxSerpent]
}

// Serpent
tSerpent vSerpent;

// Fin du jeu
bool gameOver=false;

// Coordonnées courantes de notre snake
int vHauteur=0;
int vLargeur=0;

// Coordonnées précédente de notre snake
int vHauteur_p=0;
int vLargeur_p=0;

// Coordonnées courantes du fruit 
int vHauteur_fruit;
int vLargeur_fruit;

// Score qui va augmenter à chaque fois qu'il va y avoir une collision entre le snake et ma pomme, soit entre les coordonnées
int score=0;

//Construction d'un tableau pour stocker ma map 
char tab[kHauteur][kLargeur];

// Définition les directions que peut prendre mon snake 
enum eDirecton{STOP=0, Gauche, Haut, Droite, Bas};
eDirecton direction;

// Initialisation de mon jeu 
void Mise_en_place(){
    gameOver=false;
    direction=STOP;
    
    // On positionne notre serpent à cet endroit pour le debut 
    vHauteur=1;
    vLargeur=2;

    // Les valeurs précédentes sont les mêmes que les valeurs courantes 
    vHauteur_p=vHauteur;
    vLargeur_p=vLargeur;

} // Fin mise_en_place


 
//Stockage de tout les caractères de la map dans un tableau 
void ChargerMap(){
    // Déclaration
    char c;
    int k, i=0, j=0; /* k indice de lecture des lignes, i nombre de lignes, j indice caractère */
    
    // Lecture du fichier
    FILE *file = fopen("map.txt", "r");
    if (file == NULL)
        exit(EXIT_FAILURE);
 
    c = fgetc(file); /* lecture du 1er caractère du fichier */
    while (c != EOF) /* Tant qu'on est pas en fin de fichier */
    {
        
        // Si fin de ligne, alors je passe à la ligne suivante
        if (c == '\n')
        {
            // Ajout du caractère de fin de chaine
            tab[i][j] = '\0';
            // Ligne suivante
            i++, j=0; 
        }
        else
        {
            // Si le caractère est un "#"
            if (c==35){
                tab[i][j] = kbordure; /* affectation du caractère à l'index j */
            }
            // Sinon case vide
            else{
                tab[i][j] = kvide;
            }
             
            
            j++; /* index suivant pour le caractère suivant */
            
        }
 
        c = fgetc(file); /* lecture du prochaine caractère */
    } 
 
    // Fermeture du fichier d'initialisation
    fclose(file);
} // Fin Stockage_Map

//On affiche la map qui va definir le contour de mon jeu; 
void AfficherMap(){
    
    for (int i = 0; i < kHauteur; i++)
    {
        for (int j = 0; j < kLargeur; j++)
        {

            if (tab[i][j]==0 and j==(kLargeur-1)){
                printf("#\n");
            
            }
            else if (tab[i][j]==kbordure){
                printf("#");
            }
            
            else if (tab[i][j]==kpion){
                printf("O");
            }


            else{
                printf(" ");

            }
        }
    }
}


// Nettoyer la console, pour faire bouger le snake
void EffacerEcran(void)
{
    system("cls");
}

// Capture la direction choisie
void LireDirection(){
    // Si une touche est frappée, je mémorise la direction
    if (_kbhit()){
        switch(_getch())
        {
            // Gauche
            case 'q': 
                direction = Gauche;
                break;

            //Droite
            case 's':
                direction=Droite;
                break;
            
            // Bas
            case 'l':
                direction=Bas;
                break;

            // Haut        
            case 'p':
                direction=Haut;
                break;

            // Fin
            case 'x':
                gameOver=true;
                break;

            // Sinon rien
            default:
                break;
        }

    }
} // Fin LireDirection

// Calcule la nouvelle position du pion
void DeplacerPion(){

    // Conservation de l'ancienne position
    vLargeur_p=vLargeur;
    vHauteur_p=vHauteur;
    
    switch (direction)
    {
        case Gauche:
            // Si on ne depasse pas le mur de gauche on se deplace vers la gauche 
            if(vLargeur>1)
                vLargeur--;
            // Si on depasse le mur on meurt 
            else gameOver=true;
            break;

        case Droite:
            // Si on ne depasse pas le mur de Droite on se deplace vers la Droite
            if (vLargeur<(kLargeur-2))
                vLargeur++;
            // Si on depasse le mur on meurt 
            else gameOver=true;
            break;

        case Bas:
            // Si on ne depasse pas le mur du bas on se deplace vers le bas
            
            if (vHauteur<(kHauteur-2))
                vHauteur++;
            // Si on depasse le mur on meurt 
            else gameOver=true; 
            break;

        case Haut:
            // Si on ne depasse pas le mur du haut on se deplace vers le haut
            if (vHauteur>1)
                vHauteur--;
            // Si on depasse le mur on meurt 
            else gameOver=true;
            break;
    
        default:
        break;
    }
} 

// Affiche le pion sur la MAP
void AfficherPion()    
{
    // Tempo
    sleep (250);

    // Efface l'ancienne position
    printf("%c[%d;%df", 0x1B, vHauteur_p+1,vLargeur_p+1);
    printf(" ");

    // Affiche la pion
    printf("%c[%d;%df", 0x1B, vHauteur+1,vLargeur+1);
    printf("O");
} // Fin AfficherPion,

void AfficherFruit(){
    
    //Définir des positions aléatoire pour notre fruit
    vHauteur_fruit=rand()%kHauteur+1;
    vLargeur_fruit=rand()%kLargeur+1;

    //Afficher notre fruit
    printf("%c[%d;%df", 0x1B, vHauteur_fruit, vLargeur_fruit);
    printf("F");
} // AfficherFruit

void MangerFruit(){
    if ((vHauteur==(vHauteur_fruit-1)) and (vLargeur==(vLargeur_fruit-1))){
        score++;
        AfficherFruit();
    }
} // MangerFruit

int main() 
{
    // Initialisation
    EffacerEcran();
    Mise_en_place();
    ChargerMap();
    AfficherMap();
    AfficherFruit();
    

    while (!gameOver)
    {
        // Affiche le pion 
        AfficherPion();
        
        // Lit la nouvelle direction
        LireDirection ();

        // Calcul la nouvelle position du pion
        DeplacerPion();

        // Est-ce que je suis sur le fruit ?
        MangerFruit();
        
    }    
    return 0;
}