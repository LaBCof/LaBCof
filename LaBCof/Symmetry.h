#pragma once
#include "D2Q9BC.h"

template <typename Int, typename Dub, class T>
class Symmetry : public D2Q9BC<Int, Dub, T>
{
public:
	Symmetry<Int, Dub, T>();
	Symmetry<Int, Dub, T>(T& DataSt_);

	void scheme(RegProperties<Int, Dub, T> prop);

};

