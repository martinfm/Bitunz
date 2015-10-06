#ifndef __BITUNZ__
#define __BITUNZ__

#include "IPlug_include_in_plug_hdr.h"

#include <bitset>

class Bitunz : public IPlug
{
public:

  static const int kNumBits = 8;
  Bitunz(IPlugInstanceInfo instanceInfo);
  ~Bitunz();

  void Reset();
  void OnParamChange(int paramIdx);

  void ProcessDoubleReplacing(double** inputs, double** outputs, int nFrames);

  inline double mix(double dry, double wet) const {
	  return dry * mDry + wet * mWet;
  }

private:

	/* bit crusher */
	std::bitset<kNumBits> mOnOffBits;
	std::bitset<kNumBits> mInvertBits;
	unsigned int mOnOff;
	unsigned int mInvert;

	/* downsample */
	int mDownsample;
	double mCurrentSample;

	/* dry/wet */
	double mDry;
	double mWet;

};

#endif


