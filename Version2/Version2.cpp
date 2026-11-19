#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;


int main() { // Version 2 : Enregistrement de l'ASCII art
	string nomfichierpgm, output_txt, ligne, strPalette, lignePalette;
	
	cout << "Saisissez le nom du fichier pgm (avec l'extention) : ";
	cin >> nomfichierpgm;
	cout << "Saisissez le nom du fichier txt à creer (avec l'extention) : ";
	cin >> output_txt;


	//Ouverture du fichier "ImageTest1.pgm" en mode binaire :
	//ifstream fichier(nomfichierpgm, ios_base::binary);
	ifstream fichier("Wanderer.pgm", ios_base::binary);

	if (!fichier.is_open())
		cerr << "problème d'ouverture du fichier " << nomfichierpgm << ".\n";


	//ifstream fichierPalette(nomfichierpalette);
	ifstream fichierPalette("palette.txt");

	if (!fichierPalette.is_open())
		cerr << "problème d'ouverture du fichier  \"palette.txt.\".\n";

	//On extraie les valeur de palette.txt et on les insère dans le string strPalette
	while (getline(fichierPalette, ligne)) {
		for (char caractere : ligne) {
			strPalette.push_back(caractere);
		}
	}

	//décodage de l'entête du fichier
	getline(fichier, ligne);
	getline(fichier, ligne);

	int largeur, hauteur;
	fichier >> largeur >> hauteur;

	int taille = largeur * hauteur;
	int taillePalette = strPalette.size();


	//Création d'un tableau qui stocke les valeurs des pixels :
	vector<unsigned char> donnees(taille);

	//Lecture de "taille" octets depuis le fichier et stockage dans le tableau donnees :
	fichier.read(reinterpret_cast<char*>(donnees.data()), taille);


	string output_str;


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