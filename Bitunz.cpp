#include "Bitunz.h"
#include "IPlug_include_in_plug_src.h"
#include "IControl.h"
#include "resource.h"

const int kNumPrograms = 1;

template <typename T> int sgn(T val) {
	return (T(0) < val) - (val < T(0));
}

enum EParams
{
	kBit1 = 0,
	kBit2,
	kBit3,
	kBit4,
	kBit5,
	kBit6,
	kBit7,
	kBit8,

	kDownsample,

	kDry,
	kWet,

	kNumParams
};


enum EBitState
{
	kBitOn = 0,
	kBitInv = 1,
	kBitOff = 2,

	kNumBitStates = 3
};

Bitunz::Bitunz(IPlugInstanceInfo instanceInfo)
	: IPLUG_CTOR(kNumParams, kNumPrograms, instanceInfo), mDownsample(1), mCurrentSample(0), mDry(1.0), mWet(0.0)
{
	TRACE;

	// -------- INIT PARAMS ----------
	for (int i = 0; i < kNumBits; i++){ // ranges from kBit1 to kBit8

		/* init the off and invert bit to no effect */
		mOnOffBits[i] = 1;
		mInvertBits[i] = 0;

		/* init the IParam for the bits */
		char BitLabel[8];
		sprintf(BitLabel, "Bit %d", i + 1);
		GetParam(i)->InitEnum(BitLabel, 0, kNumBitStates);
		GetParam(i)->SetDisplayText(kBitOn, "On");
		GetParam(i)->SetDisplayText(kBitInv, "Inv");
		GetParam(i)->SetDisplayText(kBitOff, "Off");

	}

	GetParam(kDownsample)->InitInt("Downsample", 1, 1, 64);

	GetParam(kDry)->InitDouble("Dry", -61.0, -61.0, 0., 0.2, "dB", "", 0.2);
	GetParam(kWet)->InitDouble("Wet", 0.0, -61.0, 0., 0.2, "dB", "", 0.2);
	
	//MakePreset("preset 1", ... );
	MakeDefaultPreset((char *) "-", kNumPrograms);
}

Bitunz::~Bitunz() {}

void Bitunz::ProcessDoubleReplacing(double** inputs, double** outputs, int nFrames)
{
	// Mutex is already locked for us.

	int nChannels = (IsInChannelConnected(1) && IsOutChannelConnected(1) ? 2 : 1);

	for (int channel = 0; channel < nChannels; channel++){
		for (int frame = 0; frame < nFrames; frame++)
		{
			double in = inputs[channel][frame];
			double out = inputs[channel][frame];

			/* downsampling with sample and hold */
			if (frame % mDownsample == 0){
				mCurrentSample = in;
			}

			out = mCurrentSample;

			/* bit crusher */
			/* I took the algorithm from this brilliant video
			https://www.youtube.com/watch?v=ohYQe5kzZg8 and ported it into C++ */
			if (!mOnOffBits.all() || mInvertBits.any()){
				/* enters the if only if at least one bit is different from "on" */

				/* This avoids noise when the plug-in is chained to an analog input audio:
				when there is no sound in, values slightly different from 0 due to the cable noise 
				will be amplified by the bit manipulation and result in awful noise.
				*/
				if (out < 0.01 && out > -0.01){
					out = 0.0;
				}

				int signIn = sgn(out);

				out = std::abs(out);
				out *= 255.0;

				unsigned int roundedIn = int(round(out));
				roundedIn &= mOnOff;
				roundedIn ^= mInvert;

				out = (double(roundedIn) / 255.0) * signIn;
			}

			outputs[channel][frame] = mix(in, out); // in is the wet now 
		}
	}
}

void Bitunz::Reset()
{
	TRACE;
	IMutexLock lock(this);

	//double sr = GetSampleRate();
}

void Bitunz::OnParamChange(int paramIdx)
{
	IMutexLock lock(this);

	switch (paramIdx) {
	case kDownsample:{
		mDownsample = GetParam(paramIdx)->Int();
	}; break;

	case kDry: {
		if (GetParam(kDry)->Value() < -60.){ // when it goes below 60db just turn it off
			mDry = 0.0;
		}
		else {
			mDry = ::DBToAmp(GetParam(kDry)->Value());
		}

	}; break;

	case kWet: {
		if (GetParam(kWet)->Value() < -60.0){
			mWet = 0.0;
		}
		else{
			mWet = ::DBToAmp(GetParam(kWet)->Value());
		}
	}; break;

	default: { // executed for bits, paramIdx = 0 - 7

		int bit = GetParam(paramIdx)->Int();

		switch (bit) {
		case kBitOn:
			mOnOffBits.set(paramIdx, 1);
			mOnOff = mOnOffBits.to_ulong();

			mInvertBits.set(paramIdx, 0);
			mInvert = mInvertBits.to_ulong();
			break;
		case kBitOff:
			mOnOffBits.set(paramIdx, 0);
			mOnOff = mOnOffBits.to_ulong();

			mInvertBits.set(paramIdx, 0);
			mInvert = mInvertBits.to_ulong();
			break;
		case kBitInv:
			mOnOffBits.set(paramIdx, 1);
			mOnOff = mOnOffBits.to_ulong();

			mInvertBits.set(paramIdx, 1);
			mInvert = mInvertBits.to_ulong();
			break;
		}
	};  break; // outer switch default:
	}
}

