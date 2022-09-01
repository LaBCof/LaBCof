#pragma once
#include "D2Q9BC.h"
#include "D2Q9BC.cpp"

template <typename Int, typename Dub, class T>
class BouncBackFW : public D2Q9BC<Int, Dub, T>
{
private:
	Dub* fVal_tm1;
	Dub tmpFval[9];
	Dub* fi_tm1;
	Dub fi[9];
	Int count = 0;

	double Fx = 0.0;
	double Fy = 0.0;

public:
	BouncBackFW<Int, Dub, T>();
	BouncBackFW<Int, Dub, T>(T& DataSt_);
	void scheme(RegProperties<Int, Dub, T> prop);

public:

	Dub collide(Dub fi, Dub u, Dub v, Dub rho, Dub Cx, Dub Cy, Dub w);

	Dub Rho(Dub* PDFv);

	Dub Ux(Dub* PDFv);

	Dub Uy(Dub* PDFv);

};












