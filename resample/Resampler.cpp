#include "Resampler.h"
#include <cmath>
#include <vector>
#include <iostream>

// Resamples an audio buffer 

template <class I, class O> 
void Resampler::resample(const I* source, int sourceLength, double sourceSampleRate, O* target, double targetSampleRate)
{
	if (sourceSampleRate != targetSampleRate) {
		// Resample using linear interpolation.
		double pos = 0.;
		double delta = sourceSampleRate / targetSampleRate;
		int targetLength = targetSampleRate / sourceSampleRate * (double)sourceLength + 0.5;
		for (int i = 0; i < targetLength; ++i)
		{
			int idx = int(pos);
			if (idx < sourceLength)
			{
				double frac = pos - floor(pos);
				double interp = (1. - frac) * source[idx];
				if (++idx < sourceLength) {
					interp += frac * source[idx];
				}
				pos += delta;
				*target++ = (O)(delta * interp);
			}
			else
			{
				*target++ = 0;
			}
		}

	}
	else {
		// No need for resample
		for (int i = 0; i < sourceLength; ++i) {
			target[i] = (O)source[i];
		}
	}
}

// Test implementation

const std::vector<float> ir_testdata_44100Hz =
{
	#include "ir_testdata_44100Hz.data"
};
int main(int argc, char* argv[])
{

	int sourceLen = ir_testdata_44100Hz.size();
	double sourceSampleRate = 44100.f;
	double resampledSampleRate = 48000.f;
	int targetLength = resampledSampleRate / sourceSampleRate * (double)sourceLen + 0.5;
	std::vector<float> resampledData(targetLength);

	Resampler::resample(ir_testdata_44100Hz.data(), sourceLen, sourceSampleRate, resampledData.data(), resampledSampleRate);
	std::cout << "Test implementation." << std::endl;
	std::cout << "Source size:" << ir_testdata_44100Hz.size() << std::endl;
	std::cout << "Resampled size: " << resampledData.size() << std::endl;
}

