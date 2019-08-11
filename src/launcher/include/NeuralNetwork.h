//
// Created by rostard on 31.01.18.
//

#ifndef TRON_NEURALNETWORK_H
#define TRON_NEURALNETWORK_H

#include <vector>

class NeuralNetwork {
public:
    NeuralNetwork(int n_input, int n_hidden, int n_output);
    NeuralNetwork(const NeuralNetwork& nn);
    NeuralNetwork(const NeuralNetwork&& nn);

    virtual ~NeuralNetwork();

    std::vector<float> Guess(std::vector<float>& input);

    void print();
    void increaseFitness(){
         fitness+=2;
    }

    void resetFitness(){
        fitness = 0;
    }

    NeuralNetwork* crossover(NeuralNetwork* r);
    void mutate();
    unsigned long getFitness() const;

private:
    int n_input;
    int n_hidden;
    int n_output;

    unsigned long fitness = 0;
    float** firstLayer;
    float** secondLayer;
};


#endif //TRON_NEURALNETWORK_H
