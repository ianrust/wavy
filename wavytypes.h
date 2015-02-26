#ifndef WAVY_TYPES
#define WAVY_TYPES

struct Data
{
    int * values; //array of values
    int channels; //number of channels
    int samples; //total number of samples (eg if there are 2 channels, 2 values at the same time is considered 1 sample)
    int sample_rate; //number of samples per second
    int sample_resolution; //number of bytes in a sample
};

#endif