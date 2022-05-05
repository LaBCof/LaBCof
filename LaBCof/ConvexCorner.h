#pragma once
#include "D2Q9BC.h"

template <typename Int, typename Dub>
class ConvexCorner : public D2Q9BC<Int, Dub>
{
	Dub* fVal_tm1;

public:
	ConvexCorner<Int, Dub>();
	ConvexCorner<Int, Dub>(DataStBCIndirect<Int, Dub>& DataSt_);
	Int findNodeForExtrapolate(RegProperties<Int, Dub> prop);
	void scheme(RegProperties<Int, Dub> prop);
};

