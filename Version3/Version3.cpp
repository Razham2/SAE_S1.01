#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#define NOMINMAX
#include <windows.h>


using namespace std;

int main() { // Version 3 : Choix de la palette

	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	string nomfichierpalette, output_txt, ligne, fichierpgm;
	ifstream fichier;
	int largeur, hauteur;

	while (true) {
		cout << "Saisissez le nom du fichier pgm (avec l'extension) : ";
		cin >> fichierpgm;
		fichier.open(fichierpgm, ios_base::binary);
		if (!fichier.is_open()) {
			cerr << "problème d'ouverture du fichier " << fichierpgm << ".\n";
			fichier.clear();
			continue;
		}
		break;
	}

	getline(fichier, ligne);
	getline(fichier, ligne);
	fichier >> largeur >> hauteur;
	fichier.ignore(numeric_limits<streamsize>::max(), '\n');

	vector<string> strPalette;
	while (true) {
		cout << "Saisissez le nom du fichier palette (avec l'extension) : ";
		cin >> nomfichierpalette;
		ifstream fichierPalette(nomfichierpalette);
		if (!fichierPalette.is_open()) {
			cerr << "problème d'ouverture du fichier " << nomfichierpalette << "\n";
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

	cout << "Saisissez le nom du fichier txt à créer (avec l'extension) : ";
	cin >> output_txt;

	// Palette : chaque ligne du fichier est un symbole
	int taillePalette = strPalette.size();

	int taille = largeur * hauteur;

	// Pixels
	vector<unsigned char> donnees(taille);
	fichier.read(reinterpret_cast<char*>(donnees.data()), taille);

	// Écriture dans le fichier output
	ofstream output(output_txt);

	for (int j = 0; j < hauteur; j++) {
		for (int i = 0; i < largeur; i++) {
			int valeur_pixel = donnees[j * largeur + i];
			output << strPalette[valeur_pixel * taillePalette / 256]; //impression du craractère ASCII le plus proche de l'indice de la valeur du pixel par rapport à la taille de la palette
			//plutot que de faire un cout on insère le texte dans le fichier output
		}
		output << "\n";
	}
}