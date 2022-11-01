
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <fstream>
#include <string>
//A faire aujourd'hui:
//résoudre probleme affichage 
//Connecter les fléches
//Faire apparaitre une pomme
//Gerer les colisions
// Ajouter un score 
using namespace std;
//Je definie la taille de mon jeu
bool gameOver;
const int largeur=20;
const int hauteur=20;
//On definie les coordonées que notre snake prends à chaque fois qu'il bouge, elles varient
int a=2;
int b=1;
//On definie les coordonnées d'un fruit qui va bouger à chaque fois qu'il va être mangé 
int x_bis;
int y_bis;
//Score qui va augmanter à chaque fois qu'il va y avoir une colision entre le snake et ma pomme, soit entre les coordonnées
int score;
char tab[4][3];

enum eDirecton{STOP=0, Ouest, Nord, Est, Sud};
eDirecton direction;

void mise_en_place(){
    gameOver=false;
    direction=STOP;
    // On positionne notre serpent à cet endroit pour le debut 
    a=1;
    b=2;



}

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
    
    char c;
    int k, i=0, j=0; /* k indice de lecture des lignes, i nombre de lignes, j indice caractère */
    
    FILE *file = fopen("map.txt", "r");
    if (file == NULL)
        exit(EXIT_FAILURE);
 
    c = fgetc(file); /* lecture du 1er caractère du fichier */
    while (c != EOF) /* Tant qu'on est pas en fin de fichier */
    {
        if (c == '\n')
        {
            tab[i][j] = '\0'; /* on ajoute le caractère de fin de chaîne de caractères */
            i++, j=0; /* Ligne suivante, remise à 0 de l'index des caractères */
        }
 
        else
        {
            if (c==35){
                tab[i][j] = 0; /* affectation du caractère à l'index j */
            }
            else{
                tab[i][j] = 1;/* affectation du caractère à l'index j */
            }
             
            
            j++; /* index suivant pour le caractère suivant */
            
        }
 
        c = fgetc(file); /* lecture du prochaine caractère */
    }
 
    fclose(file);
    
    
    //for (k=0; k<i; k++) /* lecture des lignes enregistrées dans la variable tab */
        //printf("%s\n", tab[k]);
    
    
    //printf("%d", tab[1][2]);
    
    
}

//On affiche la map; 
void Affichermap(){
    int p=4;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {

            if (tab[i][j]==0 and j==3){
                printf("#\n");
            
            }
            else if (tab[i][j]==0){
                printf("#");
            }
            
            else if (tab[i][j]==2){
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
void se_placer()
{
    tab[a][b]=2;

    
}

// Nettoyer la console, pour faire bouger le snake
void clrscr(void)
{
    system("cls");
}

void detection_touche(){
    //détecter si une touche est frappée par le joueur sans interrompre le déroulement du jeu
    if (_kbhit()){

        switch(_getch())
        {

        case 'g':
           direction = Ouest;
            break;

        case 'j':
            direction=Est;
            break;

        case 'b':
            direction=Sud;
            break;
                
        case 'y':
            direction=Nord;
            break;

        case 'q':
            gameOver=true;
            break;

        }

    }
}

void deplacer(){
    switch (direction)
    {
    case Ouest:
        a--;
        break;

    case Est:
        a++;
        break;

    case Sud:
        b--;
        break;

    case Nord:
        b++;
        break;
    
    default:
        break;
    }
}


int main() 
{
    mise_en_place();
    Stockage_map();
    
    //Stockage_map();
    
    
    //while (!gameOver)
    //{
    //detection_touche();
    //deplacer();
    se_placer();
    
    Affichermap();
    //}
    
    
    return 0;
}