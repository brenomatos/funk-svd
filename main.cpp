#include <bits/stdc++.h>
#include "matrix.h"
#include "svd.h"
using namespace std;

class Matrix;

// params 50,0.005,0.8 epochs 73
// como checar se uma chave existe de forma eficiente?
int main(int argc, char const *argv[]) {
  (void)argc;
  ifstream input_ratings, input_targets;
  input_ratings.open(argv[1]);
  input_targets.open(argv[2]);

  int k=50; // # of factors
  double learning_rate=0.005;
  double reg=0.8;
  int epochs = 73;

  Svd svd = Svd(k,learning_rate,reg,epochs,&input_ratings);
  svd.train_model();
  svd.submission(&input_targets);

  input_ratings.close();
  input_targets.close();
  return 0;
}
