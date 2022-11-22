
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <fstream>
#include <windows.h>
#include <C:\Users\marret\Desktop/PremierProjet/ESME-TEST/serpent.h>
using namespace std;
// Dimension de mon jeu
const int kLargeur=40;
const int kHauteur=20;

// valeur des cases
const int kbordure=0;
const int kpion=2;
const int kvide=1 ;

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
//BESTSCORE
int best_score=0;
//Construction d'un tableau pour stocker ma map 
char tab[kHauteur][kLargeur];

// Définition les directions que peut prendre mon snake 
enum eDirecton{Stop=0, Gauche, Haut, Droite, Bas};
eDirecton direction;

// Serpent
struct tSerpent vSerpent;


// Initialiser le jeu
void InitialiserSerpent()
{
    // Inialisation du jeu
    gameOver=false;
    direction=Stop;

    // Positionnement de notre serpent : première case
    vHauteur=1;
    vLargeur=2;

    // Initialisation de notre serpent : Ancienne position 
    vSerpent.longueur = 1 ;
    vSerpent.tabCoordonnees[0].Horizontal=vLargeur;
    vSerpent.tabCoordonnees[0].Vertical=vHauteur;
} // Fin InitialiserSerpent

// Affiche le serpent sur la MAP :

void InsererTeteSerpent ()
{
    // J'augmente la dimension du serpent si le score a augmente
    if (score<kLongeurMaxSerpent) vSerpent.longueur=score+1;

    // Je décale le corps de mon serpent (en oubliant le dernier élément car la tête a bougé)
    for (int i=vSerpent.longueur-1;i>0;i--){
        vSerpent.tabCoordonnees[i].Horizontal=vSerpent.tabCoordonnees[i-1].Horizontal;
        vSerpent.tabCoordonnees[i].Vertical=vSerpent.tabCoordonnees[i-1].Vertical;
    }
 
    // J'insère la tête
    vSerpent.tabCoordonnees[0].Horizontal=vLargeur;
    vSerpent.tabCoordonnees[0].Vertical=vHauteur;
} // Fin insererDeplacement

void AfficherSerpent()    
{
    // Tempo
    Sleep (150);

    // J'efface l'ancienne position du serpent
    for (int i=0;i<vSerpent.longueur;i++){
        printf("%c[%d;%df", 0x1B, vSerpent.tabCoordonnees[i].Vertical+1,vSerpent.tabCoordonnees[i].Horizontal+1);
        printf(" ");
    }

    // J'insère la tête
    InsererTeteSerpent();

    // J'affiche le serpent en prenant en compte son déplacement
    for (int i=0;i<vSerpent.longueur;i++){
        printf("%c[%d;%df", 0x1B, vSerpent.tabCoordonnees[i].Vertical+1,vSerpent.tabCoordonnees[i].Horizontal+1);
        printf("o");
    }
} // Fin AfficherPion
 
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
                printf("a\n");
            
            }
            else if (tab[i][j]==kbordure){
                printf("a");
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
            case 'd':
                direction=Droite;
                break;
            
            // Bas
            case 's':
                direction=Bas;
                break;

            // Haut        
            case 'z':
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
} // Fin DeplacerPion 

void AfficherFruit(){
    srand(time(NULL));
    //Définir des positions aléatoire pour notre fruit
    vHauteur_fruit=rand()%kHauteur+1;
    vLargeur_fruit=rand()%kLargeur+1;

    while ((vHauteur_fruit<1 or vHauteur_fruit>=kHauteur-2) or (vLargeur_fruit<1 or vLargeur_fruit>=kLargeur-2)){
        vHauteur_fruit=rand()%kHauteur+1;
        vLargeur_fruit=rand()%kLargeur+1;
    }

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

//Afficher le score en continu 
void AfficherScore(){
    printf("%c[%d;%df", 0x1B, 3, 50);
    printf("votre score est de: %d",score);
}


//Enregistrer le score si celui ci est supérieur aux précédents
void Enregistrer_best_score()
{
    FILE *file = fopen("best_score.txt", "w");
    if(file==NULL){
        printf("Erreur lors de l'ouverture d'un fichier");
        exit(1);
    }
    
    fprintf(file, "%d\n", best_score);
    
    fclose(file);
    // Pour le nom du meilleur joueur 
    
    char nom[20];
    
    FILE *file1 = fopen("nom_record.txt", "w");
    if(file1==NULL){
        printf("Erreur lors de l'ouverture d'un fichier");
        exit(1);
    }
    // Amélioration de notre jeu, pour la gestion du nom du meilleur joueur
    
    //printf("Saisir votre nom :");
    //scanf("%s",&nom);

    fprintf(file1, "%s\n", nom);
    
    fclose(file1);
}

//Afficher le meilleur score, nous devons l'améliorer 
int Best_score(){
    char strLigne[70];
    int intBestScore;
    
    // Lecture du fichier
    FILE *file = fopen("best_score.txt", "r");
    if (file == NULL)
        exit(EXIT_FAILURE);
 
    // Lecture de la ligne
    fgets (strLigne, 70, file);
    intBestScore = atoi(strLigne);
 
    // Fermeture du fichier d'initialisation
    fclose(file);
    
    return intBestScore;
} // Fin Best_score

// En recherche 
string nom_score(){
    string strNom;
    char* temp;
    
    // Lecture du fichier
    FILE *file = fopen("nom_record.txt", "r");
    if (file == NULL)
        exit(EXIT_FAILURE);
 
    // Lecture du nom
    
    fgets (temp, 10, file);
    strNom = string(temp);
    
    // Fermeture du fichier d'initialisation
    fclose(file);
    //printf("%c",strNom);
    //strNOM=*strNom;
    
    return strNom;
}

//En recherche
void afficher_best_score(){
    //char nom;
    //nom=nom_score();
    //string strNom;
    //strNom=nom_score();
    
    best_score=Best_score();
    printf("%c[%d;%df", 0x1B, 7, 50);
    //,strNom.c_str()
    printf("Le meilleur score est de: %d ",best_score);
 
}


int main() 
{
    EffacerEcran();
    printf("Bonjour voici notre snake, realise en mode console! Bon jeu");
    Sleep(800);
    

    // Initialisation
    EffacerEcran();
    InitialiserSerpent();
    ChargerMap();
    AfficherMap();
    AfficherFruit();
    afficher_best_score();
    
    while (!gameOver)
    {
        AfficherScore();
        // Affiche le pion 
        AfficherSerpent();
        
        // Lit la nouvelle direction
        LireDirection ();

        // Calcul la nouvelle position du pion
        DeplacerPion();

        // Est-ce que je suis sur le fruit ?
        MangerFruit();
    }    

    printf("%c[%d;%df", 0x1B, 10, 9);
    printf("GAME OVER LES PETITS LOUPS");
    
    if (score>best_score){
        //EffacerEcran();
        best_score=score;
        Enregistrer_best_score();
    
    }
    
    return 0;  

}