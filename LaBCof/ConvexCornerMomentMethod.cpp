#include "ConvexCornerMomentMethod.h"

template <typename Int, typename Dub, class T>
ConvexCornerMomentMethod<Int, Dub, T>::ConvexCornerMomentMethod(){

}
template <typename Int, typename Dub, class T>
ConvexCornerMomentMethod<Int, Dub, T>::ConvexCornerMomentMethod(T& DataSt_) :D2Q9BC<Int, Dub, T>(DataSt_){
	this->schemeInx = 10002;

	std::cout << "ConvexCornerMomentMethod obj done" << std::endl;
}

template <typename Int, typename Dub, class T>
void ConvexCornerMomentMethod<Int, Dub, T>::scheme(RegProperties<Int, Dub, T> prop) {

	Dub rho = prop.PDFval[0] + 2 * (prop.PDFval[5] + prop.PDFval[7]) + 4 * prop.PDFval[6];

	prop.PDFval[1] = (2. / 3) * rho - prop.PDFval[0] - prop.PDFval[5];
	prop.PDFval[3] = (2. / 3) * rho - prop.PDFval[0] - prop.PDFval[7];
	prop.PDFval[8] = (1. / 6) * rho - prop.PDFval[7] - prop.PDFval[6];
	prop.PDFval[2] = -(2. / 3) * rho + prop.PDFval[0] + prop.PDFval[7] + prop.PDFval[5] + prop.PDFval[6];
	prop.PDFval[4] = (1. / 6) * rho - prop.PDFval[5] - prop.PDFval[6];

}










