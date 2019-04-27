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

Matrix::Matrix(int col, int row){
  this->set_col(col);
  this->set_row(row);

  this->m = (int**) malloc (this->get_row() * sizeof(int*));
  for (int i = 0; i < this->get_row(); i++) {
    this->m[i] = (int*) malloc (this->get_col() * sizeof(int));
  }

}

Matrix::~Matrix(){
  for (int i = 0; i < this->get_row(); i++) {
    free(this->m[i]);
  }
  free(this->m);
}

void Matrix::set_value(int i, int j,int value){
  this->m[i][j] = value;
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
  for (int i = 0; i < this->col; i++) {
    for (int j = 0; j < this->row; j++) {
      cout << this->m[i][j] << " ";
    }
    cout << endl;
  }
}

void print_input(map<string, map<string,int> > * dense_users){
  for(auto const &ent1 : (*dense_users)) {
    // ent1.first is the first key
    for(auto const &ent2 : ent1.second) {
      cout << ent1.first << " "<< ent2.first << " "<< ent2.second<<endl;
    }
  }
}

void print_output(map<string, string> * targets){
  for(auto elem : (*targets))
  {
    std::cout << elem.first << " " << elem.second << " " << "\n";
  }
}

void read_ratings(map<string, map<string,int> > * dense_users, ifstream* input_ratings){
  // reading ratings file
  string line; // needed to read line by line from each file
  string user_id, item_id;
  int prediction, timestamp;
  if (input_ratings->is_open())
  {
    getline(*input_ratings,line);
    while ( getline (*input_ratings,line) )
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
      (*dense_users)[user_id][item_id] = prediction;
      (void) timestamp;

    }
  }
}

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

  map<string, map<string,int> > dense_users;
  map<string, string> targets;

  read_ratings( &dense_users, &input_ratings);
  read_targets( &targets, &input_targets);
  print_input(&dense_users);
  print_output(&targets);
  
  Matrix matriz = Matrix(3,3);
  for (int i = 0; i < matriz.get_col(); i++) {
    for (int j = 0; j < matriz.get_row(); j++) {
      matriz.set_value(i,j,i+j);
    }
  }
  matriz.print_matrix();


  input_ratings.close();
  input_targets.close();
  return 0;
}
