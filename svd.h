#ifndef SVD_H
#define SVD_H

#include <bits/stdc++.h>
// #include "svd.h"

using namespace std;
class Matrix;

class Svd{
private:
  Matrix* q;
  Matrix* p;
  
public:

  Svd (int k);
  ~Svd ();
  void print_svd();

};

#endif
