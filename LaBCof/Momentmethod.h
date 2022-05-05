#pragma once
#include "D2Q9BC.h"

template <typename Int, typename Dub>
class Momentmethod : public D2Q9BC<Int, Dub>
{

public:
	Momentmethod<Int, Dub>();
	Momentmethod<Int, Dub>(DataStBCIndirect<Int, Dub>& DataSt_);

	void scheme(RegProperties<Int, Dub> prop);

};