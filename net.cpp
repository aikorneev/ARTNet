#include "net.h"

net::net(int input_size)
{
    input_count = input_size;
    border_value = BORDER_VALUE;
    compare = new net_layer(0, input_size);
    recognition = new net_layer(1, input_size);
}

void net::get_info(QString* info)
{
    int i,j;
    for (i=1; i < compare->neuron_count; i++)
    {
        *info += "For neuron " + QString::number(i) + "\nT ";
        for(j=0;j<compare->neurons[i]->size;j++)
        {
            *info += QString::number(compare->neurons[i]->vector[j])+ "\t";
        }
        *info +="\nB ";
        for(j=0;j<recognition->neurons[i]->size;j++)
        {
            *info += QString::number(recognition->neurons[i]->vector[j], 'f', 2)+ "\t";
        }
        *info +="\n";
    }
}

void net::show_net()
{
    qDebug() << "Compare layer:";
    compare->show_layer();
    qDebug() << "Recognition layer:";
    recognition->show_layer();
}

void net::new_input(double *input, int size, QString* logs)
{
    *logs += "NEW_INPUT\n";
    if (size != input_count)
    {
        qDebug() << "input > net input";
    }
    if (compare->neuron_count == 1)
    {
        *logs  += "First input, remember without any changes\n";

        remember_input(input, size);
        return;
    }
    //recognition
    int i, index=0;
    double max, temp;
    max = recognition->neurons[0]->output(input, size);
    *logs += "Sn = " + QString::number(max) + "\n";
    for(i=1; i < recognition->neuron_count; i++)
    {
        temp = recognition->neurons[i]->output(input, size);
         *logs += "S" + QString::number(i) + " = " + QString::number(temp) + "\n";
        if (max < temp)
        {
            max = temp;
            index = i;
        }
    }
    QString S = index?QString::number(index):"n";
    *logs += "Winner is S" + S + + " = " + QString::number(max)+ "\n";

    if (index == 0) // winner is 0 neuron
    {
       *logs += "Remember as a new neuron\n";
       remember_input(input, size);
       return;
    }

    double result;
    double C[size];
    int diff = 0;
     *logs += "C ";
    for(i=0; i < size; i++)
    {
        if (input[i] > compare->neurons[index]->vector[i])
        {
            diff++;
            C[i] = 0;
        }
        else C[i] = input[i];
         *logs += QString::number(C[i]) + " ";
    }
    result = (double) (size-diff)/ size;

    if (result > border_value)
    {
        *logs += "\n result = " + QString::number(result) + " > " + QString::number(border_value,'f',2) + "\n";
        *logs += "Update neuron #" + QString::number(index) + "\n";
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
        *logs += "\nresult = " + QString::number(result) + " < " + QString::number(border_value,'f',2) + "\n";
        *logs += "Remember as a new neuron\n";
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
        qDebug() << i << L << input[i] << sum << L*input[i]/(L-1+sum);
        input[i] = L*input[i]/(L-1+sum);
    }
    recognition->new_neuron(input, size);
}
