#ifndef SVD_CPP
#define SVD_CPP

#include <bits/stdc++.h>
#include "svd.h"
#include "matrix.h"
using namespace std;

class Matrix;

void Svd::read_ratings(ifstream* input_ratings){
  // reading ratings file
  string line; // needed to read line by line from each file
  string user_id, item_id;
  int prediction, timestamp;
  int index_user=0,index_item=0;
  if (input_ratings->is_open())
  {
    getline(*input_ratings,line);
    while ( getline (*input_ratings,line) )
    {
      user_id = line.substr(0,8);
      item_id = line.substr(9,8);
      // dict that keeps track of user index in p matrix
      if ((this->user_index).find(user_id) == this->user_index.end()) {
        (this->user_index)[user_id] = index_user;
        index_user++;
      }
      // dict that keeps track of item index in q matrix
      if ((this->item_index).find(item_id) == this->item_index.end()) {
        (this->item_index)[item_id] = index_item;
        index_item++;
      }

      // workaround: sometimes ratings have 2 digits
      if (line[19]!=',') {
        prediction = stoi(line.substr(18,2));
        timestamp = stoi(line.substr(21,line.size()-1));
      }
      else{
        prediction = stoi(line.substr(18,1));
        timestamp = stoi(line.substr(20,line.size()-1));
      }
      this->dense_users.push_back(make_pair(make_pair(user_index[user_id], item_index[item_id]),prediction));
      // (this->dense_users)[user_id][item_id] = prediction;
      (void) timestamp;
    }
  }
}
void Svd::read_targets(ifstream* input_targets ){
  string user_id, item_id, line;
  // reading targets file
  if (input_targets->is_open()) {
    getline(*input_targets, line);
    while (getline(*input_targets, line)) {
      user_id = line.substr(0,8);
      item_id = line.substr(9,8);
      this->targets.push_back(make_pair(user_id, item_id));
      // (this->targets)[user_id] = item_id;
    }
  }
}

Svd::Svd(int k, double learning_rate, double reg, int epochs, ifstream* input_ratings, ifstream* input_targets){
  this->read_ratings(input_ratings);
  this->read_targets(input_targets);
  this->factors = k;
  this->learning_rate = learning_rate;
  this->reg = reg;
  this->epochs = epochs;
  p = new Matrix(this->user_index.size(), k);
  q = new Matrix(this->item_index.size(), k);
  // both p and q star with random numbers following a normal distribuition

  // default_random_engine generator(23);
  // normal_distribution<double> distribution(0.0,0.01);

  for (int i = 0; i < p->get_row(); i++) {
    for (int j = 0; j < p->get_col(); j++) {
      double rnd = 1.0;
      p->set_value(i,j,rnd);
    }
  }

  for (int i = 0; i < q->get_row(); i++) {
    for (int j = 0; j < q->get_col(); j++) {
      double rnd = 1.0;
      q->set_value(i,j,rnd);
    }
  }

}

Svd::~Svd(){
  delete q;
  delete p;
}

double Svd::predict(int user, int item){
  double prediction = 0.0;
  for (int i = 0; i < this->factors; i++) {
    prediction += p->get_value(user,i) * q->get_value(item,i);
  }
  return prediction;
}

void Svd::train_model(){
	int u_id,i_id; // user and item ids
	double rating;
	double error;
  double q_correction, p_correction;
  for (int i = 0; i < this->epochs; i++) {
    double rmse = 0;
    int sum = 0;
    for (int j = 0; j < this->dense_users.size(); j++) {
      u_id = this->dense_users[j].first.first;
      i_id =  this->dense_users[j].first.second;
      rating = this->dense_users[j].second;

      error = rating - predict(u_id,i_id);
      rmse+=(error*error);
      sum+=1;
      for (int k = 0; k < this->factors; k++) {
        q_correction = 2*this->learning_rate*(error * p->get_value(u_id,k));
        p_correction = 2*this->learning_rate*(error * q->get_value(i_id,k));
        q->set_value(i_id, k, q->get_value(i_id,k) + q_correction);
        p->set_value(u_id, k, p->get_value(u_id,k) + p_correction);
      }
    }
    rmse/=sum ;
    // cout << "epoca "<< i << " "<< sqrt(rmse) << endl;
  }

}

void Svd::submission(){
  string  line;
  string u_id,i_id;
  double answer;
  // reading targets file
  cout<< "UserId:ItemId,Prediction\n";
  for (int i = 0; i < targets.size(); i++) {
    u_id = this->targets[i].first;
    i_id = this->targets[i].second;
    if (this->user_index.count(u_id) && this->item_index.count(i_id)) {
      answer = predict(user_index[u_id],item_index[i_id]);
      if (answer>10) {
        answer = 10.0;
      } else if(answer<0) {
        answer = 0.0;
      }
    }
    else{
      answer = 7.2;
    }
    cout << u_id<< ":" << i_id<<","<<answer << endl;
  }
}

void Svd::print_svd(){
  p->print_matrix();
  cout << endl ;
  q->print_matrix();
}

#endif
