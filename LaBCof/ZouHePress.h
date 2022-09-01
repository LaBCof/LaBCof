#pragma once
#include "D2Q9BC.h"
//#include "D2Q9BC.cpp"

template <typename Int, typename Dub, class T>
class ZouHePress : public D2Q9BC<Int, Dub, T>
{
public:
	ZouHePress<Int, Dub, T>();
	ZouHePress<Int, Dub, T>(T& DataSt_);
	void scheme(RegProperties<Int, Dub, T> prop);
};
