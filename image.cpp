#include "image.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<vector<int>> Image::getRouge() {
    return _rouge;
}
vector<vector<int>> Image::getVert() {
    return _vert;
}
vector<vector<int>> Image::getBleu() {
    return _bleu;
}

float getValue() {
    float value;
    cout << "Entrez la valeur : ";
    cin >> value;
    return value;
}

Image::Image(vector<vector<int>> &rouge, vector<vector<int>> &vert,
             vector<vector<int>> &bleu) {
    if (!(rouge.size() == vert.size() && vert.size() == bleu.size()))
        throw(invalid_argument("Constructeur de Image : les trois vecteurs doivent avoir la même taille"));
    _rouge = rouge;
    _vert = vert;
    _bleu = bleu;
    _height = _rouge.size();
    _width = _rouge[0].size();
};
void Image::displayValues() {
    for (int i = 0; i < _height; i++) {
        cout << "[";
        for (int j = 0; j < _width; j++) {
            cout << _rouge[i][j] << " " << _vert[i][j] << " " << _bleu[i][j] << ", ";
        }
        cout << "]" << endl;
    }
};


Image::Image(string &name) {
    // Declaration des variables
    string line;    // pour recuperer les lignes du fichier image au format .ppm, qui est code en ASCII.
    string format;  // pour recuperer le format de l'image : celui-ci doit être de la forme P3
                    //  au cas où l'utilisateur se trompe dans le nom de l'image a charger, on redemande le nom.
    int taille;
    vector<int> mypixels;  // pour recuperer les donnees du fichier de maniere lineaire. On repartira ensuite ces donnees dans les tableaux correspondants
    ifstream entree;       // Declaration d'un "flux" qui permettra ensuite de lire les donnees de l'image.
    int hauteur;           // pour bien verifier que l'image est carree, et de taille respectant les conditions fixees par l'enonce
    // Initialisation des variables

    // Permet d'ouvrir le fichier portant le nom picture
    // ouverture du fichier portant le nom picture
    entree.open(name);
    // On verifie que le fichier a bien ete ouvert. Si cela n'est pas le cas, on redemande un nom de fichier valide
    while (!entree) {
        // cin.rdbuf(oldbuf);
        cerr << "Erreur! Impossible de lire de fichier " << name << " ! " << endl;
        cerr << "Redonnez le nom du fichier a ouvrir SVP. Attention ce fichier doit avoir un nom du type nom.ppm." << endl;
        cin >> name;
        entree.open(name);  // relance
    }
    // Lecture du nombre definissant le format (ici P3)
    entree >> format;
    // on finit de lire la ligne (caractere d'espacement)
    getline(entree, line);
    // Lecture du commentaire
    getline(entree, line);
    // lecture des dimensions
    entree >> taille >> hauteur;
    getline(entree, line);  // on finit de lire la ligne (caractere d'espacement)
    // On verifie que l'image a une taille qui verifie bien les conditions requises par l'enonce.
    // Si cela n'est pas le cas, on redemande un fichier valide, et ce, tant que necessaire.
    _height = hauteur;
    _width = taille;
    while (format != "P3") {
        if (format != "P3") {
            cerr << "Erreur! L'image que vous nous avez donnee a un format ne verifiant pas les conditions requises." << endl;
            cerr << "L'image que vous nous avez donnee doit etre codee en ASCII et non en brut." << endl;
        }
        entree.close();
        // On va redemander un nom de fichier valide.
        do {
            cerr << "Veuillez redonner un nom de fichier qui respecte les conditions de format et de taille. Attention, ce nom doit etre de la forme nom.ppm." << endl;
            cin >> name;
            entree.open(name);  // relance
        } while (!entree);
        // Lecture du nombre definissant le format (ici P3)
        entree >> format;
        getline(entree, line);  // on finit de lire la ligne (caractere d'espacement)
        // Lecture du commentaire
        getline(entree, line);
        // lecture des dimensions
        entree >> taille >> hauteur;  // relance
        getline(entree, line);        // on finit de lire la ligne (caractere d'espacement)
    }
    // Lecture de la valeur max
    getline(entree, line);
    // Lecture des donnees et ecriture dans les tableaux :
    //  Pour plus de simplicite, on stocke d'abord toutes les donnees dans mypixels
    //  dans l'ordre de lecture puis ensuite on les repartira dans les differents tableaux.
    // Les donnees stockees dans mypixels sont de la forme RGB RGB RGB ....
    //  Il faudra donc repartir les valeurs R correspondant a la composante rouge de l'image
    //  dans le tableau red, de même pour G et B.
    int pix;
    mypixels.resize(3 * taille * hauteur);  // taille fixe : on alloue une fois pour toutes
    for (int i = 0; i < 3 * taille * hauteur; i++) {
        entree >> pix;
        mypixels[i] = pix;
    }
    // Remplissage des 3 tableaux : on repartit maintenant les valeurs dans les bonnes composantes
    // Comme dans mypixels, les donnees sont stockees de la maniere suivante : RGB RGB RGB, il faut mettre
    // les valeurs correspondant a la composante rouge dans red, ...
    // Ainsi, les valeurs de la composante rouge correspondent aux valeurs stockes aux indices
    // congrus a 0 mod 3 dans mypixels, que les valeurs de la composante verte correspond aux valeurs
    // stockes aux indices sont congrus a 1 mod 3, ...
    // les valeurs d'une ligne
    int val;
    _rouge.resize(hauteur);
    _vert.resize(hauteur);
    _bleu.resize(hauteur);
    for (int i = 0; i < hauteur; i++) {
        vector<int> ligneR(taille);
        vector<int> ligneB(taille);  // les lignes ont toutes la même taille
        vector<int> ligneG(taille);
        for (int j = 0; j < taille; j++) {
            val = mypixels[3 * j + 3 * taille * i];
            ligneR[j] = val;
            val = mypixels[3 * j + 1 + 3 * taille * i];
            ligneG[j] = val;
            val = mypixels[3 * j + 2 + 3 * taille * i];
            ligneB[j] = val;
        }
        _rouge[i] = ligneR;
        _vert[i] = ligneG;
        _bleu[i] = ligneB;
    }
    // Informations a l'utilisateur pour dire que tout s'est bien passe
    cout << " L'image " << name << " a bien ete chargee dans les tableaux ." << endl;
    entree.close();
}

void Image::display() {
    char continuer;
    if (_height > 600 || _width > 600) {
        cout << "L'image est trop grande pour être affichée, continuer (o/n)" << endl;
        cin >> continuer;
        if (continuer == 'n' || continuer == 'N') return;
    }
    for (int i = 0; i < _height; i++) {
        for (int j = 0; j < _width; j++) {
            // cout << "\e[38;2;"<<_rouge[i][j] << ";"<< _vert[i][j]<<";"<<_bleu[i][j]<<"m■\e[0m" << " ";
            cout << "\e[48;2;" << _rouge[i][j] << ";" << _vert[i][j] << ";" << _bleu[i][j] << "m  \e[0m";
        }
        cout << endl;
    }
    cout << endl;
};

void displayHistGris(vector<int> &histGris) {
    cout << "Histogramme de l'image en niveaux de gris" << endl;
    for (int i = 0; i < histGris.size(); i++) {
        cout << i << " : " << histGris[i] << endl;
    }
}

bool Image::detection(int rouge, int vert, int bleu) {
    bool found = false;
    int i = 0;
    int j = 0;
    while (i < _width && !found) {
        while (j < _height && !found) {
            found =
                (_rouge[i][j] == rouge && _vert[i][j] == vert && _bleu[i][j] == bleu);
            j++;
        }
        i++;
    }
    return found;
};
Image Image::composanteRouge() {
    vector<vector<int>> rouge = _rouge;
    vector<vector<int>> vert(_vert.size(), vector<int>(_vert[0].size(), 0));
    vector<vector<int>> bleu(_bleu.size(), vector<int>(_bleu[0].size(), 0));
    Image img(rouge, vert, bleu);
    return (img);
};

Image Image::niveauxGris() {
    vector<vector<int>> rouge = _rouge;
    vector<vector<int>> vert = _vert;
    vector<vector<int>> bleu = _bleu;
    int average;
    for (int i = 0; i < rouge.size(); i++) {
        for (int j = 0; j < rouge[i].size(); j++) {
            average = (rouge[i][j] + vert[i][j] + bleu[i][j]) / 3;
            rouge[i][j] = average;
            vert[i][j] = average;
            bleu[i][j] = average;
        }
    }

    return (Image(rouge, vert, bleu));
}
Image Image::visionDeuteranopie() {
    vector<vector<int>> rouge = _rouge;
    vector<vector<int>> vert = _vert;
    vector<vector<int>> bleu = _bleu;
    int average;
    for (int i = 0; i < rouge.size(); i++) {
        for (int j = 0; j < rouge[i].size(); j++) {
            average = (rouge[i][j] + vert[i][j]) / 2;
            rouge[i][j] = average;
            vert[i][j] = average;
        }
    }
    return (Image(rouge, vert, bleu));
}
Image Image::visionTritanopie() {
    vector<vector<int>> rouge = _rouge;
    vector<vector<int>> vert = _vert;
    vector<vector<int>> bleu(_bleu.size(), vector<int>(_bleu[0].size(), 0));
    return (Image(rouge, vert, bleu));
}
Image Image::visionProtanopie() {
    vector<vector<int>> rouge(_rouge.size(), vector<int>(_rouge[0].size(), 0));
    int average = 0;
    for (int i = 0; i < rouge.size(); i++) {
        for (int j = 0; j < rouge[i].size(); j++) {
            average = (_rouge[i][j] + _vert[i][j] +
                       _bleu[i][j]) /
                      3;
            rouge[i][j] = average;
        }
    }
    vector<vector<int>> vert = _vert;
    vector<vector<int>> bleu = _bleu;
    return (Image(rouge, vert, bleu));
}

Image Image::noirEtBlanc(int seuil) {
    vector<vector<int>> rouge = _rouge;
    vector<vector<int>> vert = _vert;
    vector<vector<int>> bleu = _bleu;

    Image imageNiveauxGris(rouge, vert, bleu);
    imageNiveauxGris = imageNiveauxGris.niveauxGris();

    int average;
    for (int i = 0; i < imageNiveauxGris._rouge.size(); i++) {
        for (int j = 0; j < imageNiveauxGris._rouge[i].size(); j++) {
            average = (imageNiveauxGris._rouge[i][j] + imageNiveauxGris._vert[i][j] +
                       imageNiveauxGris._bleu[i][j]) /
                      3;

            if (average < seuil) {
                imageNiveauxGris._rouge[i][j] = 0;
                imageNiveauxGris._vert[i][j] = 0;
                imageNiveauxGris._bleu[i][j] = 0;

            } else {
                imageNiveauxGris._rouge[i][j] = 255;
                imageNiveauxGris._vert[i][j] = 255;
                imageNiveauxGris._bleu[i][j] = 255;
            }
        }
    }

    return (Image(imageNiveauxGris._rouge, imageNiveauxGris._vert, imageNiveauxGris._bleu));
}

vector<int> Image::histogrammeGris() {
    Image imageNiveauxGris(_rouge, _vert, _bleu);
    vector<int> histogrammeGrisV(256, 0);

    for (int i = 0; i < imageNiveauxGris._rouge.size(); i++) {
        for (int j = 0; j < imageNiveauxGris._rouge[i].size(); j++) {
            histogrammeGrisV[imageNiveauxGris._rouge[i][j]]++;
        }
    }

    return histogrammeGrisV;
};

vector<vector<vector<int>>> Image::histogrammeCouleur() {
    vector<vector<vector<int>>> histogrammeCouleurV(256, vector<vector<int>>(256, vector<int>(256)));

    for (int i = 0; i < _width; i++) {
        for (int j = 0; j < _height; j++) {
            histogrammeCouleurV[_rouge[i][j]][_vert[i][j]][_bleu[i][j]]++;
        }
    }

    return histogrammeCouleurV;
};

Image Image::luminosityUp(float luminosityfactor) {
    luminosityfactor = max(float(1.0), luminosityfactor);  // les floats hardcodés sont des double, que min n'accepte pas
    vector<vector<int>> rouge = _rouge;
    vector<vector<int>> vert = _vert;
    vector<vector<int>> bleu = _bleu;

    for (int i = 0; i < rouge.size(); i++) {
        for (int j = 0; j < rouge[i].size(); j++) {
            rouge[i][j] = min(int(_rouge[i][j] * luminosityfactor), 255);
            vert[i][j] = min(int(_vert[i][j] * luminosityfactor), 255);
            bleu[i][j] = min(int(_bleu[i][j] * luminosityfactor), 255);
        }
    }

    return (Image(rouge, vert, bleu));
}

Image Image::luminosityDown(float luminosityfactor) {
    luminosityfactor = min(float(1.0), luminosityfactor);  // les floats hardcodés sont des double, que min n'accepte pas
    vector<vector<int>> rouge = _rouge;
    vector<vector<int>> vert = _vert;
    vector<vector<int>> bleu = _bleu;

    for (int i = 0; i < rouge.size(); i++) {
        for (int j = 0; j < rouge[i].size(); j++) {
            rouge[i][j] = int(_rouge[i][j] * luminosityfactor);
            vert[i][j] = int(_vert[i][j] * luminosityfactor);
            bleu[i][j] = int(_bleu[i][j] * luminosityfactor);
        }
    }

    return (Image(rouge, vert, bleu));
}

Image Image::contrasteUp(float contrasteFactor) {
    contrasteFactor = max(float(1.0), contrasteFactor);  // les floats hardcodés sont des double, que min n'accepte pas
    vector<vector<int>> rouge = _rouge;
    vector<vector<int>> vert = _vert;
    vector<vector<int>> bleu = _bleu;
    float facteurRouge, facteurVert, facteurBleu;

    for (int i = 0; i < rouge.size(); i++) {
        for (int j = 0; j < rouge[i].size(); j++) {
            facteurRouge = (_rouge[i][j] - 128) * contrasteFactor;
            facteurVert = (_vert[i][j] - 128) * contrasteFactor;
            facteurBleu = (_bleu[i][j] - 128) * contrasteFactor;

            rouge[i][j] = max(min(facteurRouge + _rouge[i][j], float(255)), float(0));
            vert[i][j] = max(min(facteurVert + _vert[i][j], float(255)), float(0));
            bleu[i][j] = max(min(facteurBleu + _bleu[i][j], float(255)), float(0));
        }
    }

    return (Image(rouge, vert, bleu));
}

Image Image::contrasteDown(float contrasteFactor) {
    contrasteFactor = min(float(1.0), contrasteFactor);  // les floats hardcodés sont des double, que min n'accepte pas
    vector<vector<int>> rouge = _rouge;
    vector<vector<int>> vert = _vert;
    vector<vector<int>> bleu = _bleu;

    float facteurRouge, facteurVert, facteurBleu;
    for (int i = 0; i < rouge.size(); i++) {
        for (int j = 0; j < rouge[i].size(); j++) {
            facteurRouge = abs(int((_rouge[i][j] - 128) * contrasteFactor));
            facteurVert = abs(int((_vert[i][j] - 128) * contrasteFactor));
            facteurBleu = abs(int((_bleu[i][j] - 128) * contrasteFactor));

            rouge[i][j] = max(min(float(_rouge[i][j] - facteurRouge), float(255)), float(0));
            vert[i][j] = max(min(float(_vert[i][j] - facteurVert), float(255)), float(0));
            bleu[i][j] = max(min(float(_bleu[i][j] - facteurBleu), float(255)), float(0));
        }
    }

    return (Image(rouge, vert, bleu));
}

Image Image::reglageAuto() {
    vector<vector<int>> rouge = _rouge;
    vector<vector<int>> vert = _vert;
    vector<vector<int>> bleu = _bleu;

    float sommeRouge = 0, sommeVert = 0, sommeBleu = 0;
    float facteurRouge = 0, facteurVert = 0, facteurBleu = 0;

    for (int i = 0; i < rouge.size(); i++) {
        for (int j = 0; j < rouge[i].size(); j++) {
            sommeRouge += rouge[i][j];
            sommeVert += vert[i][j];
            sommeBleu += bleu[i][j];
        }
    }

    facteurRouge = (128.0 / (sommeRouge / rouge.size()));
    facteurVert = (128.0 / (sommeVert / vert.size()));
    facteurBleu = (128.0 / (sommeBleu / bleu.size()));

    for (int i = 0; i < rouge.size(); i++) {
        for (int j = 0; j < rouge[i].size(); j++) {
            rouge[i][j] = rouge[i][j] * facteurRouge;
            vert[i][j] = vert[i][j] * facteurVert;
            bleu[i][j] = bleu[i][j] * facteurBleu;
        }
    }

    int i = 0;
    int j = 0;
    bool didPixelReachMax = false;

    while (i < rouge.size() && didPixelReachMax) {
        while (j < rouge[i].size() && didPixelReachMax) {
            // contrasteUp(1.01);
            // cout << "i : " << i << " j : " << j << endl;
            didPixelReachMax = (rouge[i][j] < 255 && vert[i][j] < 255 && bleu[i][j] < 255);
            j++;
        }
        i++;
        j = 0;
    }

    // displayValues();

    return (Image(rouge, vert, bleu));
}

/*
Image Image::reglageAutoGris(){
  Image image = niveauxGris()
  int nbtotal=image._width*image._height;
  vector<int> a = image.histogrammeGris();
  for (int i=0; i < a.size(); i++){
    if (a[i] > 0){

    }
  }
}
void cdisplayValues(int rouge, int vert, int bleu){
  cout << "\e[48;2;"<<rouge << ";"<< vert<<";"<<bleu<<"m  \e[0m";
}

*/

Image Image::rognerD(int nb) {
    vector<vector<int>> rouge = _rouge;
    vector<vector<int>> vert = _vert;
    vector<vector<int>> bleu = _bleu;
    if (rouge[0].size() < nb + 1) return (Image(rouge, vert, bleu));
    for (int i = 0; i < rouge.size(); i++) {
        for (int j = 0; j < nb; j++) {
            rouge[i].pop_back();
            vert[i].pop_back();
            bleu[i].pop_back();
        }
    }

    return (Image(rouge, vert, bleu));
}

Image Image::rognerG(int nb) {
    vector<vector<int>> rouge = _rouge;
    vector<vector<int>> vert = _vert;
    vector<vector<int>> bleu = _bleu;
    if (rouge[0].size() < nb + 1) return (Image(rouge, vert, bleu));
    for (int i = 0; i < rouge.size(); i++) {
        for (int j = 0; j < nb; j++) {
            rouge[i].erase(rouge[i].begin());
            vert[i].erase(vert[i].begin());
            bleu[i].erase(bleu[i].begin());
        }
    }

    return (Image(rouge, vert, bleu));
}

Image Image::rognerH(int nb) {
    vector<vector<int>> rouge = _rouge;
    vector<vector<int>> vert = _vert;
    vector<vector<int>> bleu = _bleu;
    if (rouge.size() < nb + 1) return (Image(rouge, vert, bleu));
    for (int i = 0; i < nb; i++) {
        rouge.erase(rouge.begin());
        vert.erase(vert.begin());
        bleu.erase(bleu.begin());
    }

    return (Image(rouge, vert, bleu));
}
Image Image::rognerB(int nb) {
    vector<vector<int>> rouge = _rouge;
    vector<vector<int>> vert = _vert;
    vector<vector<int>> bleu = _bleu;
    if (rouge.size() < nb + 1) return (Image(rouge, vert, bleu));
    for (int i = 0; i < nb; i++) {
        rouge.pop_back();
        vert.pop_back();
        bleu.pop_back();
    }

    return (Image(rouge, vert, bleu));
}

Image Image::rotationD() {
    vector<vector<int>> rouge = _rouge;
    vector<vector<int>> vert = _vert;
    vector<vector<int>> bleu = _bleu;
    for (int i = 0; i < rouge.size(); i++) {
        for (int j = 0; j < rouge[i].size(); j++) {
            rouge[i][j] = _rouge[j][i];
            vert[i][j] = _vert[j][i];
            bleu[i][j] = _bleu[j][i];
        }
    }
    // retournementH();

    return (Image(rouge, vert, bleu).retournementH());
}

Image Image::rotationG() {
    vector<vector<int>> rouge = _rouge;
    vector<vector<int>> vert = _vert;
    vector<vector<int>> bleu = _bleu;
    for (int i = 0; i < rouge.size(); i++) {
        for (int j = 0; j < rouge[i].size(); j++) {
            rouge[i][j] = _rouge[j][i];
            vert[i][j] = _vert[j][i];
            bleu[i][j] = _bleu[j][i];
        }
    }
    // retournementH();

    return (Image(rouge, vert, bleu).retournementV());
}

Image Image::retournementH() {
    vector<vector<int>> rouge = _rouge;
    vector<vector<int>> vert = _vert;
    vector<vector<int>> bleu = _bleu;
    int tmp;
    for (int i = 0; i < rouge.size(); i++) {
        for (int j = 0; j < rouge[i].size(); j++) {
            rouge[i][j] = _rouge[i][rouge[i].size() - j - 1];
            vert[i][j] = _vert[i][rouge[i].size() - j - 1];
            bleu[i][j] = _bleu[i][rouge[i].size() - j - 1];
        }
    }

    return (Image(rouge, vert, bleu));
}

Image Image::retournementV() {
    vector<vector<int>> rouge = _rouge;
    vector<vector<int>> vert = _vert;
    vector<vector<int>> bleu = _bleu;
    int tmp;
    for (int i = 0; i < rouge.size(); i++) {
        rouge[i] = _rouge[_rouge.size() - i - 1];
        vert[i] = _vert[_vert.size() - i - 1];
        bleu[i] = _bleu[_bleu.size() - i - 1];
    }

    return (Image(rouge, vert, bleu));
}

bool Image::comparer(const Image &image){
    return (_rouge == image._rouge && _vert==image._vert && _bleu==image._bleu);
}

Image Image::aggrandissement(int facteur) {
    vector<vector<int>> rouge(_rouge.size() * facteur, vector<int>(_rouge[0].size() * facteur, 0));
    vector<vector<int>> vert(_vert.size() * facteur, vector<int>(_vert[0].size() * facteur, 0));
    vector<vector<int>> bleu(_bleu.size() * facteur, vector<int>(_bleu[0].size() * facteur, 0));

    for (int i = 0; i < rouge.size(); i++) {
        for (int j = 0; j < rouge[i].size(); j += facteur) {
            for (int k = 0; k < facteur; k++) {
                rouge[i][j + k] = _rouge[i / facteur][j / facteur];
                vert[i][j + k] = _vert[i / facteur][j / facteur];
                bleu[i][j + k] = _bleu[i / facteur][j / facteur];
            }
        }
    }

    return (Image(rouge, vert, bleu));
}

Image Image::retrecissement(int facteur) {
    vector<vector<int>> rouge(_rouge.size() / facteur, vector<int>(_rouge[0].size() / facteur, 0));
    vector<vector<int>> vert(_vert.size() / facteur, vector<int>(_vert[0].size() / facteur, 0));
    vector<vector<int>> bleu(_bleu.size() / facteur, vector<int>(_bleu[0].size() / facteur, 0));
    int averageR;
    int averageV;
    int averageB;
    for (int i = 0; i < rouge.size(); i++) {
        for (int j = 0; j < rouge[i].size(); j++) {
            averageR = 0;
            averageV = 0;
            averageB = 0;
            for (int k = 0; k < facteur; k++) {
                for (int l = 0; l < facteur; l++) {
                    averageR += _rouge[i * facteur + k][j * facteur + l];
                    averageV += _vert[i * facteur + k][j * facteur + l];
                    averageB += _bleu[i * facteur + k][j * facteur + l];
                }
            }

            rouge[i][j] = averageR / (facteur * facteur);
            vert[i][j] = averageV / (facteur * facteur);
            bleu[i][j] = averageB / (facteur * facteur);
        }
    }

    return (Image(rouge, vert, bleu));
}

// Partie 2:

string getFileName() {
    string fileName;
    cout << "Entrez le nom du fichier ppm : ";
    cin >> fileName;
    while (fileName.size() < 2 || fileName.substr(fileName.size() - 4, fileName.size()) != ".ppm") {
        cout << "Le fichier doit être au format .ppm" << endl;
        cout << "Entrez le nom du fichier ppm : ";
        cin >> fileName;
    }

    return fileName;
}

void displayMenu(int maxStrSize) {
    int middle = (fonctionnalites.size()) / 2;
    for (int i = 0; i < middle + 1; i++) {
        // if ((i + 1) % 2 == 0)
        // else
        cout << i << " : " << fonctionnalites[i];
        if ((middle + i) < fonctionnalites.size()) cout << setw(maxStrSize + 5 - fonctionnalites[i].length() - to_string(i).length()) << middle + i << " : " << fonctionnalites[middle + i] << endl;
    }

    cout << endl;
}

int getChoice() {
    int choice;
    cout << "Entrez votre choix : ";
    cin >> choice;
    while (choice < 0) {  //|| choice > fonctionnalites.size() - 1) {
        cout << "Choix invalide" << endl;
        cout << "Entrez votre choix : ";
        cin >> choice;
    }

    return choice;
}

void Image::saveImage() {
    string name = getFileName();
    int k = 0;

    std::ofstream file(name);
    if (!file) {
        std::cerr << "Failed to open file: " << name << std::endl;
        return;
    }

    string fullFile = "";
    fullFile.append("P3\n");
    fullFile.append("#" + name + "\n");
    fullFile.append(to_string(_width) + " " + to_string(_height) + '\n');
    fullFile.append("255\n");  // Ne pas oublier la valeur max
    // cout << fullFile << endl;
    for (int i = 0; i < _height; i++) {
        for (int j = 0; j < _width; j++) {
            fullFile.append(to_string(_rouge[i][j]) + '\n' + to_string(_vert[i][j]) + '\n' + to_string(_bleu[i][j]) + '\n');
        }
    }
    file << fullFile;
    /*
    écrire dans une chaîne de caractères puis dans un fichier en
    une seule fois est beaucoup plus rapide
    */
    file.close();

    cout << "Displaying image " << endl;
    // display();
}

void annulerModification(const vector<Image> &historiqueImages, vector<int> &historiqueChoix, Image &image) {
    cout << "Selectionnez la modification à annuler :" << endl;
    for (int i = 0; i < historiqueChoix.size(); i++) {
        cout << i << " : " << fonctionnalites[historiqueChoix[i]] << endl;
    }
    int choix = getChoice();
    image = historiqueImages[choix];
    cout << "Image restaurée" << endl;
}
