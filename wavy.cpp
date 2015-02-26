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

    data.values = new int[test_length];
    for (int i = 0; i < test_length; i++)
    {
        int freq = test_length - i;
        data.values[i] = 40*(i % freq);
    }
    data.channels = 1;
    data.samples  = test_length;
    data.sample_rate = 44100;
    data.sample_resolution = 2;

    writeWav("test.wav",&data);

    return 0;
}