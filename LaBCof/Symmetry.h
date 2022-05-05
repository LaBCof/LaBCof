#pragma once
#include "D2Q9BC.h"

template <typename Int, typename Dub>
class Symmetry : public D2Q9BC<Int, Dub>
{
public:
	Symmetry<Int, Dub>();
	Symmetry<Int, Dub>(DataStBCIndirect<Int, Dub>& DataSt_);

	void scheme(RegProperties<Int, Dub> prop);

};

