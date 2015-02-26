#include <iostream>
#include <stdio.h>

#include "pcmwavgen.h"

using namespace std;

int main(int argc,const char * argv[])
{
    if (argc != 2)
    {
        cerr << "Incorrect Number of Inputs" << endl;
        return 1;
    }

    Data data;

    int test_length = 441000;

    data.channels = 2;
    data.values = new int*[data.channels];
    data.values[0] = new int[test_length];
    data.values[1] = new int[test_length];
    for (int i = 0; i < test_length; i++)
    {
        if (i>test_length/2)
        {
            int freq = test_length - i;
            data.values[0][i] = 40*(i % freq);
        }
        else
        {
            data.values[0][i] = 0;
        }
    }
    for (int i = 0; i < test_length; i++)
    {
        if (i<test_length/2)
        {
            data.values[1][i] = 40*(i % 100);
        }
        else
        {
            data.values[1][i] = 0;
        }
    }
    data.samples  = test_length;
    data.sample_rate = 44100;
    data.sample_resolution = 2;

    writeWav("test.wav",&data);

    return 0;
}