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

template <typename Int, typename Dub, class T>
class MainBC
{

private:
	T dataStBC;

	BouncBackFW<Int, Dub, T> bouncBackFW;
	ZouHePress<Int, Dub, T> zouHePress;
	ZouHeVelocity<Int, Dub, T> zouHeVelocity;
	Momentmethod<Int, Dub, T> momentmethod;
	Symmetry<Int, Dub, T> symmetry;
	Periodic<Int, Dub, T> periodic;
	OpenBoundFrstOrd<Int, Dub, T> openBoundFrstOrd;

	ConvexCornerMomentMethod<Int, Dub, T> convexCornerMomentMethod;
	ConvexCorner<Int, Dub, T> convexCorner;
public:
	MainBC<Int, Dub, T>();
	~MainBC<Int, Dub, T>();
	MainBC<Int, Dub, T>(T& dataStBC);
	void bcPDFvCalculation();
};


