#pragma once
#include "D2Q9BC.h"

template <typename int1, typename int2, typename Dub, class T>
class Periodic : public D2Q9BC<int1, int2, Dub, T>
{
public:
	int2 nPeriodicPDF = 0;
	//int2*periodicPDF1;
	//int2*periodicPDF2;
	int2* corespondingNode;

	int2* nNodeReg;
	int2 nBoundNode;

public:
	Periodic<int1, int2, Dub, T>();
	Periodic<int1, int2, Dub, T>(T& DataSt_);

	void findCorespondingNodes(int2 reg1, int2 reg2);
	void findPeriodicRegions(int2& reg1, int2& reg2);

	void scheme(RegProperties<int1, int2, Dub, T> prop);

};

