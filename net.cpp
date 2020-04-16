#include "net.h"

net::net(int input_size)
{
    input_count = input_size;
    border_value = BORDER_VALUE;
    compare = new net_layer(0, input_size);
    recognition = new net_layer(1, input_size);
}

void net::show_net()
{
    qDebug() << "Compare layer:";
    compare->show_layer();
    qDebug() << "Recognition layer:";
    recognition->show_layer();
}

void net::new_input(double *input, int size)
{
    qDebug() << "NEW_INPUT";
    if (size != input_count)
    {
        qDebug() << "input > net input";
    }
    if (compare->neuron_count == 1)
    {
        qDebug() << "first input, no changes";

        remember_input(input, size);
        return;
    }
    //recognition
    int i, index=0;
    double max, temp;
    max = recognition->neurons[0]->output(input, size);
    for(i=1; i < recognition->neuron_count; i++)
    {
        temp = recognition->neurons[i]->output(input, size);
        qDebug() << "ch " << temp;
        if (max < temp)
        {
            max = temp;
            index = i;
        }
    }
    qDebug() << "winner is " << index << max;

    if (index == 0) // winner is 0 neuron
    {
       remember_input(input, size);
       return;
    }

    double result;
    double C[size];
    int diff = 0;
    for(i=0; i < size; i++)
    {
        if (input[i] > compare->neurons[index]->vector[i])
        {
            diff++;
            C[i] = 0;
        }
        else C[i] = input[i];

    }
    result = (double) (size-diff)/ size;

    qDebug() << "result" << result << C;

    if (result > border_value)
    {
        qDebug() << "update neuron";
        compare->update_neuron(index, C, size);
        double sum = 0;
        for(i=0; i < size; i++)
            sum+=C[i];

        for(i=0; i < size; i++)
        {
            C[i] = L*C[i]/(L-1+sum);
        }
        recognition->update_neuron(index, C, size);
    } else
    {

        qDebug() << "new neuron";
        remember_input(input, size);
    }
    return;
}

void net::remember_input(double *input, int size)
{
    qDebug() << "Remember";
    compare->new_neuron(input, size);

    int i;
    double sum = 0;
    for(i=0; i < size; i++)
        sum+=input[i];

    for(i=0; i < size; i++)
    {
        input[i] = L*input[i]/(L-1+sum);
    }
    recognition->new_neuron(input, size);
}
