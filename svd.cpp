#ifndef SVD_CPP
#define SVD_CPP

#include <bits/stdc++.h>
#include "svd.h"
#include "matrix.h"
using namespace std;

class Matrix;

void Svd::print_ratings(){
  for(auto const &ent1 : (this->dense_users)) {
    // ent1.first is the first key
    for(auto const &ent2 : ent1.second) {
      cout << ent1.first << " "<< ent2.first << " "<< ent2.second<<endl;
    }
  }
}

void Svd::print_targets(){
  cout << this->targets.size() << endl;
  for(auto elem : this->targets)
  {
    std::cout << elem.first << " " << elem.second << " " << "\n";
  }
}

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
      if ((this->user_index).find(user_id)==this->user_index.end()) {
        (this->user_index)[user_id] = index_user;
        index_user++;
      }
      // dict that keeps track of item index in q matrix
      if ((this->item_index).find(item_id)==this->item_index.end()) {
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
      (this->dense_users)[user_id][item_id] = prediction;
      (void) timestamp;
    }
  }
}
void Svd::read_targets(ifstream* input_targets ){
  string user_id, item_id, line;
  // reading targets file
  if (input_targets->is_open()) {
    while (getline(*input_targets, line)) {
      user_id = line.substr(0,8);
      item_id = line.substr(9,8);
      (this->targets)[user_id] = item_id;
    }
  }
}

Svd::Svd(int k, double learning_rate, double reg, int epochs, ifstream* input_ratings){
  this->read_ratings(input_ratings);
  // this->read_targets(input_targets);
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
	string u_id,i_id; // user and item ids
	double rtng;
	double error;
  double q_correction, p_correction;
  for (int e = 0; e < this->epochs; e++)
  {
    double rmse = 0;
  int sum = 0;
  	for(auto const &ent1 : (this->dense_users)) {
    	// ent1.first is the first key
    	for(auto const &ent2 : ent1.second) {
	      	u_id = ent1.first;
	      	i_id =  ent2.first;
	      	rtng = ent2.second;
	      	// calculating prediction error
	      	error =  this->dense_users[u_id][i_id] - predict(this->user_index[u_id],this->item_index[i_id]);
          rmse+=(error*error);
          sum+=1;
	      	// updating vectors
	    	for (int i = 0; i < this->factors; i++) {
          q_correction = 2*this->learning_rate*(error * p->get_value(user_index[u_id],i));
          p_correction = 2*this->learning_rate*(error * q->get_value(item_index[i_id],i));
	    		q->set_value(item_index[i_id],i, q->get_value(item_index[i_id],i) + q_correction);
    			p->set_value(user_index[u_id],i, p->get_value(user_index[u_id],i) + p_correction);
  			}
    	}
  	}
    rmse/=sum ;
    // cout << "epoca "<< e << " "<< sqrt(rmse) << endl;

}
}

void Svd::submission(ifstream* input_targets ){
  string user_id, item_id, line;
  // reading targets file
  cout<< "UserId:ItemId,Prediction\n";
  if (input_targets->is_open()) {
    getline(*input_targets, line);
    while (getline(*input_targets, line)) {
      user_id = line.substr(0,8);
      item_id = line.substr(9,8);
      double answer = predict(user_index[user_id],item_index[item_id]);
      if (this->user_index.find(user_id)==this->user_index.end() || this->item_index.find(item_id)==this->item_index.end() )
      {
        answer = 7.2;
      }
      if (answer>10)
        {
          answer=10.0;
        }
      if (answer<0)
      {
        answer=0.0;
      }
      cout << user_id << ":" << item_id<<","<<answer << endl;
    }
  }
}

void Svd::print_svd(){
  p->print_matrix();
  cout << endl ;
  q->print_matrix();
}

#endif
