#pragma once
#include "D2Q9BC.h"

template <typename int1, typename int2, typename Dub, class T>
class ConvexCorner : public D2Q9BC<int1, int2, Dub, T>
{
	Dub* fVal_tm1;

public:
	ConvexCorner<int1, int2, Dub, T>();
	ConvexCorner<int1, int2, Dub, T>(T& DataSt_);
	int2 findNodeForExtrapolate(RegProperties<int1, int2, Dub, T> prop);
	void scheme(RegProperties<int1, int2, Dub, T> prop);
};

