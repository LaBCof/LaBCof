#pragma once
#include "D2Q9BC.h"

template <typename Int, typename Dub, class T>
class OpenBoundFrstOrd : public D2Q9BC<Int, Dub, T>
{
public:
	OpenBoundFrstOrd<Int, Dub, T>();
	OpenBoundFrstOrd<Int, Dub, T>(T& DataSt_);

	void scheme(RegProperties<Int, Dub, T> prop);

};

