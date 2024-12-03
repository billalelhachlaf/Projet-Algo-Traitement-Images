#include <iostream>

#include "image.h"
int test() {
    vector<vector<int>> vAttenduRouge;
     vector<vector<int>>vAttenduVert;
     vector<vector<int>>vAttenduBleu;
    vector<vector<int>> rouge = {
        {0, 0, 0, 0},
        {0, 0, 255, 255},
        {0, 255, 255, 255},
        {255, 255, 255, 255}
        };

    vector<vector<int>> vert =
        {{0, 0, 255, 255},
         {0, 255, 255, 255},
         {255, 255, 255, 0},
         {255, 255, 0, 0}};
    vector<vector<int>> bleu = {
        {255, 255, 0, 0},
        {255, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}};

    Image img(rouge, vert, bleu);
    

    cout << "Tests automatiques de méthodes : "<<endl << endl;

    cout << "Test de Retournement V : ";
    vAttenduRouge = {{255, 255, 255, 255, },
    {0, 255, 255, 255, },
    {0, 0, 255, 255, },
    {0, 0, 0, 0, },
    };
    vAttenduVert = {{255, 255, 0, 0, },
    {255, 255, 255, 0, },
    {0, 255, 255, 255, },
    {0, 0, 255, 255, },
    };
    vAttenduBleu = {{0, 0, 0, 0, },
    {0, 0, 0, 0, },
    {255, 0, 0, 0, },
    {255, 255, 0, 0, },
    };
    

    Image imgRetournementV = Image(vAttenduRouge, vAttenduVert, vAttenduBleu);
    if(img.retournementV().comparer(imgRetournementV)) cout << "ok";
    else cout << "Erreur"<<endl;
    cout << endl;

    cout << "Test de Noir et blanc : ";
    vAttenduRouge = {{0, 0, 0, 0, },
    {0, 0, 255, 255, },
    {0, 255, 255, 0, },
    {255, 255, 0, 0, },
    };
    vAttenduVert = {{0, 0, 0, 0, },
    {0, 0, 255, 255, },
    {0, 255, 255, 0, },
    {255, 255, 0, 0, },
    };
    vAttenduBleu = {{0, 0, 0, 0, },
    {0, 0, 255, 255, },
    {0, 255, 255, 0, },
    {255, 255, 0, 0, },
    };


    Image imgNB = Image(vAttenduRouge, vAttenduVert, vAttenduBleu);
    if(img.noirEtBlanc(127).comparer(imgNB)) cout << "ok";
    else cout << "Erreur"<<endl;
    cout << endl;
    


    cout << "Test d'agrandissement : ";
    vAttenduRouge = {{0, 0, 0, 0, 0, 0, 0, 0, },
    {0, 0, 0, 0, 0, 0, 0, 0, },
    {0, 0, 0, 0, 255, 255, 255, 255, },
    {0, 0, 0, 0, 255, 255, 255, 255, },
    {0, 0, 255, 255, 255, 255, 255, 255, },
    {0, 0, 255, 255, 255, 255, 255, 255, },
    {255, 255, 255, 255, 255, 255, 255, 255, },
    {255, 255, 255, 255, 255, 255, 255, 255, },
    };
    vAttenduVert = {{0, 0, 0, 0, 255, 255, 255, 255, },
    {0, 0, 0, 0, 255, 255, 255, 255, },
    {0, 0, 255, 255, 255, 255, 255, 255, },
    {0, 0, 255, 255, 255, 255, 255, 255, },
    {255, 255, 255, 255, 255, 255, 0, 0, },
    {255, 255, 255, 255, 255, 255, 0, 0, },
    {255, 255, 255, 255, 0, 0, 0, 0, },
    {255, 255, 255, 255, 0, 0, 0, 0, },
    };
    vAttenduBleu = {{255, 255, 255, 255, 0, 0, 0, 0, },
    {255, 255, 255, 255, 0, 0, 0, 0, },
    {255, 255, 0, 0, 0, 0, 0, 0, },
    {255, 255, 0, 0, 0, 0, 0, 0, },
    {0, 0, 0, 0, 0, 0, 0, 0, },
    {0, 0, 0, 0, 0, 0, 0, 0, },
    {0, 0, 0, 0, 0, 0, 0, 0, },
    {0, 0, 0, 0, 0, 0, 0, 0, },
    };

    Image imgAgg = Image(vAttenduRouge, vAttenduVert, vAttenduBleu);
    if(img.aggrandissement(2).comparer(imgAgg)) cout << "ok";
    else cout << "Erreur"<<endl;
    cout << endl<<endl<<endl;

   
    
    return 0;
}
