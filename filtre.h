#ifndef FILTRE_H
#define FILTRE_H
#include "image.h"
#include <vector>
class Filtre
{
  private:
    std::vector<std::vector<float>> _actions;
    int _rayon;
  public:
      Filtre(std::vector<std::vector<float>> action, int rayon);
      Image apply(Image& image) const; //application
      int flouG3(vector<vector<float>> &a);
};
#endif
