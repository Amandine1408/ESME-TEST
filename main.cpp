
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <conio.h>
using namespace std;
//Je definie la taille de mon jeu
bool gameOver;
const int largeur=40;
const int hauteur=40;
int x, y;
enum eDirecton{STOP=0, Ouest, Nord, Est, Sud};
eDirecton direction;

void mise_en_place(){
    gameOver=false;
    direction=STOP;
    x=largeur/2;
    y=hauteur/2;

}

void Affichage(){
    system("cls");
    printf("Bonjour nous allons vous présenter notre snakes \n");
    //sleep(2);
    printf("Bon jeu \n");
    //Premier ligne du haut
    for (int i=0; i < largeur+2; i++ )
    
        cout << "a";

    cout << endl;
    //Pour chaque coté 
    for (int i=0; i< hauteur; i++){
        for (int k=0; k<largeur; k++){
            if (k==0)
                cout<<"b";

            if (i==y && k==x)
                cout<<"O";
            //if (k!=0)
            //Vide au milieu
            else
                cout<<" ";

            if (k==largeur-1)
                cout<<"b";

            
        }
        cout<<endl;
    }
    // Ligne de fin
    for (int i=0; i<largeur+2;i++)
        cout<<"a";
    

}


void detection_touche(){
    //détecter si une touche est frappée par le joueur sans interrompre le déroulement du jeu
    if (_kbhit()){

        switch(_getch()){

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
    
    
    while (gameOver!=true){
        
        Affichage();
        detection_touche();
        deplacer();
        //sleep(10);

    }
    
    
    return 0;
}