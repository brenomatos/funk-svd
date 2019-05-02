#include <bits/stdc++.h>
#include "matrix.h"
#include "svd.h"
using namespace std;

class Matrix;


int main(int argc, char const *argv[]) {
  (void)argc;
  ifstream input_ratings, input_targets;
  input_ratings.open(argv[1]);
  input_targets.open(argv[2]);

  Svd svd = Svd(70,0.005,0.1,&input_ratings);
  svd.train_model(50);

  input_targets.close();
  input_targets.open(argv[2]);
  svd.submission(&input_targets);

  input_ratings.close();
  input_targets.close();
  return 0;
}
