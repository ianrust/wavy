#ifndef PCM_WAV_GEN
#define PCM_WAV_GEN

#include <iostream>
#include <fstream>

#include "wavytypes.h"

//This website was very useful to make this:
//http://www-mmsp.ece.mcgill.ca/documents/AudioFormats/WAVE/WAVE.html

using namespace std;

// Write a 4-byte char array to the file (only size needed for the wav format)
static void writeString(const char * const string, ofstream * const file)
{
    file->write(string,4);
}

//write any value in as many bytes specified
static void writeValue(const int value,const int num_bytes_used, ofstream * const file)
{
    char byte;
    for (int i = 0; i < num_bytes_used; i++)
    {
        byte = (value >> 8*i) & 0xFF; //loop through the chunks of data and grab the byte;
        file->write(&byte,1);
    }
}

static void writeHeader(const Data * const data, ofstream * const file)
{
    writeString("RIFF",file);
    int pad_size = (data->sample_resolution * data->channels * data->samples) % 2;
    writeValue(36 + data->sample_resolution * data->channels * data->samples + pad_size,4,file); //size of all the data
    writeString("WAVE",file);
}

static void writeFormat(const Data * const data, ofstream * const file)
{
    writeString("fmt ",file);
    writeValue(16,4,file); //size of stuff to come
    writeValue(1,2,file); //Format tag, hard-coded to PCM until this becomes wavgen.h not pcmwavgen.h
    writeValue(data->channels,2,file);
    writeValue(data->sample_rate,4,file);
    writeValue(data->sample_rate * data->sample_resolution * data->channels,4,file); //Bytes per second
    writeValue(data->sample_resolution * data->channels,2,file); //Bytes per point in time
    writeValue(data->sample_resolution * 8,2,file); //number of bits per sample
}

static void writeData(const Data * const data, ofstream * const file)
{
    writeString("data",file);
    writeValue(data->sample_resolution * data->channels * data->samples,4,file); //bytes of data to be contained in the file;

    //loop through the data and write it
    for (int s = 0; s < data->samples; s++)
    {
        for (int c = 0; c < data->channels; c++)
        {
            writeValue(data->values[c][s],data->sample_resolution,file);
        }
    }

    writeValue(0,(data->sample_resolution * data->channels * data->samples) % 2,file); //padding byte;
}

void writeWav(const char * const filename,const Data * const data)
{
    //Create file object to shove data into. This will be passed around to put all the stuff in it
    ofstream file (filename,ios::out | ios::binary);

    //Write header chunk needed for any .wav file
    writeHeader(data,&file);

    // //Write format chunk
    writeFormat(data,&file);

    // //Write data chunk to the file
    writeData(data,&file);

    file.close();
}

#endif