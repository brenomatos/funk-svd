#ifndef MATRIX_H
#define MATRIX_H


#include <bits/stdc++.h>
#include "matrix.h"
using namespace std;


Matrix::Matrix(int row, int col){
  this->set_col(col);
  this->set_row(row);

  this->m = (float**) malloc (this->get_row() * sizeof(float*));
  for (int i = 0; i < this->get_row(); i++) {
    this->m[i] = (float*) malloc (this->get_col() * sizeof(float));
  }

}

Matrix::~Matrix(){
  for (int i = 0; i < this->get_row(); i++) {
    free(this->m[i]);
  }
  free(this->m);
}

void Matrix::set_value(int i, int j,float value){
  this->m[i][j] = value;
}

float Matrix::get_value(int i, int j){
  return this->m[i][j];
}
int Matrix::get_col(){
  return this->col;
}

int Matrix::get_row(){
  return this->row;
}

void Matrix::set_col(int col){
  this->col = col;
}

void Matrix::set_row(int row){
  this->row = row;
}

void Matrix::print_matrix(){
  for (int i = 0; i < this->row; i++) {
    for (int j = 0; j < this->col; j++) {
      cout << this->m[i][j] << " ";
    }
    cout << endl;
  }
}

#endif
