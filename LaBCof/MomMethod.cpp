#include "MomMethod.h"
template <typename int1, typename int2, typename Dub, class T>
MomMethod<int1, int2, Dub, T>::MomMethod() {

}
template <typename int1, typename int2, typename Dub, class T>
MomMethod<int1, int2, Dub, T>::MomMethod(T& DataSt_) :D2Q9BC<int1, int2, Dub, T>(DataSt_) {
	this->schemeInx = 12;

	std::cout << "MomentMethod obj done" << std::endl;

}

template <typename int1, typename int2, typename Dub, class T>
void MomMethod<int1, int2, Dub, T>::scheme(RegProperties<int1, int2, Dub, T> prop) {

	Dub rho = prop.PDFval[0] + prop.PDFval[1] + prop.PDFval[5] + 2 * (prop.PDFval[6] + prop.PDFval[7] + prop.PDFval[8]);

	prop.PDFval[3] = prop.PDFval[5] + prop.PDFval[1] + prop.PDFval[7] + 2*(prop.PDFval[6] + prop.PDFval[8]) - rho / 3;
	prop.PDFval[4] = rho / 6 - prop.PDFval[5] - prop.PDFval[6];
	prop.PDFval[2] = rho / 6 - prop.PDFval[1] - prop.PDFval[8];

}