
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <fstream>
#include <string>
#include <windows.h>

//A faire aujourd'hui:
//résoudre probleme affichage 
//Connecter les fléches
//Faire apparaitre une pomme
//Gerer les colisions
// Ajouter un score 
using namespace std;

// Fin du jeu
bool gameOver=false;

// Dimension de mon jeu
const int kLargeur=40;
const int kHauteur=20;

// valeur des cases
const int kbordure=0;
const int kpion=2;
const int kvide=1 ;

// Coordonnées courantes de notre snake
int vHauteur=0;
int vLargeur=0;

// Coordonnées précédente de notre snake
int vHauteur_p=0;
int vLargeur_p=0;

// Coordonnées courantes d'un fruit qui va bouger à chaque fois qu'il va être mangé 
int x_bis;
int y_bis;

// Score qui va augmenter à chaque fois qu'il va y avoir une collision entre le snake et ma pomme, soit entre les coordonnées
int score;
char tab[kHauteur][kLargeur];

// Définition des directions
enum eDirecton{STOP=0, Gauche, Haut, Droite, Bas};
eDirecton direction;

// Initialisation
void mise_en_place(){
    gameOver=false;
    direction=STOP;
    
    // On positionne notre serpent à cet endroit pour le debut 
    vHauteur=1;
    vLargeur=2;

    // Les valeurs précédentes sont les mêmes que les valeurs courantes 
    vHauteur_p=vHauteur;
    vLargeur_p
    =vLargeur;

} // Fin mise_en_place

void Affichage(){
    //system("cls");
    //cout<<"Bonjour nous allons vous présenter notre snakes \n"<<endl;
    //printf("Bonjour nous allons vous présenter notre snakes \n");
    //sleep(2);
    //printf("Bon jeu \n");
    //Premier ligne du haut
    //for (int i=0; i < largeur+2; i++ )
    
       // cout << "a";

    //cout << endl;
    //Pour chaque coté 
    //for (int i=0; i< hauteur; i++){
        //for (int k=0; k<largeur; k++){
            //if (k==0)
                //cout<<"b";

            //if (i==y && k==x)
                //cout<<"O";
            //if (k!=0)
            //Vide au milieu
            //else
                //cout<<" ";

            //if (k==largeur-1)
                //cout<<"b";

            
        //}
        //cout<<endl;
    //}
    // Ligne de fin
    //for (int i=0; i<largeur+2;i++)
        //cout<<"a";
    //cout<<endl;
    

}
 
//Stockage de tout les caractères dans un tableau 
void Stockage_map(){
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
    
    
    //for (k=0; k<i; k++) /* lecture des lignes enregistrées dans la variable tab */
        //printf("%s\n", tab[k]);
    
    
    //printf("%d", tab[1][2]);
    
    
} // Fin Stockage_Map

//On affiche la map; 
void Affichermap(){
    
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

            //printf("%d",tab[i][j]);
        }
    
    }
    
    
    

}

//Placer notre snake 
void positionner_pion()
{
    tab[vHauteur_p][vLargeur_p]=kvide;
    tab[vHauteur][vLargeur]=kpion;
} // Fin Positionner_pion

void Effacer_ancien_pion()
{
    tab[vHauteur][vLargeur]=1;
}

// Nettoyer la console, pour faire bouger le snake
void clrscr(void)
{
    system("cls");
}

// Lecture direction
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

void deplacer(){
    switch (direction)
    {
    case Gauche:
        // Si on ne depasse pas le mur de gauche on se deplace vers la gauche 
        if(vLargeur>0){
            vLargeur_p=vLargeur;
            vLargeur--;
        }
        // Si on depasse le mur on meurt 
        else gameOver=true;
        break;

    case Droite:
        // Si on ne depasse pas le mur de Droite on se deplace vers la Droite
        if (vLargeur<(kLargeur-1)){
            vLargeur_p=vLargeur;
            vLargeur++;
        } 
        // Si on depasse le mur on meurt 
        else gameOver=true;
        break;

    case Bas:
        // Si on ne depasse pas le mur du bas on se deplace vers le bas
         
        if (vHauteur<(kHauteur-1)){
            vHauteur_p=vHauteur;
            vHauteur++;
        }
        // Si on depasse le mur on meurt 
        else gameOver=true; 
        break;

    case Haut:
        // Si on ne depasse pas le mur du haut on se deplace vers le haut
        if (vHauteur>0){
            vHauteur_p=vHauteur;
            vHauteur--;
        } 
        // Si on depasse le mur on meurt 
        else gameOver=true;
        break;
    
    default:
       break;
    }
} 

void gotoxy(int x,int y)    
{
    printf("%c[%d;%df",0x1B,y+1,x+1);
}

void AfficherPion()
{
    // Tempo
    Sleep (15);

    // Affichage de la nouvelle position du pion
    gotoxy (vLargeur_p,vHauteur_p);
    printf(" ");
    gotoxy (vLargeur,vHauteur);
    printf("O");

} // Fin AfficherPion

int main() 
{
    clrscr();
    mise_en_place();
    Stockage_map();
    Affichermap();

    while (!gameOver)
    {
        // j'applique donne les coordonnees 
        // positionner_pion();

        //Affiche tout 
        AfficherPion();

        //Effacement de l case précedente 
        // Effacer_ancien_pion();
        LireDirection ();
        deplacer();
    }
    
    
    return 0;
}