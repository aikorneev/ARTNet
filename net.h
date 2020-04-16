#ifndef NET_H
#define NET_H
#include "net_layer.h"
#include <QDebug>
#define BORDER_VALUE 0.8

class net
{
public:
    net(int input_size);
    void show_net();
    void new_input(double *, int);

    int input_count;
    double border_value;
    net_layer* compare;
    net_layer* recognition;
private:
    void remember_input(double *, int);
};

#endif // NET_H
