#include <bits/stdc++.h>
#include "matrix.h"
#include "svd.h"
using namespace std;

class Matrix;

// params 30,0.008,0.8 epochs 60
int main(int argc, char const *argv[]) {
  (void)argc;
  ifstream input_ratings, input_targets;
  input_ratings.open(argv[1]);
  input_targets.open(argv[2]);

  Svd svd = Svd(30,0.008,0.8,&input_ratings);
  svd.train_model(60);

  svd.submission(&input_targets);

  input_ratings.close();
  input_targets.close();
  return 0;
}
