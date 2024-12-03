#include <string>
#include <vector>
using namespace std;

const vector<string> fonctionnalites = {
    "Afficher",
    "Composante rouge",
    "Niveaux de gris",
    "Vision deuteranopie",
    "Vision protanopie",
    "Vision tritanopie",
    "Noir et blanc",
    "Histogramme gris",
    "Histogramme couleur",
    "Luminosity up",
    "Luminosity down",
    "Contraste up",
    "Contraste down",
    "Reglage auto",
    "Enregistrer",
    "Annuler modification",
    "Rogner droite",
    "Rogner gauche",
    "Rogner haut",
    "Rogner bas",
    "Rotation droite",
    "Rotation gauche",
    "Retournement horizontal",
    "Retournement vertical",
    "Aggrandissement",
    "Retrecissement",
    "Filtre 1",
    "Quitter"};


class Image {
   private:
    vector<vector<int>> _rouge;
    vector<vector<int>> _vert;
    vector<vector<int>> _bleu;
    int _width;
    int _height;

   public:
    Image(vector<vector<int>> &rouge, vector<vector<int>> &vert,
          vector<vector<int>> &bleu);
    void displayValues();

    void display();
    vector<vector<int>> getRouge();
    vector<vector<int>> getVert();
    vector<vector<int>> getBleu();
    Image composanteRouge();
    Image niveauxGris();
    Image visionTritanopie();
    Image visionProtanopie();
    Image visionDeuteranopie();
    bool detection(int rouge, int vert, int bleu);
    Image noirEtBlanc(int seuil);
    vector<int> histogrammeGris();
    vector<vector<vector<int>>> histogrammeCouleur();
    Image luminosityUp(float luminosityfactor);
    Image luminosityDown(float luminosityfactor);
    Image contrasteUp(float contrasteFactor);
    Image contrasteDown(float contrasteFactor);
    Image reglageAuto();
    Image(string &fileName);
    void saveImage();
    Image rognerD(int nb);
    Image rognerG(int nb);
    Image rognerH(int nb);
    Image rognerB(int nb);
    Image rotationD();
    Image rotationG();
    Image retournementH();
    Image retournementV();
    Image aggrandissement(int facteur);
    Image retrecissement(int facteur);
    bool comparer(const Image &image);
};
    void displayHistGris(vector<int> &histGris);
/*
void cdisplayValues(int ,int, int);
*/
float getValue();
//void menu(Image &image, vector<Image> &historiqueImages, vector<int> &historiqueChoix);
string getFileName();

void displayMenu(int maxStrSize);

int getChoice();

void annulerModification(const vector<Image> &historiqueImages, vector<int> &historiqueChoix, Image &image);
