#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#define NOMINMAX
#include <windows.h>

using namespace std;

int main(){ // Version 1 : La base

	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	string fichierpgm, nomPalette, ligne, strPalette;
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

	int taille = largeur * hauteur;
	int taillePalette = static_cast<int>(strPalette.size());


	//Création d'un tableau qui stocke les valeurs des pixels :
	vector<unsigned char> donnees(taille);

	//Lecture de "taille" octets depuis le fichier et stockage dans le tableau donnees :
	fichier.read(reinterpret_cast<char*>(donnees.data()), taille);


	for (int j = 0; j < hauteur; j++) {
		for (int i = 0; i < largeur; i++) {
			int valeur_pixel = donnees[j * largeur + i];
			cout << strPalette[(255-valeur_pixel) * taillePalette / 256]; //impression du craractère ASCII le plus proche de l'indice de la valeur du pixel par rapport à la taille de la palette
		}
		cout << "\n"; //saut de ligne
	}
}
