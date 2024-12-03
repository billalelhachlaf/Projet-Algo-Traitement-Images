#include <iostream>
#include "image.h"
#include "mainTest.h"
//#include "filtre.h"
using namespace std;
int main() {
    test();

    
   /*
   vector<vector<float>> a_filtre1 = {
    {0,50,100,150},
    {50,100,150,200},
    {100,150,200,225},
    {150,200,225,255}
    };

    Filtre filtre1(a_filtre1, 1);

   */



    vector<Image> historiqueImages;
    vector<int> historiqueChoix;

    string fileName = getFileName();
    // historiqueImages.push_back(img6);
    // historiqueChoix.push_back(0);
    Image image(fileName);
    image.display();
    vector<vector<vector<int>>> histCouleur;
    vector<int> histGris; 

    

   
   
    int maxStrSize = fonctionnalites[0].length();
    for (int i = 1; i < fonctionnalites.size(); i++) {
        if (fonctionnalites[i].length() > maxStrSize) {
            maxStrSize = fonctionnalites[i].length();
        }
    }

    //string fileName;
    int choice = 0;


    //historiqueImages.push_back(image);
    //historiqueChoix.push_back(0);

    while (choice != fonctionnalites.size() - 1) {
        displayMenu(maxStrSize);
        choice = getChoice();
        if (choice != 0 && choice != 7 && choice != 8 && choice != 14 && choice != 15) {  // && _width != _width && _height != _height && _rouge != _rouge && _vert != _vert && _bleu != _bleu) {
            historiqueImages.push_back(image);
            historiqueChoix.push_back(choice);
        }
        //cout << historiqueImages.size() << endl;
        if (historiqueImages.size() > 10) {
            int size = historiqueImages.size() - 10;
            historiqueImages.erase(historiqueImages.begin(), historiqueImages.begin() + size);
            historiqueChoix.erase(historiqueChoix.begin(), historiqueChoix.begin() + size);
        }
        switch (choice) {
            case 0:
                image.display();
                break;
            case 1:
                image = image.composanteRouge();
                break;
            case 2:
                image = image.niveauxGris();
                break;
            case 3:
                image = image.visionDeuteranopie();
                break;
            case 4:
                image = image.visionProtanopie();
                break;
            case 5:
                image = image.visionTritanopie();
                break;
            case 6:
            
                image = image.noirEtBlanc(getValue());
                break;
            case 7:
                histGris = image.histogrammeGris();
                displayHistGris(histGris);
                break;
            case 8:
                 histCouleur = image.histogrammeCouleur();
                break;
            case 9:
                image = image.luminosityUp(getValue());
                break;
            case 10:
                image = image.luminosityDown(getValue());
                break;
            case 11:
                image = image.contrasteUp(getValue());
                break;
            case 12:
                image = image.contrasteDown(getValue());
                break;
            case 13:
                image = image.reglageAuto();
                break;
            case 14:
                image.saveImage();
                break;
            case 15:
                annulerModification(historiqueImages, historiqueChoix, image);
                break;
            case 16:
                image = image.rognerD(getValue());
                break;
            case 17:
                image = image.rognerG(getValue());
                break;
            case 18:
                image = image.rognerH(getValue());
                break;
            case 19:
                image = image.rognerB(getValue());
                break;
            case 20:
                image = image.rotationD();
                break;
            case 21:
                image = image.rotationG();
                break;
            case 22:
                image = image.retournementH();
                break;
            case 23:
                image = image.retournementV();
                break;
            case 24:
                image = image.aggrandissement(getValue());
                break;
            case 25:
                image = image.retrecissement(getValue());
                break;
	    case 26:
		//get filter, apply filter.
        //image = filtre1.apply(image);
        continue;
        //    case 27:
        //        break;
        case 27:
            return 0;
            default:
                break;
        }

        image.display();
    }
    // if(choice != 0 && choice != 7 && choice != 8 && choice != 14) historiqueImages.push_backimage;

    //menu(image, historiqueImages, historiqueChoix);

}
