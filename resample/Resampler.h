// Simple resampler.
// Resample using linear interpolation

#pragma once

class Resampler
{

public:
	template <class I, class O>
	static void resample(const I* source, int sourceLength, double sourceSampleRate, O* target, double targetSampleRate);

};