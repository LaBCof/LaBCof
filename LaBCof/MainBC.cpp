#include "MainBC.h"

template <typename Int, typename Dub>
MainBC<Int, Dub>::MainBC()
{
}

template <typename Int, typename Dub>
MainBC<Int, Dub>::~MainBC()
{
}

template <typename Int, typename Dub>
MainBC<Int, Dub>::MainBC(DataStBCIndirect<Int, Dub>& dataStBC_)
{
	dataStBC = dataStBC_;

	bouncBackFW = BouncBackFW<Int, Dub>(dataStBC);
	zouHeVelocity = ZouHeVelocity<Int, Dub>(dataStBC);
	zouHePress = ZouHePress<Int, Dub>(dataStBC);
	momentmethod = Momentmethod<Int, Dub>(dataStBC);
	symmetry = Symmetry<Int, Dub>(dataStBC);
	periodic = Periodic<Int, Dub>(dataStBC);
	openBoundFrstOrd = OpenBoundFrstOrd<Int, Dub>(dataStBC);

	convexCornerMomentMethod = ConvexCornerMomentMethod<Int, Dub>(dataStBC);
	convexCorner = ConvexCorner<Int, Dub>(dataStBC);

}

template <typename Int, typename Dub>
void MainBC<Int, Dub>::bcPDFvCalculation() {

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
















