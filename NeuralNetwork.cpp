#include "NeuralNetwork.h"
#include <algorithm>
float square(float n)
{
	return n*n;
}

NeuralNetwork::NeuralNetwork(vector<int> num_nodes, float learning_rate, float (*activation_func)(float), float (*activation_dfunc)(float))
:num_nodes(num_nodes), learning_rate(learning_rate), activation_func(activation_func), activation_dfunc(activation_dfunc)
{
	this->weights.reserve(this->num_nodes.size()-1);
	this->bias.reserve(this->num_nodes.size()-1);
	// Initialise the weights and bias vectors
	for(int i = 0; i < this->num_nodes.size()-1; i++)
	{
		// Create matricies of correct size
		Matrix<float> weight_matrix(this->num_nodes[i+1], this->num_nodes[i]);
		// Randomize initial values between 0 and 1
		weight_matrix.randomize();
		weights.push_back(weight_matrix);

		// Do the same for the bias
		Matrix<float> bias_matrix(num_nodes[i+1], 1);
		bias_matrix.randomize();
		bias.push_back(bias_matrix);
	}
}

vector<float> NeuralNetwork::predict(vector<float> input_vec)
{
	if(input_vec.size() != this->num_nodes[0])
	{
		cout << "Incorrect number of inputs when training" << endl;
	}
	else
	{
		Matrix<float> inputs = Matrix<float>::fromVector(input_vec);
		vector<Matrix<float>> activation_nodes;
		activation_nodes.resize(this->num_nodes.size());

		activation_nodes[0] = inputs;
		for(int i = 0; i < activation_nodes.size()-1; i++)
		{
			activation_nodes[i+1] = this->weights[i] * activation_nodes[i] + this->bias[i];
			activation_nodes[i+1].map(this->activation_func);
		}

		// Return the last (output) layer as a single vector
		Matrix<float> outputs = activation_nodes.back();
		return outputs.transpose().data[0];
	}
	return input_vec;
}

void NeuralNetwork::train(vector<float> input_vec, vector<float> target_vec)
{
	if(input_vec.size() != this->num_nodes[0])
	{
		cout << "Incorrect number of inputs when training" << endl;
	}
	else if(target_vec.size() != this->num_nodes[this->num_nodes.size()-1])
	{
		cout << "Incorrect number of outputs when training" << endl;
	}
	else
	{
		// Run a predict to use the values of the activation nodes
		Matrix<float> inputs = Matrix<float>::fromVector(input_vec);
		Matrix<float> targets = Matrix<float>::fromVector(target_vec);

		vector<Matrix<float>> activation_nodes;
		activation_nodes.resize(this->num_nodes.size());

		activation_nodes[0] = inputs;
		for(int i = 0; i < activation_nodes.size()-1; i++)
		{
			activation_nodes[i+1] = this->weights[i] * activation_nodes[i] + this->bias[i];
			activation_nodes[i+1].map(this->activation_func);
		}
		Matrix<float> outputs = activation_nodes.back();

		vector<Matrix<float>> errors;
		errors.resize(this->weights.size());

		errors[0] = targets - outputs;
		//errors[0].map(square);
		for (int i = 1; i < this->weights.size(); i++)
		{
			errors[i] = this->weights[this->weights.size()-i].transpose() * errors[i-1];
			//errors[i].map(sqrt);
		}
		reverse(errors.begin(), errors.end());


		vector<Matrix<float>> gradients;
		gradients.resize(this->weights.size());

		for(int i = gradients.size()-1; i >= 0; i--)
		{
			gradients[i] = Matrix<float>::map(activation_nodes[i+1], activation_dfunc).multiply_elements(errors[i])*learning_rate;
			this->bias[i] = this->bias[i] + gradients[i];
		}
		for(int i = this->weights.size()-1; i >= 0; i--)
		{
			this->weights[i] = this->weights[i] + (gradients[i]*(activation_nodes[i].transpose()));
		}

	}

}

void NeuralNetwork::train(vector<vector<float>> training_input, vector<vector<float>> training_target)
{
	vector<Matrix<float>> delta_weights;
	vector<Matrix<float>> delta_bias;

	delta_weights = this->weights;
	delta_bias = this->bias;

	for(auto &m : delta_weights) m.set_values(0.0);
	for(auto &m : delta_bias) 	 m.set_values(0.0);


	for(int training_index = 0; training_index < training_input.size(); training_index++)
	{
		Matrix<float> inputs = Matrix<float>::fromVector(training_input[training_index]);
		Matrix<float> targets = Matrix<float>::fromVector(training_target[training_index]);

		vector<Matrix<float>> activation_nodes;
		activation_nodes.resize(this->num_nodes.size());

		activation_nodes[0] = inputs;
		for(int i = 0; i < activation_nodes.size()-1; i++)
		{
			activation_nodes[i+1] = this->weights[i] * activation_nodes[i] + this->bias[i];
			activation_nodes[i+1].map(this->activation_func);
		}
		Matrix<float> outputs = activation_nodes.back();

		vector<Matrix<float>> errors;
		errors.resize(this->weights.size());

		errors[0] = targets - outputs;
		//errors[0].map(square);
		for (int i = 1; i < this->weights.size(); i++)
		{
			errors[i] = this->weights[this->weights.size()-i].transpose() * errors[i-1];
			//errors[i].map(sqrt);
		}
		reverse(errors.begin(), errors.end());


		vector<Matrix<float>> gradients;
		gradients.resize(this->weights.size());

		for(int i = gradients.size()-1; i >= 0; i--)
		{
			gradients[i] = Matrix<float>::map(activation_nodes[i+1], activation_dfunc).multiply_elements(errors[i])*learning_rate;
			delta_bias[i] = delta_bias[i] + gradients[i];
		}
		for(int i = this->weights.size()-1; i >= 0; i--)
		{
			delta_weights[i] = delta_weights[i] + gradients[i]*(activation_nodes[i].transpose());
		}
	}

	for(int i = 0; i < this->weights.size(); i++)
	{
		this->weights[i] = this->weights[i] + (delta_weights[i] * (1.0/(float)training_input.size()));
		this->bias[i] = this->bias[i] + (delta_bias[i] * (1.0/(float)training_input.size()));
	}

}

