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
#include "MomMethod.h"
#include "MomMethod.cpp"
#include "Periodic.h"
#include "Periodic.cpp"
#include "Open.h"
#include "Open.cpp"
#include "ConvxCornMomMethod.h"
#include "ConvxCornMomMethod.cpp"
#include "ConvexCorner.h"
#include "ConvexCorner.cpp"

template <typename int1, typename int2, typename Dub, class T>
class MainBC
{

private:
	T dataStBC;

	BouncBackFW<int1, int2, Dub, T> bouncBackFW;
	ZouHePress<int1, int2, Dub, T> zouHePress;
	ZouHeVelocity<int1, int2, Dub, T> zouHeVelocity;
	MomMethod<int1, int2, Dub, T> momentmethod;
	Symmetry<int1, int2, Dub, T> symmetry;
	Periodic<int1, int2, Dub, T> periodic;
	Open<int1, int2, Dub, T> openBoundFrstOrd;

	ConvxCornMomMethod<int1, int2, Dub, T> convexCornerMomentMethod;
	ConvexCorner<int1, int2, Dub, T> convexCorner;
public:
	MainBC<int1, int2, Dub, T>();
	~MainBC<int1, int2, Dub, T>();
	MainBC<int1, int2, Dub, T>(T& dataStBC);
	void bcPDFvCalculation();
};


