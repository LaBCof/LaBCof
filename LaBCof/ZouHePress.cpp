#include "ZouHePress.h"

template <typename Int, typename Dub>
ZouHePress<Int, Dub>::ZouHePress() {
}

template <typename Int, typename Dub>
ZouHePress<Int, Dub>::ZouHePress(DataStBCIndirect<Int, Dub>& DataSt_) :D2Q9BC<Int, Dub>(DataSt_) {
	this->schemeInx = 3;

	std::cout  << "ZouHePress obj done" << std::endl;
}

template <typename Int, typename Dub>
void ZouHePress<Int, Dub>::scheme(RegProperties<Int, Dub> prop) {

	Dub u = 1.0 - (prop.PDFval[0] + prop.PDFval[1] + prop.PDFval[5] + 2 * (prop.PDFval[6] + prop.PDFval[7] + prop.PDFval[8])) / prop.rho;

	prop.PDFval[3] = prop.PDFval[7] + (2. / 3)*prop.rho*u;
	prop.PDFval[2] = prop.PDFval[6] + 0.5*(prop.PDFval[5] - prop.PDFval[1]) + (1. / 6)*prop.rho*u;
	prop.PDFval[4] = prop.PDFval[8] - 0.5*(prop.PDFval[5] - prop.PDFval[1]) + (1. / 6)*prop.rho*u;

}
