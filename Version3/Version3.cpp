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

	cout << "Saisissez le nom du fichier pgm (avec l'extention) : ";
	cin >> fichierpgm;
	cout << "Saisissez le nom du fichier palette (avec l'extension) : ";
	cin >> nomfichierpalette;
	cout << "Saisissez le nom du fichier txt à créer (avec l'extension) : ";
	cin >> output_txt;

	ifstream fichier(fichierpgm, ios_base::binary);
	if (!fichier.is_open()) {
		cerr << "problème d'ouverture du fichier Wanderer.pgm.\n";
		return 1;
	}

	ifstream fichierPalette(nomfichierpalette);
	if (!fichierPalette.is_open()) {
		cerr << "problème d'ouverture du fichier " << nomfichierpalette << "\n";
		return 1;
	}

	// Palette : chaque ligne du fichier est un symbole
	vector<string> strPalette;
	while (getline(fichierPalette, ligne)) {
		if (!ligne.empty() && ligne.back() == '\r')   
			ligne.pop_back();
		if (!ligne.empty())                           
			strPalette.push_back(ligne);
	}

	int taillePalette = strPalette.size();
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
			output << strPalette[valeur_pixel * taillePalette / 256];
		}
		output << "\n";
	}
}