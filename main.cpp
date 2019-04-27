#include <bits/stdc++.h>
using namespace std;

class Matrix {
private:

  // add getters and setters (cleaner code)
public:
  int **m;
  int col;
  int row;
  Matrix (int col, int row);
  ~Matrix ();
  void print_matrix();
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

void Matrix::print_matrix(){
  for (int i = 0; i < this->col; i++) {
    for (int j = 0; j < this->row; j++) {
      cout << this->m[i][j] << " ";
    }
    cout << endl;
  }
}

int main(int argc, char const *argv[]) {
  ifstream ratings, targets;
  ratings.open(argv[1]);
  targets.open(argv[2]);
  string line; // needed to read line by line from each file
  string user_id, item_id;
  int prediction, timestamp;

  //reading ratings file
  if (ratings.is_open())
  {
    getline(ratings,line);
    while ( getline (ratings,line) )
    {
      user_id = line.substr(0,8);
      item_id = line.substr(9,8);
      if (line[19]!=',') {
        prediction = stoi(line.substr(18,2));
        timestamp = stoi(line.substr(21,line.size()-1));
      }
      else{
        prediction = stoi(line.substr(18,1));
        timestamp = stoi(line.substr(20,line.size()-1));
      }
      // cout << user_id << " " << item_id << " " <<  prediction << " "<< timestamp << endl;
    }
  }

  // reading targets file
  if (targets.is_open()) {
    while (getline(targets, line)) {
      cout << line << endl;
      user_id = line.substr(0,8);
      item_id = line.substr(9,8);
      cout << user_id << " " << item_id << endl;
    }
  }

  Matrix matriz = Matrix(3,3);
  for (int i = 0; i < matriz.col; i++) {
    for (int j = 0; j < matriz.row; j++) {
      matriz.m[i][j] = i+j;
    }
  }
  matriz.print_matrix();


  ratings.close();
  targets.close();
  return 0;
}
