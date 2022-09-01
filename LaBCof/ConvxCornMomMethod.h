#pragma once
#include "D2Q9BC.h"

template <typename int1, typename int2, typename Dub, class T>
class ConvxCornMomMethod : public D2Q9BC<int1, int2, Dub, T>
{
public:
	ConvxCornMomMethod<int1, int2, Dub, T>();
	ConvxCornMomMethod<int1, int2, Dub, T>(T& DataSt_);

	void scheme(RegProperties<int1, int2, Dub, T> prop);
};

