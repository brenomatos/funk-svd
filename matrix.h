#ifndef MATRIX_CPP
#define MATRIX_CPP


#include <bits/stdc++.h>
using namespace std;

class Matrix {
protected:
  double **m;
  int col;
  int row;
public:

  Matrix (int row, int col);
  ~Matrix ();
  void set_col(int col);
  void set_row(int row);
  int get_col();
  int get_row();
  void print_matrix();
  void set_value(int i, int j, double value);
  double get_value(int i,int j);
};

#endif
