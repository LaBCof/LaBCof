#pragma once
#include <iostream>
#include <iomanip> 
#include <vector>

#include "BouncBackFW.h"
#include "BouncBackFW.cpp"
#include "ZouHePress.h"
#include "ZouHePress.cpp"
#include "ZouHeVelocity.h"
#include "ZouHeVelocity.cpp"
#include "Symmetry.h"
#include "Symmetry.cpp"
#include "Momentmethod.h"
#include "Momentmethod.cpp"
#include "Periodic.h"
#include "Periodic.cpp"
#include "OpenBoundFrstOrd.h"
#include "OpenBoundFrstOrd.cpp"
#include "ConvexCornerMomentMethod.h"
#include "ConvexCornerMomentMethod.cpp"
#include "ConvexCorner.h"
#include "ConvexCorner.cpp"

template <typename Int, typename Dub>
class MainBC
{

private:
	DataStBCIndirect<Int, Dub> dataStBC;

	BouncBackFW<Int, Dub> bouncBackFW;
	ZouHePress<Int, Dub> zouHePress;
	ZouHeVelocity<Int, Dub> zouHeVelocity;
	Momentmethod<Int, Dub> momentmethod;
	Symmetry<Int, Dub> symmetry;
	Periodic<Int, Dub> periodic;
	OpenBoundFrstOrd<Int, Dub> openBoundFrstOrd;

	ConvexCornerMomentMethod<Int, Dub> convexCornerMomentMethod;
	ConvexCorner<Int, Dub> convexCorner;
public:
	MainBC<Int, Dub>();
	~MainBC<Int, Dub>();
	MainBC<Int, Dub>(DataStBCIndirect<Int, Dub>& dataStBC);
	void bcPDFvCalculation();
};


