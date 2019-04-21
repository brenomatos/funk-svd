#include <bits/stdc++.h>

using namespace std;

class Matrix {
private:


public:
  int **m;
  int col;
  int row;
  Matrix (int col, int row);
  ~Matrix ();
};

Matrix::Matrix(int col, int row){
  m = (int**) malloc (row * sizeof(int*));
  for (int i = 0; i < row; i++) {
    m[i] = (int*) malloc (col * sizeof(int));
  }
  this->col = col;
  this->row = row;
}

Matrix::~Matrix(){
  for (int i = 0; i < this->row; i++) {
    free(m[i]);
  }
  free(m);
}

int main(int argc, char const *argv[]) {
  Matrix matriz = Matrix(3,3);
  for (int i = 0; i < matriz.col; i++) {
    for (int j = 0; j < matriz.row; j++) {
      matriz.m[i][j] = i+j;
    }
  }

  for (int i = 0; i < matriz.col; i++) {
    for (int j = 0; j < matriz.row; j++) {
      cout << matriz.m[i][j] << " ";
    }
    cout << endl;
  }

  return 0;
}
