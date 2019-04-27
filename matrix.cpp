#include <bits/stdc++.h>
using namespace std;

class Matrix {
private:
  int **m;
  int col;
  int row;
public:

  Matrix (int col, int row);
  ~Matrix ();
  void set_col(int col);
  void set_row(int row);
  int get_col();
  int get_row();
  void print_matrix();
  void set_value(int i, int j, int value);
};
