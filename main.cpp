#include <bits/stdc++.h>
#include "matrix.h"
#include "svd.h"
using namespace std;

class Matrix;

// params 23,0.005 epochs 80
// RMSE DO MELHOR RESULTADO (EM TREINO): 1.38441
int main(int argc, char const *argv[]) {
  (void)argc;
  ifstream input_ratings, input_targets;
  input_ratings.open(argv[1]);
  input_targets.open(argv[2]);

  int k=23; // # of factors
  double learning_rate=0.005;
  int epochs = 80; //testra 23

  Svd svd = Svd(k,learning_rate,epochs,&input_ratings, &input_targets);
  svd.train_model();
  svd.submission();


  input_ratings.close();
  input_targets.close();
  return 0;
}
