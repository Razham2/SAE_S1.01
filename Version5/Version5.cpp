#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "fonctions.h"

#define NOMINMAX
#include <windows.h>

using namespace std;

int main(int argc, char* argv[]) {

	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	string nomfichierpalette, output_txt, ligne, fichierpgm;

	//aguments
	for (int i = 1; i < argc; ++i)
	{
		string arg = argv[i];
		if (arg == "--input" && i + 1 < argc)
		{
			fichierpgm = argv[i + 1];
			++i;
		}

		else if (arg == "--output" && i + 1 < argc)
		{
			output_txt = argv[i + 1];
			++i;
		}

		else if (arg == "--palette" && i + 1 < argc)
		{
			nomfichierpalette = argv[i + 1];
			++i;
		}

		else if (arg == "--help")
		{
			afficherAide();
			return 0;
		}

	}

	ifstream fichier(fichierpgm, ios_base::binary);
	if (!fichier.is_open()) {
		cerr << "problème d'ouverture du fichier Wanderer.pgm.\n";
		return 1;
	}

	//palette par défaut si --palette n'est pas renseigné
	vector<string> palette;
	if (nomfichierpalette.empty()) {
		palette = { "W", "w", "l", "i", ":", ",", ".", " " };
	}
	else {
		ifstream fichierPalette(nomfichierpalette);
		if (!fichierPalette.is_open()) {
			cerr << "problème d'ouverture du fichier " << nomfichierpalette << "\n";
			return 1;
		}

		// Palette
		while (getline(fichierPalette, ligne)) {
			if (!ligne.empty() && ligne.back() == '\r')
				ligne.pop_back();
			if (!ligne.empty())
				palette.push_back(ligne);
		}
	}

	int taillePalette = palette.size();
	if (taillePalette == 0) {
		cerr << "palette vide\n";
		return 1;
	}

	//Parcours de l'en-tete
	getline(fichier, ligne);
	getline(fichier, ligne);

	int largeur, hauteur, maxval;
	fichier >> largeur >> hauteur >> maxval;
	fichier.get();
	int taille = largeur * hauteur;

	// Pixels
	vector<unsigned char> donnees(taille);
	fichier.read(reinterpret_cast<char*>(donnees.data()), taille);

	if (fichier.gcount() != taille) {
		cerr << "lecture incomplète : " << fichier.gcount() << " octets lus sur " << taille << "\n";
		return 1;
	}

	// Écriture dans le fichier output
	ofstream output(output_txt);
	if (!output.is_open()) {
		cerr << "problème d'ouverture du fichier " << output_txt << "\n";
		return 1;
	}

	for (int j = 0; j < hauteur; j++) {
		for (int i = 0; i < largeur; i++) {
			int valeur_pixel = donnees[j * largeur + i];
			output << palette[valeur_pixel * taillePalette / 256];
		}
		output << "\n";
	}
}