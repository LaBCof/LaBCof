#pragma once
#include "D2Q9BC.h"

template <typename Int, typename Dub>
class OpenBoundFrstOrd : public D2Q9BC<Int, Dub>
{
public:
	OpenBoundFrstOrd<Int, Dub>();
	OpenBoundFrstOrd<Int, Dub>(DataStBCIndirect<Int, Dub>& DataSt_);

	void scheme(RegProperties<Int, Dub> prop);

};

