#include <bits/stdc++.h>
#include "matrix.h"
#include "svd.h"
using namespace std;

class Matrix;

void read_targets(map<string, string> * targets,ifstream* input_targets ){
  string user_id, item_id, line;
  // reading targets file
  if (input_targets->is_open()) {
    while (getline(*input_targets, line)) {
      user_id = line.substr(0,8);
      item_id = line.substr(9,8);
      (*targets)[user_id] = item_id;
    }
  }
}

int main(int argc, char const *argv[]) {
  (void)argc;
  ifstream input_ratings, input_targets;
  input_ratings.open(argv[1]);
  input_targets.open(argv[2]);

  Svd svd = Svd(20,0.05,0.5,&input_ratings,&input_targets);
  // svd.print_svd();
  int result = svd.predict(0,0);
  svd.print_ratings();
  svd.print_targets();
  cout << "resultado " << result << endl;
  input_ratings.close();
  input_targets.close();
  return 0;
}
