#pragma once
#include "D2Q9BC.h"

template <typename Int, typename Dub, class T>
class ConvexCorner : public D2Q9BC<Int, Dub, T>
{
	Dub* fVal_tm1;

public:
	ConvexCorner<Int, Dub, T>();
	ConvexCorner<Int, Dub, T>(T& DataSt_);
	Int findNodeForExtrapolate(RegProperties<Int, Dub, T> prop);
	void scheme(RegProperties<Int, Dub, T> prop);
};

