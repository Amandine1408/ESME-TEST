
#include <iostream>
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
int x;
int y;
//On definie les coordonnées d'un fruit qui va bouger à chaque fois qu'il va être mangé 
int x_bis;
int y_bis;
//Score qui va augmanter à chaque fois qu'il va y avoir une colision entre le snake et ma pomme, soit entre les coordonnées
int score;
enum eDirecton{STOP=0, Ouest, Nord, Est, Sud};
eDirecton direction;

void mise_en_place(){
    gameOver=false;
    direction=STOP;
    x=largeur/2;
    y=hauteur/2;


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
    /* Pointer to the file */
     FILE *fp1;
     /* Character variable to read the content of file */
     char c;

     /* Opening a file in r mode*/
     fp1= fopen ("map.txt", "r");

     /* Infinite loop –I have used break to come out of the loop*/
     while(1)
     {
        
        c = fgetc(fp1);
        if(c==EOF)
           break;
        else
            printf("%c", c);
     }
     fclose(fp1);

}

//On affiche la map 
void Afficher_map(){

}

//Placer notre snake 
void se_placer(int a, int b)
{
    printf("%c[%d;%df",0x1B,y,x);
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
        x--;
        break;

    case Est:
        x++;
        break;

    case Sud:
        y--;
        break;

    case Nord:
        y++;
        break;
    
    default:
        break;
    }
}


int main() 
{
    mise_en_place();
    Stockage_map();
    
    
    //while (!gameOver)
    //{
        
    //();
    //detection_touche();
    //deplacer();
    //sleep(10);

    //}
    
    
    return 0;
}