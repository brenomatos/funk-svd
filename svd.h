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
  int factors;
public:

  Svd (int k, float learning_rate, float reg, int n_users, int n_items);
  ~Svd ();
  int predict(int user, int item);//for a pair user:item, predicts a rating
  void print_svd();

};

#endif
