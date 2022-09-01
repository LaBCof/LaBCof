#pragma once
#include <iostream>
//#include "DataStBCIndirect.h"
//typedef long long Int Int;
#include "..\TypeDefinition.h"



template <typename Int, typename Dub, class T>
struct RegProperties
{
	Int pos;
	Dub u;
	Dub v;
	Dub rho;
	ULLI*PDFidx;
	Dub *PDFval;
	Int angle;
	bool flip;
};

template <typename Int, typename Dub, class T>
class D2Q9BC
{

public:
	T DataSt;
	Int nVec; 
	Int schemeInx;

	Dub* bcPDFv;
	ULLI* bcPDFi;
	Int* orient;
	Int* iBondNode;
	Int nReg;
	Int *nNodeReg;
	Int nBoundNode;

	Int* BCidx;
	Dub* rho;
	Dub* xVel;
	Dub* yVel;

	RegProperties<Int, Dub, T> regPropContaInter = RegProperties<Int, Dub, T>();

public:
	D2Q9BC<Int, Dub, T>();
	~D2Q9BC<Int, Dub, T>();
	D2Q9BC<Int, Dub, T>(T& DataSt);

	void execut();
	virtual void scheme(RegProperties<Int, Dub, T> regPropContaInter) = 0;
};

