#pragma once
#include <iostream>
#include "DataStBCIndirect.h"
//typedef long long Int Int;

template <typename Int, typename Dub>
struct RegProperties
{
	Int pos;
	Dub u;
	Dub v;
	Dub rho;
	Int *PDFidx;
	Dub *PDFval;
	Int angle;
	bool flip;
};

template <typename Int, typename Dub>
class D2Q9BC
{

public:
	DataStBCIndirect<Int, Dub> DataSt;
	Int nVec; 
	Int schemeInx;

	Dub* bcPDFv;
	Int * bcPDFi;
	Int* orient;
	Int* iBondNode;
	Int nReg;
	Int *nNodeReg;
	Int nBoundNode;

	Int* BCidx;
	Dub* rho;
	Dub* xVel;
	Dub* yVel;

	RegProperties<Int, Dub> regPropContaInter = RegProperties<Int, Dub>();

public:
	D2Q9BC<Int, Dub>();
	~D2Q9BC<Int, Dub>();
	D2Q9BC<Int, Dub>(DataStBCIndirect<Int, Dub>& DataSt);

	void execut();
	virtual void scheme(RegProperties<Int, Dub> regPropContaInter) = 0;
};

