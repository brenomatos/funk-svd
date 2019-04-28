#ifndef SVD_CPP
#define SVD_CPP

#include <bits/stdc++.h>
#include "svd.h"
#include "matrix.h"
using namespace std;

class Matrix;

Svd::Svd(int k){
  p = new Matrix(10,k);
  q = new Matrix(k,10);
}

Svd::~Svd(){
  delete q;
  delete p;
}

void Svd::print_svd(){
  for (int i = 0; i < p->get_row(); i++) {
    for (int j = 0; j < p->get_col(); j++) {
      p->set_value(i,j,1);
    }
  }

  for (int i = 0; i < q->get_row(); i++) {
    for (int j = 0; j < q->get_col(); j++) {
      q->set_value(i,j,0);
    }
  }


  p->print_matrix();
  q->print_matrix();
}

#endif
