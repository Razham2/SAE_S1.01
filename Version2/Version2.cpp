#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#define NOMINMAX
#include <windows.h>

using namespace std;

int main() { // Version 2 : Enregistrement de l'ASCII art

	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	string nomfichierpgm, nomPalette, output_txt, ligne, strPalette;
	ifstream fichier;
	int largeur, hauteur;

	while (true) {
		cout << "Saisissez le nom du fichier pgm (avec l'extension) : ";
		cin >> nomfichierpgm;
		fichier.open(nomfichierpgm, ios_base::binary);
		if (!fichier.is_open()) {
			cerr << "problème d'ouverture du fichier " << nomfichierpgm << ".\n";
			fichier.clear();
			continue;
		}
		break;
	}

	getline(fichier, ligne);
	getline(fichier, ligne);
	fichier >> largeur >> hauteur;

	while (true) {
		cout << "Saisissez le nom du fichier palette (avec l'extension) : ";
		cin >> nomPalette;
		ifstream fichierPalette(nomPalette);
		if (!fichierPalette.is_open()) {
			cerr << "problème d'ouverture du fichier " << nomPalette << ".\n";
			continue;
		}
		while (getline(fichierPalette, ligne))
			strPalette += ligne;
		break;
	}

	cout << "Saisissez le nom du fichier txt à créer (avec l'extension) : ";
	cin >> output_txt;

	int taille = largeur * hauteur;
	int taillePalette = static_cast<int>(strPalette.size());


	//Création d'un tableau qui stocke les valeurs des pixels :
	vector<unsigned char> donnees(taille);

	//Lecture de "taille" octets depuis le fichier et stockage dans le tableau donnees :
	fichier.read(reinterpret_cast<char*>(donnees.data()), taille);


	ofstream output(output_txt);

	for (int j = 0; j < hauteur; j++) {
		for (int i = 0; i < largeur; i++) {
			int valeur_pixel = donnees[j * largeur + i];
			output << strPalette[valeur_pixel * taillePalette / 256]; //plutot que de faire un cout on insère le texte dans le fichier output
		}
		output << "\n"; //saut de ligne
	}
	output.close();
}