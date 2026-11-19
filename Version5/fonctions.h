#pragma once
#include <string>

double moyenne(std::vector <double> valeurs);
void afficherAide();
string parcoursImage(int largeur, int hauteur, const std::vector<unsigned char>& donnees, const std::vector<string>& palette, int taillePalette);