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
  float learning_rate, reg;
  map<string, map<string,int> > dense_users;
  map<string, string> targets;
  // 2 dicts below keep track of user index in matrix p and item index in matrix q
  map<string,int> user_index;
  map<string,int> item_index;
public:

  Svd (int k, float learning_rate, float reg, ifstream* input_targets, ifstream* input_ratings);
  ~Svd ();
  void read_targets(ifstream* input_targets );
  void read_ratings(ifstream* input_ratings);
  void print_ratings();
  void print_targets();
  void train_model(int epochs);
  int predict(int user, int item);//for a pair user:item, predicts a rating
  void submission();
  void print_svd();

};

#endif
