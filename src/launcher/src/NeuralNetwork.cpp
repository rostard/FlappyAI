//
// Created by rostard on 31.01.18.
//

#include <cstdlib>
#include "NeuralNetwork.h"
#include "Log.h"
#include <cmath>
#include <cassert>

NeuralNetwork::NeuralNetwork(int n_input, int n_hidden, int n_output) : n_input(n_input), n_hidden(n_hidden), n_output(n_output) {
    firstLayer = new float*[1 + n_input];
    for(int i = 0; i < 1 + n_input; i++){
        firstLayer[i] = new float[n_hidden];
        for(int j = 0; j < n_hidden; j++){
            firstLayer[i][j] = (std::rand()% 200) / 100.0f - 1.0f;
        }
    }

    secondLayer = new float*[1 + n_hidden];
    for(int i = 0; i < 1 + n_hidden; i++){
        secondLayer[i] = new float[n_output];
        for(int j = 0; j < n_output; j++){
            secondLayer[i][j] = (std::rand()% 200) / 100.0f  - 1.0f  ;
        }
    }
}



void NeuralNetwork::print() {
    Log::Message("First Layer", LOG_INFO);
    for(int i = 0; i < 1 + n_input; i++){
        for(int j = 0; j < n_hidden; j++){
            Log::Message(std::to_string(firstLayer[i][j]), LOG_INFO);
        }
        Log::Message("\n", LOG_INFO);
    }

    Log::Message("Second Layer", LOG_INFO);
    for(int i = 0; i < 1 + n_hidden; i++){
        for(int j = 0; j < n_output; j++){
            Log::Message(std::to_string(secondLayer[i][j]), LOG_INFO);
        }
        Log::Message("\n", LOG_INFO);
    }
}
float sigmoid(float x){
    return 1.0f / (1 + exp(-x));
}
std::vector<float> NeuralNetwork::Guess(std::vector<float>& input) {
    assert(input.size() == n_input);

    std::vector<float> hidden_neurons(n_hidden);

    for(int i = 0; i < n_hidden; i++){
        float wx=0;
        for(int j = 1; j<n_input+1; j++){
            wx += firstLayer[j][i] * input[j-1];
        }
        wx += firstLayer[0][i];
        hidden_neurons[i] = sigmoid(wx);
    }

    std::vector<float> output_neurons(n_output);
    for(int i = 0; i < n_output; i++){
        float wx=0;
        for(int j = 1; j<n_hidden+1; j++){
            wx += secondLayer[j][i] * hidden_neurons[j-1];
        }
        wx += secondLayer[0][i];
        output_neurons[i] = sigmoid(wx);
    }

    return output_neurons;
}

NeuralNetwork::~NeuralNetwork() {

    for(int i = 0; i < 1 + n_input; i++){
        delete[] firstLayer[i];
    }
    delete[] firstLayer;

    for(int i = 0; i < 1 + n_hidden; i++){
        delete[] secondLayer[i];
    }
    delete[] secondLayer;
}

unsigned long NeuralNetwork::getFitness() const {
    return fitness;
}

NeuralNetwork *NeuralNetwork::crossover(NeuralNetwork *r) {
    NeuralNetwork *result = new NeuralNetwork(n_input, n_hidden, n_output);
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            result->firstLayer[i][j] = rand()%2 ? this->firstLayer[i][j] : r->firstLayer[i][j];
        }
    }

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 1; j++){
            result->secondLayer[i][j] = rand()%2 ? this->secondLayer[i][j] : r->secondLayer[i][j];
        }
    }
    return result;
}


void NeuralNetwork::mutate() {
    for(int i = 0; i < 1 + n_input; i++){
        for(int j = 0; j < n_hidden; j++){
            if(std::rand()%100<10)this->firstLayer[i][j] += (std::rand()% 200) / 400.0f - 0.25f ;
        }
    }

    for(int i = 0; i < 1 + n_hidden; i++){
        for(int j = 0; j < n_output; j++){
            if(std::rand()%100<10)this->secondLayer[i][j] += (std::rand()% 200) / 400.0f  - 0.25f  ;
        }
    }
}

NeuralNetwork::NeuralNetwork(const NeuralNetwork &nn) {
    n_input = nn.n_input;
    n_hidden = nn.n_hidden;
    n_output = nn.n_output;

    firstLayer = new float*[1 + n_input];
    for(int i = 0; i < 1 + n_input; i++){
        firstLayer[i] = new float[n_hidden];
        for(int j = 0; j < n_hidden; j++){
            firstLayer[i][j] = nn.firstLayer[i][j];
        }
    }

    secondLayer = new float*[1 + n_hidden];
    for(int i = 0; i < 1 + n_hidden; i++){
        secondLayer[i] = new float[n_output];
        for(int j = 0; j < n_output; j++){
            secondLayer[i][j] = nn.secondLayer[i][j];
        }
    }
}

NeuralNetwork::NeuralNetwork(const NeuralNetwork &&nn) {
    n_input = nn.n_input;
    n_hidden = nn.n_hidden;
    n_output = nn.n_output;

    firstLayer = new float*[1 + n_input];
    for(int i = 0; i < 1 + n_input; i++){
        firstLayer[i] = new float[n_hidden];
        for(int j = 0; j < n_hidden; j++){
            firstLayer[i][j] = nn.firstLayer[i][j];
        }
    }

    secondLayer = new float*[1 + n_hidden];
    for(int i = 0; i < 1 + n_hidden; i++){
        secondLayer[i] = new float[n_output];
        for(int j = 0; j < n_output; j++){
            secondLayer[i][j] = nn.secondLayer[i][j];
        }
    }
}


