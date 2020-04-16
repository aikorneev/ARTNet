#ifndef NET_LAYER_H
#define NET_LAYER_H
#include "neuron.h"
#include "stdlib.h"
#include "QDebug"
#define L 2.

class net_layer
{
public:
    net_layer(bool type, int size);
    void show_layer();
    void new_neuron(double *, int);
    void update_neuron(int,double *, int);

    bool type; //1 - compare, 0 - recognition
    int neuron_count;
    neuron **neurons;
};

#endif // NET_LAYER_H
