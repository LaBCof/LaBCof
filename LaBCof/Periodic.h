#pragma once
#include "D2Q9BC.h"

template <typename Int, typename Dub>
class Periodic : public D2Q9BC<Int, Dub>
{
public:
	Int nPeriodicPDF = 0;
	Int *periodicPDF1;
	Int *periodicPDF2;
	Int* corespondingNode;

	Int* nNodeReg;
	Int nBoundNode;

public:
	Periodic<Int, Dub>();
	Periodic<Int, Dub>(DataStBCIndirect<Int, Dub>& DataSt_);

	void findCorespondingNodes(Int reg1, Int reg2);
	void findPeriodicRegions(Int& reg1, Int& reg2);

	void scheme(RegProperties<Int, Dub> prop);

};

