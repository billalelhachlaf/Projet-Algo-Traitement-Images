#include "filtre.h"
#include <exception>
#include <vector>
using namespace std;
Filtre::Filtre(std::vector<std::vector<float>> _actions, int rayon)
{
  _actions = _actions;
  _rayon = rayon;
}
Image Filtre::apply(Image& image) const{
  vector<vector<int>> rouge = image.getRouge();
  vector<vector<int>> vert = image.getVert();
  vector<vector<int>> bleu = image.getBleu();

  vector<vector<int>> crouge;
  vector<vector<int>> cvert;
  vector<vector<int>> cbleu;
  for (int x; x<rouge.size();x++)
    for (int y; y<rouge[x].size();y++){
      float rpixel=0;
      float vpixel=0;
      float bpixel=0;
      for (int i=0; i<_actions.size();i++){
        for(int j=0; j<_actions[i].size();j++){
        try {
            rpixel+=_actions[i][j]/rouge[x+(i-_rayon)][y+(j-_rayon)];
            vpixel+=_actions[i][j]/vert[x+(i-_rayon)][y+(j-_rayon)];
            bpixel+=_actions[i][j]/bleu[x+(i-_rayon)][y+(j-_rayon)];
        }catch(const exception &e){}
        }
      }
      crouge[x][y]=rpixel;
      cvert[x][y]=vpixel;
      cbleu[x][y]=bpixel;
    }
  return Image(crouge, cvert, cbleu);
}
int flouG3(vector<vector<float>> &a){
    return (a.size()/2);
}

