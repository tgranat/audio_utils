# audio_utils
Audio utility programs I've made when working with audio plugins.


### convert_ir

Made this program to read an audio file and create two files that can be useful:
* .h file containing a ``static const vector<float>`` with the data
* .data file with the data as text 

It uses libsndfile to read the audio file. File formats supported by libsndfile should work, but is only tested with Wav.

Example to show format of the generated .h file:
```
namespace BinaryData {
static const std::vector<float> some_impulse_response {
 -7.33137131e-05f,
 -1.14083290e-04f,
```
etc.

Example to show format of the generated .data:
```
1.34298682e-01f,
4.98918891e-01f,
8.79464746e-01f,
9.99999881e-01f,
.30221534e-01f,
4.50268507e-01f,
```
etc.

### resample

Simple resampler that uses linear interpolation.