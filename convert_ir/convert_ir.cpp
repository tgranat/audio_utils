
#include <stdio.h>
#include <sndfile.hh>
#include <iostream>
#include <vector>
using namespace std;

void printFileInfo(SndfileHandle sf) {
    cout << "    Sample rate : " << sf.samplerate() << endl;
    cout << "    Channels    : " << sf.channels() << endl;
    cout << "    Frames      : " << sf.frames() << endl;
    cout << "    Format      : ";

    switch (sf.format() & SF_FORMAT_TYPEMASK) {
    case SF_FORMAT_CAF:
        cout << "CAF" << endl;
        break;
    case SF_FORMAT_WAV:
        cout << "WAV" << endl;
        break;
    case SF_FORMAT_AIFF:
        cout << "AIFF" << endl;
        break;
    default:
        cout << "other: " << (sf.format() & SF_FORMAT_TYPEMASK) << endl;
    }
    cout << "    PCM         : ";
    switch (sf.format() & SF_FORMAT_SUBMASK) {
    case SF_FORMAT_PCM_16:
        cout << "16 bit" << endl;
        break;
    case SF_FORMAT_PCM_24:
        cout << "24 bit" << endl;
        break;
    case SF_FORMAT_PCM_32:
        cout << "32 bit" << endl;;
        break;
    case SF_FORMAT_FLOAT:
        cout << "32 bit float" << endl;
        break;
    default:
        cout << "other: " << (sf.format() & SF_FORMAT_SUBMASK) << endl;
    }
}

int main(int argc, char* argv[])
{
    if (argc < 3) {
        cout << "This program read an impulse response file <IR filename> and" << endl;
        cout << "writes the data as text to <output filename>." << endl;
        cout << "Syntax:" << endl;
        cout << argv[0] << " <IR filename> <output filename>" << endl;
        return 1;
    }

    SndfileHandle infile;
    FILE *outfile = NULL;
    char* IRfilename = argv[1];
    char* outfilename = argv[2];

    infile = SndfileHandle(IRfilename);

    if (infile.error() != SF_ERR_NO_ERROR) {
        cout << "Error while opening IR file " << IRfilename << endl;
        cout << infile.strError() << endl;
        return 1;
    }
    
    errno_t err;
    err = fopen_s(&outfile, outfilename, "w");
    if (err != 0) {
        cout << "Not able to open output file " << outfilename << endl; 
        cout << "err=" << err << endl;
        return 1;
    };

    cout << "Reading from: " << IRfilename << endl;
    cout << "Writing to: " << outfilename << endl;
    printFileInfo(IRfilename);

    int frames = infile.frames();
    int channels = infile.channels();
    int totalFrames = frames * channels;
     
    float* inbuffer = new float[totalFrames];
    int readcount =  infile.read(inbuffer, totalFrames);
 
    for (int i = 0; i < totalFrames; i++) {
        //printf("%.8ef,\n", (float) inbuffer[i]);
        fprintf(outfile, " %.8ef,\n", inbuffer[i]);
    }
    
    cout << readcount << " frames read and written." << endl;
}
