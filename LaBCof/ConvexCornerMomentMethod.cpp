#include "ConvexCornerMomentMethod.h"

template <typename Int, typename Dub>
ConvexCornerMomentMethod<Int, Dub>::ConvexCornerMomentMethod(){

}
template <typename Int, typename Dub>
ConvexCornerMomentMethod<Int, Dub>::ConvexCornerMomentMethod(DataStBCIndirect<Int, Dub>& DataSt_) :D2Q9BC<Int, Dub>(DataSt_){
	this->schemeInx = 10002;

	std::cout << "ConvexCornerMomentMethod obj done" << std::endl;
}

template <typename Int, typename Dub>
void ConvexCornerMomentMethod<Int, Dub>::scheme(RegProperties<Int, Dub> prop) {

	Dub rho = prop.PDFval[0] + 2 * (prop.PDFval[5] + prop.PDFval[7]) + 4 * prop.PDFval[6];

	prop.PDFval[1] = (2. / 3) * rho - prop.PDFval[0] - prop.PDFval[5];
	prop.PDFval[3] = (2. / 3) * rho - prop.PDFval[0] - prop.PDFval[7];
	prop.PDFval[8] = (1. / 6) * rho - prop.PDFval[7] - prop.PDFval[6];
	prop.PDFval[2] = -(2. / 3) * rho + prop.PDFval[0] + prop.PDFval[7] + prop.PDFval[5] + prop.PDFval[6];
	prop.PDFval[4] = (1. / 6) * rho - prop.PDFval[5] - prop.PDFval[6];

}










