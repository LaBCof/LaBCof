#pragma once
#include "D2Q9BC.h"

template <typename Int, typename Dub, class T>
class ConvexCornerMomentMethod : public D2Q9BC<Int, Dub, T>
{
public:
	ConvexCornerMomentMethod<Int, Dub, T>();
	ConvexCornerMomentMethod<Int, Dub, T>(T& DataSt_);

	void scheme(RegProperties<Int, Dub, T> prop);
};

