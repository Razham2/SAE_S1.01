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

	//Definition des variables
	string nomfichierpalette, output_txt, ligne, fichierpgm;
	int largeur, hauteur;

	//Arguments
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

		else if (arg == "--width" && i + 1 < argc)
		{
			largeur = stoi(argv[i + 1]); //stoi convertit une chaîne de caractères en entier
			i++;
		}

		else if (arg == "--height" && i + 1 < argc)
		{
			hauteur = stoi(argv[i + 1]); 
			i++;
		}

		else
		{
			cerr << "Argument inconnu : " << arg << "\n";// sert à indiquer qu'une erreur s'est produite
			return 1;
		}

	}

	ifstream fichier;
	int largeur, hauteur;
	while (true) {
		if (fichierpgm.empty()) {
			cout << "Saisissez le nom du fichier pgm (avec l'extension) : ";
			cin >> fichierpgm;
		}
		fichier.open(fichierpgm, ios_base::binary);
		if (!fichier.is_open()) {
			cerr << "problème d'ouverture du fichier " << fichierpgm << ".\n";
			fichierpgm.clear();
			fichier.clear();
			continue;
		}
		break;
	}

	getline(fichier, ligne);
	getline(fichier, ligne);
	fichier >> largeur >> hauteur;
	fichier.ignore(numeric_limits<streamsize>::max(), '\n');

	//palette par défaut si --palette n'est pas renseigné
	vector<string> palette;
	if (nomfichierpalette.empty()) {
		palette = { "W", "w", "l", "i", ":", ",", ".", " " };
	}
	else {
		while (true) {
			ifstream fichierPalette(nomfichierpalette);
			if (!fichierPalette.is_open()) {
				cerr << "problème d'ouverture du fichier " << nomfichierpalette << "\n";
				nomfichierpalette.clear();
				cout << "Saisissez le nom du fichier palette (avec l'extension) : ";
				cin >> nomfichierpalette;
				continue;
			}

			while (getline(fichierPalette, ligne)) {
				if (!ligne.empty() && ligne.back() == '\r')
					ligne.pop_back();
				if (!ligne.empty())
					palette.push_back(ligne);
			}
			break;
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

	fichier >> largeur >> hauteur;
	fichier.get();
	int taille = largeur * hauteur;

	// Pixels
	vector<unsigned char> donnees(taille);
	fichier.read(reinterpret_cast<char*>(donnees.data()), taille);

	if (output_txt.empty()) {
		cout << "Saisissez le nom du fichier txt à créer (avec l'extension) : ";
		cin >> output_txt;
	}

	// Écriture dans le fichier output
	ofstream output(output_txt);

	if (!output.is_open()) {
		cerr << "problème d'ouverture du fichier " << output_txt << "\n";
		return 1;
	}
	//parcours des pixels et écriture dans le fichier output
	for (int j = 0; j < hauteur; j++) {
		for (int i = 0; i < largeur; i++) {
			int valeur_pixel = donnees[j * largeur + i];
			output << palette[valeur_pixel * taillePalette / 256];
		}
		output << "\n";
	}
}