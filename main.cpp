#include <bits/stdc++.h>
#include "matrix.h"
#include "svd.h"
using namespace std;

class Matrix;

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
  // print_input(&dense_users);
  // print_output(&targets);

  Svd svd = Svd(20);
  svd.print_svd();

  input_ratings.close();
  input_targets.close();
  return 0;
}
