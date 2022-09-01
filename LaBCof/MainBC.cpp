#include "MainBC.h"

template <typename int1, typename int2, typename Dub, class T>
MainBC<int1, int2, Dub, T>::MainBC()
{
}

template <typename int1, typename int2, typename Dub, class T>
MainBC<int1, int2, Dub, T>::~MainBC()
{
}

template <typename int1, typename int2, typename Dub, class T>
MainBC<int1, int2, Dub, T>::MainBC(T& dataStBC_)
{
	dataStBC = dataStBC_;

	bouncBackFW = BouncBackFW<int1, int2, Dub, T>(dataStBC);
	zouHeVelocity = ZouHeVelocity<int1, int2, Dub, T>(dataStBC);
	zouHePress = ZouHePress<int1, int2, Dub, T>(dataStBC);
	momentmethod = MomMethod<int1, int2, Dub, T>(dataStBC);
	symmetry = Symmetry<int1, int2, Dub, T>(dataStBC);
	periodic = Periodic<int1, int2, Dub, T>(dataStBC);
	openBoundFrstOrd = Open<int1, int2, Dub, T>(dataStBC);

	convexCornerMomentMethod = ConvxCornMomMethod<int1, int2, Dub, T>(dataStBC);
	convexCorner = ConvexCorner<int1, int2, Dub, T>(dataStBC);

}

template <typename int1, typename int2, typename Dub, class T>
void MainBC<int1, int2, Dub, T>::bcPDFvCalculation() {

	dataStBC.get_bcPDFvFromLBM();

	bouncBackFW.execut();
	zouHeVelocity.execut();
	zouHePress.execut();
	momentmethod.execut();
	symmetry.execut();
	periodic.execut();
	openBoundFrstOrd.execut();

	convexCornerMomentMethod.execut();
	convexCorner.execut();

	dataStBC.write_bcPDFvToLBM();
}
















