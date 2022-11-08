// Longueur maximum du serpent
const int kLongeurMaxSerpent=100;

// Définition d'une coordonnées
struct tCoordonnees {
    int Horizontal;
    int Vertical;
};

// Définition d'un serpent
struct tSerpent{
    int longueur=0;
    struct tCoordonnees tabCoordonnees [kLongeurMaxSerpent];
};