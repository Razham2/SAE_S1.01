#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "fonctions.h"

#define NOMINMAX
#include <windows.h>

using namespace std;

double moyenne(std::vector <double> valeurs) {
	double moyenne = 0.0;
	for (auto a : valeurs)
		moyenne += valeurs[a];
	moyenne /= valeurs.size();
    return moyenne;
}


//Fonction prenant comme argument :
// 
// - la largeur et la hauteur de l'image
// - un vecteur de pixels (donnees)
// - un vecteur de chaînes de caractères représentant la palette
// - la taille de la palette
// 
//Et qui renvoie une chaine de caractères avec les info de l'image convertie en Ascii Art
string parcoursImage(int largeur, int hauteur, const std::vector<unsigned char>& donnees, const std::vector<string>& palette, int taillePalette) {
	string output;
    for (int j = 0; j < hauteur; j++) {
        for (int i = 0; i < largeur; i++) {
            int valeur_pixel = donnees[j * largeur + i];
            output += palette[valeur_pixel * taillePalette / 256];
        }
		//retour à la ligne après chaque ligne
        output += "\n";
    }
	return output;
}


void afficherAide() {
    cout << R"(Usage :
pgm2txt [options]

Options :
--input fichier     Spécifie le fichier image à convertir
                    Si ce paramètre n'est pas spécifié, le fichier est demandé via la
                    console.

--output fichier    Spécifie le nom du fichier texte qui contiendra l'Ascii Art.
                    Si ce paramètre n'est pas spécifié, l'Ascii Art est sortie dans la
                    console.

--palette fichier   Spécifie un fichier texte contenant la palette de couleur Ascii.
                    Chaque ligne du fichier contient un caractère en UTF-8, du plus
                    sombre au plus clair.
                    Si ce paramètre n'est pas spécifié, la palette par défaut est
                    "W", "w", "l", "i", ":", ",", ".", " "


--width nombre      Spécifie la largeur max de l'Ascii Art.
                    Si ce paramètre n'est pas spécifié, aucune limite n'est fixée.
                    Voir Remarques.

--height nombre     Spécifie la hauteur max de l'Ascii Art.
                    Si ce paramètre n'est pas spécifié, aucune limite n'est fixée.
                    Voir Remarques.
                    
Remarques :
Quelles que soient les valeurs des options --width et --height, la taille de l'Ascii Art
est bornée par la taille de l'image en entrée. La taille de l'ascii art conserve
toujours le même ratio que l'image d'entrée, les valeurs des options --width et --height
ne sont que des maximums.

--help              Affiche cette aide.
)";
}