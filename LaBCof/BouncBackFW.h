#pragma once
#include "D2Q9BC.h"
#include "D2Q9BC.cpp"

template <typename Int, typename Dub>
class BouncBackFW : public D2Q9BC<Int, Dub>
{
private:
	Dub* fVal_tm1;
	Dub tmpFval[9];
	Dub* fi_tm1;
	Dub fi[9];

public:
	BouncBackFW<Int, Dub>();
	BouncBackFW<Int, Dub>(DataStBCIndirect<Int, Dub> & DataSt_);
	void scheme(RegProperties<Int, Dub> prop);

public:

	Dub collide(Dub fi, Dub u, Dub v, Dub rho, Dub Cx, Dub Cy, Dub w);

	Dub Rho(Dub* PDFv);

	Dub Ux(Dub* PDFv);

	Dub Uy(Dub* PDFv);

};












