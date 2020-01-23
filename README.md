# audio_utils
Audio utility programs.

So far:

### convert_ir

Made this program to read an impulse response file and write the data as text to another file. Result looks like (example):

```
1.34298682e-01f,
4.98918891e-01f,
8.79464746e-01f,
9.99999881e-01f,
.30221534e-01f,
4.50268507e-01f,
```
etc.

Using libsndfile to read the audio file.

Can of course be used to read any audio file supported by libsndfile. Tested with wav files.

### resample

Simple resampler that uses linear interpolation.