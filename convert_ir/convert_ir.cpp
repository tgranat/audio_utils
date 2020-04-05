
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
        cout << "writes the data as text to <output filename>.data" << endl;
        cout << "and writes the data as a float vector to <output filename>.h" << endl;
        cout << "<vector name> can be given as third argument. If not given, <output filename>"  << endl;
        cout << "will be used as the vector name so it has to conform cith C++ naming rules." << endl;
        cout << "Syntax:" << endl;
        cout << argv[0] << " <IR filename> <output filename> [<vector name>]" << endl;
        return 1;
    }

    SndfileHandle infile;
    FILE *outfile = NULL;
    FILE *headerfile = NULL;
    string IRfilename(argv[1]);
    string outfilename(argv[2]);
    outfilename.append(".data");
    string headerfilename(argv[2]);
    headerfilename.append(".h");
    string vectorname("");
    if (argc == 4) {
        vectorname.append(argv[3]);
    }
    else {
        vectorname.append(argv[2]);
    }
   
    infile = SndfileHandle(IRfilename.c_str());

    if (infile.error() != SF_ERR_NO_ERROR) {
        cout << "Error while opening IR file " << IRfilename << endl;
        cout << infile.strError() << endl;
        return 1;
    }
    
    errno_t err;
    err = fopen_s(&outfile, outfilename.c_str(), "w");
    if (err != 0) {
        cout << "Not able to open output file " << outfilename << endl; 
        cout << "err=" << err << endl;
        return 1;
    };

    err = fopen_s(&headerfile, headerfilename.c_str(), "w");
    if (err != 0) {
        cout << "Not able to open header file " << headerfilename << endl;
        cout << "err=" << err << endl;
        return 1;
    };


    cout << "Reading from: " << IRfilename << endl;
    cout << "Vector is named: " << vectorname << endl;
    cout << "Writing to: " << outfilename << " and " << headerfilename << endl;
    printFileInfo(IRfilename);

    int frames = infile.frames();
    int channels = infile.channels();
    int totalFrames = frames * channels;
     
    float* inbuffer = new float[totalFrames];
    int readcount =  infile.read(inbuffer, totalFrames);
 
    fprintf(headerfile, "#pragma once\n");
    fprintf(headerfile, "// Generated from %s\n", IRfilename.c_str());
    fprintf(headerfile, "namespace BinaryData {\n");
    fprintf(headerfile, "static const std::vector<float> %s {\n", vectorname.c_str());

    for (int i = 0; i < totalFrames; i++) {
        //printf("%.8ef,\n", (float) inbuffer[i]);
        if (i < totalFrames - 1) {
            fprintf(outfile, " %.8ef,\n", inbuffer[i]);
            fprintf(headerfile, " %.8ef,\n", inbuffer[i]);
        } else {
            fprintf(outfile, " %.8ef", inbuffer[i]);
            fprintf(headerfile, " %.8ef,\n", inbuffer[i]);
        }
    }

    fprintf(headerfile, "}; \n}\n");

    cout << readcount << " frames read and written." << endl;
}
