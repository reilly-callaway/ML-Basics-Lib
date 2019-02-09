#ifndef NeuralNetwork_h
#define NeuralNetwork_h

#include "Matrix\Matrix.h"
#include <vector>

using namespace std;


float sigmoid(float n)
{
	return 1.0/(1.0 + exp(-n));
}

float dsigmoid(float n)
{
	return n * (1.0 - n);
}


class NeuralNetwork
{
	public:
		NeuralNetwork(vector<int> num_nodes, float learning_rate = 0.1, float (*activation_func)(float) = sigmoid, float (*activation_dfunc)(float) = dsigmoid);
		vector<float> predict(vector<float> input_vec);
		void train(vector<vector<float>> input_vec, vector<vector<float>> target_vec);
		void train(vector<float> input_vec, vector<float> target_vec);
				
	private:
		vector<int> num_nodes;

		vector< Matrix<float> > weights;
		vector< Matrix<float> > bias;

		float learning_rate;
		float (*activation_func)(float);
		float (*activation_dfunc)(float);
};

#endif