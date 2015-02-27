#include <iostream>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

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

    float frequency = 500;
    data.sample_resolution = atoi(argv[1]);
    float amplitude = pow(2,data.sample_resolution*8 - 1);
    data.sample_rate = 44100;
    int test_length = data.sample_rate*5;

    data.channels = 2;
    data.values = new int*[data.channels];
    data.values[0] = new int[test_length];
    data.values[1] = new int[test_length];

    for (int i = 0; i < test_length; i++)
    {
        float t = i/float(data.sample_rate);
        int value = amplitude * (sin(t * frequency*2*M_PI) * sin(t * 2*frequency*2*M_PI) * sin(t * 1/100*frequency*2*M_PI));
        // std::cout << value << std::endl;
        if (i>test_length/2)
        {
            data.values[1][i] = value;
        }
        else
        {
            data.values[0][i] = value;
        }
    }

    data.samples  = test_length;

    writeWav("test.wav",&data);

    return 0;
}