#ifndef SVD_CPP
#define SVD_CPP

#include <bits/stdc++.h>
#include "svd.h"
#include "matrix.h"
using namespace std;

class Matrix;

Svd::Svd(int k, float learning_rate, float reg, int n_users, int n_items){
  p = new Matrix(n_users,k);
  q = new Matrix(k,n_items);
  factors = k;
  for (int i = 0; i < p->get_row(); i++) {
    for (int j = 0; j < p->get_col(); j++) {
      p->set_value(i,j,1);
    }
  }

  for (int i = 0; i < q->get_row(); i++) {
    for (int j = 0; j < q->get_col(); j++) {
      q->set_value(i,j,1);
    }
  }

}

Svd::~Svd(){
  delete q;
  delete p;
}

int Svd::predict(int user, int item){
  int prediction = 0;
  for (int i = 0; i < this->factors; i++) {
    prediction += p->get_value(user,i) * q->get_value(i,item);
  }
  return prediction;
}

void Svd::print_svd(){
  p->print_matrix();
  cout << endl ;
  q->print_matrix();
}

#endif
