#include "NeuralNetwork.cpp"
#include "mnist/mnist_reader.hpp"
#include "mnist/mnist_utils.hpp"

#include <cstdio>

const int BUCKET_SIZE = 1;
const int NUM_RETRAIN = 3;
//const bool VERBOSE = false;

template <class T>
void print_vec(vector<T> v)
{
	for (auto const& c : v)
	{
		printf("%.4f ", (float)c);
		//cout << (float) c << " ";
	}
	cout << endl;
}

template <class T>
int max_index(vector<T> v)
{
	T record = (T) 0;
	int index = 0;
	for(int i = 0; i < v.size(); i++)
	{
		if(v[i] > record)
		{
			record = v[i];
			index = i;
		}
	}
	return index;
}

float soft_plus(float n)
{
	return log(1+exp(n));
}

// Also includes inverse softplus first
float d_soft_plus(float n)
{
	return 1-exp(-n);
}


void use_nn(float lr)
{
	// Create network with appropriete input and output nodes
	vector<int> nodes = {784, 20, 10};
	NeuralNetwork brain(nodes, lr, soft_plus, d_soft_plus);

	// Load MNIST data
	auto dataset = mnist::read_dataset<vector, vector, uint8_t, uint8_t>("mnist/");
	normalize_dataset(dataset);


	// Charge form of output data from 3 -> {0, 0, 0, 1, 0, 0, 0, 0, 0, 0}
	vector<vector<float>> target_data;
	for (auto const& label : dataset.training_labels)
	{	
		vector<float> target;
		target.resize(10, 0);

		target[label] = 1.0;
		target_data.push_back(target);
	}

	// Cast images from unsigned char to float for 2D vector
	vector<vector<float>> train_images;
	train_images.reserve(dataset.training_images.size());
	for (auto&& v : dataset.training_images) train_images.emplace_back(v.begin(), v.end());

	// Train over data numerous times
	for(int k = 0; k < NUM_RETRAIN; k++)
	{
		// Display rough estimate of how many loops through data set left
		cout << NUM_RETRAIN-k << endl;

		for(int i = 0; i < train_images.size(); i++)
		{
			// Train nn
			brain.train(train_images[i], target_data[i]);
		}
		

		// Break data into bucket sizes and train on the bucketed data
		// for(int i = 0; i < train_images.size(); i+=BUCKET_SIZE)
		// {
		// 	// Break image data into buckets
		// 	auto image_start = train_images.begin()+i;
		// 	vector<vector<float>> image_bucket(image_start, image_start+BUCKET_SIZE);

		// 	// Break label data into buckets
		// 	auto target_start = target_data.begin()+i;
		// 	vector<vector<float>> target_bucket(target_start, target_start+BUCKET_SIZE);

		// 	// Train nn
		// 	brain.train(image_bucket, target_bucket);
		// }
		
	}
	
	float wrong = 0;

	// Convert test data to float
	vector<vector<float>> test_images;
	test_images.reserve(dataset.test_images.size());
	for (auto&& v : dataset.test_images) test_images.emplace_back(v.begin(), v.end());

	// Test nn on test data
	//cout << "Testing..." << endl;
	for(int i = 0; i < dataset.test_labels.size(); i++)
	{
		// Get a prediction
		auto guess = brain.predict(test_images[i]);
		// Test if incorrect
		

		if(dataset.test_labels[i] != max_index(guess))
		{
			wrong++;
		}
		// if(i < 30)
		// {
		// 	cout << (int) dataset.test_labels[i];
		// 	if(dataset.test_labels[i] != max_index(guess))
		// 	{
		// 		cout << "    |  ";
		// 	}
		// 	else
		// 	{
		// 		cout << " $$ |  ";
		// 	}
		// 	print_vec(guess); 
		// }
		
	}

	// Output results
	cout << endl << "Learning rate: " << lr << endl;
	cout << "Total Incorrect: " << wrong << endl;
	cout << "\% correct: " << 100*((float)dataset.test_labels.size()-wrong)/(float)dataset.test_labels.size() << "%" << endl << endl;
}

int main(int argc, char** argv)
{
	// float rates[12] = {0.001, 0.003, 0.005, 0.008, 0.01, 0.05, 0.8, 0.1, 0.3, 0.5, 0.8, 1};
	for (int i = 0; i < 3; i++)
	{
		use_nn(0.004);
	}
	
}