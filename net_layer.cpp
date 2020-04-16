#include "net_layer.h"

net_layer::net_layer(bool layer_type, int size)
{
    type = layer_type;
    neuron_count = 1;
    neurons = (neuron **) malloc(sizeof(neuron *));
    if (neurons == NULL)
    {
        qDebug() << "Error with allocating";
        exit(1);
    }
    neurons[0] = new neuron(size);

    int i;
    for(i=0; i < size; i++)
    {
        //neurons[0]->vector[i] = type?L/(L+size):1;
        neurons[0]->vector[i] = type?1./6:1;
    }
}

void net_layer::show_layer()
{
    int i,j;
    for(j=0; j < neuron_count; j++)
    {
        qDebug() << "Neuron " << j;
        for(i=0; i < neurons[j]->size; i++)
        {
            qDebug() << neurons[j]->vector[i];
        }
    }
}

void net_layer::new_neuron(double *values, int size)
{
    neurons = (neuron **) realloc( neurons, (neuron_count + 1) * sizeof(neuron *));
    if (neurons == NULL)
    {
        qDebug() << "Error with allocating";
        exit(1);
    }
    neurons[neuron_count] = new neuron(size);
    int i;
    for(i=0; i < size; i++)
    {
        neurons[neuron_count]->vector[i] = values[i];
    }

    neuron_count++;
}

void net_layer::update_neuron(int ind, double * val, int size)
{
    int i;
    for(i=0; i < size; i++)
    {
        neurons[ind]->vector[i] = val[i];
    }

}
