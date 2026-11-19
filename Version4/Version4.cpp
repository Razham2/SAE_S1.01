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
	vector<string> strPalette;
	if (nomfichierpalette.empty()) {
		strPalette = { "W", "w", "l", "i", ":", ",", ".", " " };
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
					strPalette.push_back(ligne);
			}
			break;
		}
	}

	int taillePalette = strPalette.size();

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

	for (int j = 0; j < hauteur; j++) {
		for (int i = 0; i < largeur; i++) {
			int valeur_pixel = donnees[j * largeur + i];
			output << strPalette[valeur_pixel * taillePalette / 256];	//impression du craractère ASCII le plus proche de l'indice de la valeur du pixel par rapport à la taille de la palette
			//plutot que de faire un cout on insère le texte dans le fichier output

		}
		output << "\n";
	}
}