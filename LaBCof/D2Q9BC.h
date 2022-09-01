#pragma once
#include <iostream>

template <typename int1, typename int2, typename Dub, class T>
struct RegProperties
{
	int2 pos;
	Dub u;
	Dub v;
	Dub rho;
	int1*PDFidx;
	Dub *PDFval;
	int2 angle;
	bool flip;
};

template <typename int1, typename int2, typename Dub, class T>
class D2Q9BC
{

public:
	T DataSt;
	int2 nVec; 
	int2 schemeInx;

	Dub* bcPDFv;
	int1* bcPDFi;
	int2* orient;
	int2* iBondNode;
	int2 nReg;
	int2 *nNodeReg;
	int2 nBoundNode;

	int2* BCidx;
	Dub* rho;
	Dub* xVel;
	Dub* yVel;

	RegProperties<int1, int2, Dub, T> regPropContaInter = RegProperties<int1, int2, Dub, T>();

public:
	D2Q9BC<int1, int2, Dub, T>();
	~D2Q9BC<int1, int2, Dub, T>();
	D2Q9BC<int1, int2, Dub, T>(T& DataSt);

	void execut();
	virtual void scheme(RegProperties<int1, int2, Dub, T> regPropContaInter) = 0;
};

