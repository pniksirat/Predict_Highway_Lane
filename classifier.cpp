#include "classifier.h"
#include <math.h>
#include <string>
#include <vector>
#include <iostream>
#include<tuple>

using Eigen::ArrayXd;
using std::string;
using std::vector;
using std::cout;
using std::endl;

// Initializes GNB
GNB::GNB() {
  /**
   * TODO: Initialize GNB, if necessary. May depend on your implementation.
   */
    L_mean=ArrayXd(4);
    R_mean=ArrayXd(4);
    K_mean=ArrayXd(4);
    
    L_std=ArrayXd(4);
    R_std=ArrayXd(4);
    K_std=ArrayXd(4);
    
   double left_count=0;
   double right_count=0;
   double keep_count=0;
   
   L_mean<<0,0,0,0;
   R_mean<<0,0,0,0;
   K_mean<<0,0,0,0;
   
   L_std<<0,0,0,0;
   R_std<<0,0,0,0;
   K_std<<0,0,0,0;
   
   double L_prior=0;
   double R_prior=0;
   double K_prior=0;
  
}

GNB::~GNB() {}

void GNB::train(const vector<vector<double>> &data, 
                const vector<string> &labels) {
  /**
   * Trains the classifier with N data points and labels.
   * @param data - array of N observations
   *   - Each observation is a tuple with 4 values: s, d, s_dot and d_dot.
   *   - Example : [[3.5, 0.1, 5.9, -0.02],
   *                [8.0, -0.3, 3.0, 2.2],
   *                 ...
   *                ]
   * @param labels - array of N labels
   *   - Each label is one of "left", "keep", or "right".
   *
   * TODO: Implement the training function for your classifier.
   */

   //calculate the mean for each label 
   

   for (int i=0; i<data.size();++i){
       
       if (labels[i]=="left"){
           L_mean+=ArrayXd::Map(data[i].data(), data[i].size());
           left_count+=1;
       }
       if (labels[i]=="keep"){
           K_mean+=ArrayXd::Map(data[i].data(), data[i].size());
           keep_count+=1;
       }
       if (labels[i]=="right"){
           R_mean+=ArrayXd::Map(data[i].data(), data[i].size());
           right_count+=1;
       }
       
   }
   L_mean=L_mean/left_count;
   K_mean=K_mean/ keep_count;
   R_mean=R_mean/right_count;
   
   
    for( int n = 0; n < data.size(); n++ ) {
     if (labels[n]=="keep"){K_std+= (ArrayXd::Map(data[n].data(), data[n].size()) - K_mean) * (ArrayXd::Map(data[n].data(), data[n].size()) - K_mean);}
     if (labels[n]=="left"){L_std+= ((ArrayXd::Map(data[n].data(), data[n].size()) - K_mean) - L_mean) * ((ArrayXd::Map(data[n].data(), data[n].size()) - K_mean)- L_mean);}
     if (labels[n]=="right"){R_std+= ((ArrayXd::Map(data[n].data(), data[n].size()) - K_mean) - R_mean) * ((ArrayXd::Map(data[n].data(), data[n].size()) - K_mean) - R_mean);}
     
    }
    K_std /= keep_count;
    K_std = sqrt(K_std);

    L_std /= left_count;
    L_std = sqrt(L_std);

    R_std /= right_count;
    R_std = sqrt(R_std);

    L_prior=left_count/labels.size();
    R_prior=right_count/labels.size();
     K_prior=keep_count/labels.size();
  
}

string GNB::predict(const vector<double> &sample) {
  /**
   * Once trained, this method is called and expected to return 
   *   a predicted behavior for the given observation.
   * @param observation - a 4 tuple with s, d, s_dot, d_dot.
   *   - Example: [3.5, 0.1, 8.5, -0.2]
   * @output A label representing the best guess of the classifier. Can
   *   be one of "left", "keep" or "right".
   *
   * TODO: Complete this function to return your classifier's prediction
   */
  // cout<<"New Prediction****"<<endl;
   double Prob_left=1;
   double Prob_right=1;
   double Prob_keep=1;
   
   //for each feature calculate the probabilty of all three labels
   for (int i=0; i<4;++i){
       
       Prob_left*=1/sqrt(2*M_PI*L_std[i])*exp(-pow((sample[i]-L_mean[i]),2)/pow(2*L_std[i],2));
       Prob_right*=1/sqrt(2*M_PI*R_std[i])*exp(-pow((sample[i]-R_mean[i]),2)/pow(2*R_std[i],2));
       Prob_keep*=1/sqrt(2*M_PI*K_std[i])*exp(-pow((sample[i]-K_mean[i]),2)/pow(2*K_std[i],2));
   }
  
  ArrayXd prob(3);
  int index_max;
  
  prob<<Prob_left,Prob_keep,Prob_right;
  double max_val=0;
  for (int j=0; j<3;++j){
      if (prob[j]>max_val){
          max_val=prob[j];
          index_max=j;
      }
  }
  
  //cout<<possible_labels[index_max]<<endl;
  
  return this -> possible_labels[index_max];
}