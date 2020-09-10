Implementing Naive Bayes
 implement a Gaussian Naive Bayes classifier to predict the behavior of vehicles on a highway.
 In the image shows the behaviors you'll be looking for on a 3 lane highway (with lanes of 4 meter width).
change lanes left (shown in blue)
keep lane (shown in black)
or change lanes right (shown in red)

Each coordinate contains 4 features:

s
d
S˙
d'

Training

1) Estimate the mean and standard deviation for each label
2)calculates the prior (number of occurance of the label/total)

Prediction

for a given data needing to predict:

1) calculate the probabilty of each label for all the features P(feature/label)=> gausian distribution based on the mean and standard deviation estimated on training
2)then multiply the probability of the label given the feature to get the P(label)
3) find the max value of the probability between all the labels and that would be the predicted label
