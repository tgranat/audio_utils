
#include <stdio.h>
#include <sndfile.hh>
#include <iostream>
#include <vector>

using namespace std;

void printFileInfo(SndfileHandle sf) {
    cout << "    Format      : ";

    switch (sf.format() & SF_FORMAT_TYPEMASK) {
    case SF_FORMAT_WAV:
        cout << "WAV" << endl;
        break;
    case SF_FORMAT_AIFF:
        cout << "AIFF" << endl;
        break;
    case SF_FORMAT_FLAC:
        cout << "FLAC" << endl;
        break;
    case SF_FORMAT_OGG:
        cout << "OGG" << endl;
        break;
    case SF_FORMAT_CAF:
        cout << "CAF" << endl;
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
    case SF_FORMAT_DOUBLE:
        cout << "64 bit float" << endl;
        break;
    default:
        cout << "other: " << (sf.format() & SF_FORMAT_SUBMASK) << endl;
    }

    cout << "    Sample rate : " << sf.samplerate() << endl;
    cout << "    Channels    : " << sf.channels() << endl;
    cout << "    Frames      : " << sf.frames() << endl;


    cout << "    Endianess   : ";
    switch (sf.format() & SF_FORMAT_ENDMASK) {
    case SF_ENDIAN_FILE:
        cout << "Default file endian-ness" << endl;
        break;
    case SF_ENDIAN_LITTLE:
        cout << "Force little endian-ness" << endl;
        break;
    case SF_ENDIAN_BIG:
        cout << "Force big endian-ness" << endl;
        break;
    case SF_ENDIAN_CPU:
        cout << "Force CPU endian-ness" << endl;
        break;
    default:
        cout << "other: " << (sf.format() & SF_FORMAT_ENDMASK) << endl;
    }
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        cout << "Display some basic information about an audio file." << endl;
        cout << "Using the 'libsndfile' library (http://www.mega-nerd.com/libsndfile)" << endl;
        cout << "Not all formats and encodings supported by libsndfile are displayed." << endl;
        cout << "Syntax:" << endl;
        cout << argv[0] << " <audio filename>" << endl;
        return 1;
    }


    string IRfilename(argv[1]);

    SndfileHandle infile;
    infile = SndfileHandle(IRfilename.c_str());

    if (infile.error() != SF_ERR_NO_ERROR) {
        cout << "Error while opening IR file " << IRfilename << endl;
        cout << infile.strError() << endl;
        return 1;
    }

    cout << "Reading from: " << IRfilename << endl;
    printFileInfo(IRfilename);

}
