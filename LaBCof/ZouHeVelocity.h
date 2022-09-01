#pragma once
#include "D2Q9BC.h"

template <typename Int, typename Dub, class T>
class ZouHeVelocity : public D2Q9BC<Int, Dub, T>
{

public:
	ZouHeVelocity<Int, Dub, T>();
	ZouHeVelocity(T& DataSt_);
	void scheme(RegProperties<Int, Dub, T> prop);
};



