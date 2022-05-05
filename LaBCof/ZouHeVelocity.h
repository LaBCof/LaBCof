#pragma once
#include "D2Q9BC.h"

template <typename Int, typename Dub>
class ZouHeVelocity : public D2Q9BC<Int, Dub>
{

public:
	ZouHeVelocity<Int, Dub>();
	ZouHeVelocity(DataStBCIndirect<Int, Dub>& DataSt_);
	void scheme(RegProperties<Int, Dub> prop);
};



