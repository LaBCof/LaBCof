#pragma once
#include "D2Q9BC.h"

template <typename Int, typename Dub, class T>
class Momentmethod : public D2Q9BC<Int, Dub, T>
{

public:
	Momentmethod<Int, Dub, T>();
	Momentmethod<Int, Dub, T>(T& DataSt_);

	void scheme(RegProperties<Int, Dub, T> prop);

};