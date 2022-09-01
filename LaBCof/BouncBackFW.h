#pragma once
#include "D2Q9BC.h"
#include "D2Q9BC.cpp"

template <typename int1, typename int2, typename Dub, class T>
class BouncBackFW : public D2Q9BC<int1, int2, Dub, T>
{
private:
	Dub* fVal_tm1;
	Dub tmpFval[9];
	Dub* fi_tm1;
	Dub fi[9];
	int2 count = 0;

	double Fx = 0.0;
	double Fy = 0.0;

public:
	BouncBackFW<int1, int2, Dub, T>();
	BouncBackFW<int1, int2, Dub, T>(T& DataSt_);
	void scheme(RegProperties<int1, int2, Dub, T> prop);

};












