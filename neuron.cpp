#include "neuron.h"

neuron::neuron(int input_count)
{
    size = input_count;
    vector = (double *) malloc(sizeof (double)*size);
    if (vector == NULL)
    {
        qDebug() << "Error with allocating";
        exit(1);
    }
}

double neuron::output(double *input, int input_size)
{
    if (size != input_size)
    {
        qDebug() << "neuron size != input_size";
        return 0;
    }
    int i;
    double answer = 0;
    for (i=0; i < size; i++)
    {
        answer += vector[i] * input[i];
    }
    return answer;
}
