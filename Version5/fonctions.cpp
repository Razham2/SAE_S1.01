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

--help              Affiche cette aide.
)";
}