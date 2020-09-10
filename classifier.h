#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include <string>
#include <vector>
#include "Dense"

using Eigen::ArrayXd;
using std::string;
using std::vector;

class GNB {
 public:
  /**
   * Constructor
   */
  GNB();

  /**
   * Destructor
   */
  virtual ~GNB();

  /**
   * Train classifier
   */
  void train(const vector<vector<double>> &data, 
             const vector<string> &labels);

  /**
   * Predict with trained classifier
   */
  string predict(const vector<double> &sample);

  vector<string> possible_labels = {"left","keep","right"};
  ArrayXd L_mean;
   ArrayXd R_mean;
   ArrayXd K_mean;
   
   ArrayXd L_std;
   ArrayXd R_std;
   ArrayXd K_std;
   
   double left_count;
   double right_count;
   double keep_count;
   
   double L_prior;
   double R_prior;
   double K_prior;
};

#endif  // CLASSIFIER_H