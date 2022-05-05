#pragma once
#include "D2Q9BC.h"

template <typename Int, typename Dub>
class ZouHePress : public D2Q9BC<Int, Dub>
{
public:
	ZouHePress<Int, Dub>();
	ZouHePress<Int, Dub>(DataStBCIndirect<Int, Dub>& DataSt_);
	void scheme(RegProperties<Int, Dub> prop);
};
