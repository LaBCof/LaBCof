#include "MainBC.h"

template <typename Int, typename Dub, class T>
MainBC<Int, Dub, T>::MainBC()
{
}

template <typename Int, typename Dub, class T>
MainBC<Int, Dub, T>::~MainBC()
{
}

template <typename Int, typename Dub, class T>
MainBC<Int, Dub, T>::MainBC(T& dataStBC_)
{
	dataStBC = dataStBC_;

	bouncBackFW = BouncBackFW<Int, Dub, T>(dataStBC);
	zouHeVelocity = ZouHeVelocity<Int, Dub, T>(dataStBC);
	zouHePress = ZouHePress<Int, Dub, T>(dataStBC);
	momentmethod = Momentmethod<Int, Dub, T>(dataStBC);
	symmetry = Symmetry<Int, Dub, T>(dataStBC);
	periodic = Periodic<Int, Dub, T>(dataStBC);
	openBoundFrstOrd = OpenBoundFrstOrd<Int, Dub, T>(dataStBC);

	convexCornerMomentMethod = ConvexCornerMomentMethod<Int, Dub, T>(dataStBC);
	convexCorner = ConvexCorner<Int, Dub, T>(dataStBC);

}

template <typename Int, typename Dub, class T>
void MainBC<Int, Dub, T>::bcPDFvCalculation() {

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
















