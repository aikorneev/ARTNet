#ifndef NEURON_H
#define NEURON_H
#include "stdlib.h"
#include "QDebug"

class neuron
{
public:
    neuron(int input_count);
    double output(double *input, int input_size);
    int size;
    double *vector;
};

#endif // NEURON_H
