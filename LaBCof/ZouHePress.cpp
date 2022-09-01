#include "ZouHePress.h"

template <typename int1, typename int2, typename Dub, class T>
ZouHePress<int1, int2, Dub, T>::ZouHePress() {
}

template <typename int1, typename int2, typename Dub, class T>
ZouHePress<int1, int2, Dub, T>::ZouHePress(T& DataSt_) :D2Q9BC<int1, int2, Dub, T>(DataSt_) {
	this->schemeInx = 3;

	std::cout  << "ZouHePress obj done" << std::endl;
}

template <typename int1, typename int2, typename Dub, class T>
void ZouHePress<int1, int2, Dub, T>::scheme(RegProperties<int1, int2, Dub, T> prop) {

	Dub u = 1.0 - (prop.PDFval[0] + prop.PDFval[1] + prop.PDFval[5] + 2 * (prop.PDFval[6] + prop.PDFval[7] + prop.PDFval[8])) / prop.rho;

	prop.PDFval[3] = prop.PDFval[7] + (2. / 3)*prop.rho*u;
	prop.PDFval[2] = prop.PDFval[6] + 0.5*(prop.PDFval[5] - prop.PDFval[1]) + (1. / 6)*prop.rho*u;
	prop.PDFval[4] = prop.PDFval[8] - 0.5*(prop.PDFval[5] - prop.PDFval[1]) + (1. / 6)*prop.rho*u;

}
