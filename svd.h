#ifndef SVD_H
#define SVD_H

#include <bits/stdc++.h>

using namespace std;
class Matrix;

class Svd{
private:
  Matrix* q;
  Matrix* p;
  int factors;
  int epochs;
  double learning_rate, reg;
  unordered_map<string, unordered_map<string,int> > dense_users;
  unordered_map<string, string> targets;
  // 2 dicts below keep track of user index in matrix p and item index in matrix q
  unordered_map<string,int> user_index;
  unordered_map<string,int> item_index;
public:

  Svd (int k, double learning_rate, double reg, int epochs, ifstream* input_ratings);
  ~Svd ();
  void read_targets(ifstream* input_targets );
  void read_ratings(ifstream* input_ratings);
  void print_ratings();
  void print_targets();
  void train_model();
  double predict(int user, int item);//for a pair user:item, predicts a rating
  void submission(ifstream* input_targets );
  void print_svd();

};

#endif
