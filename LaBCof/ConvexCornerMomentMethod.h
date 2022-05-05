#pragma once
#include "D2Q9BC.h"

template <typename Int, typename Dub>
class ConvexCornerMomentMethod : public D2Q9BC<Int, Dub>
{
public:
	ConvexCornerMomentMethod<Int, Dub>();
	ConvexCornerMomentMethod<Int, Dub>(DataStBCIndirect<Int, Dub>& DataSt_);

	void scheme(RegProperties<Int, Dub> prop);
};

