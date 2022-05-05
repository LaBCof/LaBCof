#include "Momentmethod.h"
template <typename Int, typename Dub>
Momentmethod<Int, Dub>::Momentmethod() {

}
template <typename Int, typename Dub>
Momentmethod<Int, Dub>::Momentmethod(DataStBCIndirect<Int, Dub>& DataSt_) :D2Q9BC<Int, Dub>(DataSt_) {
	this->schemeInx = 12;

	std::cout << "MomentMethod obj done" << std::endl;

}

template <typename Int, typename Dub>
void Momentmethod<Int, Dub>::scheme(RegProperties<Int, Dub> prop) {

	Dub rho = prop.PDFval[0] + prop.PDFval[1] + prop.PDFval[5] + 2 * (prop.PDFval[6] + prop.PDFval[7] + prop.PDFval[8]);

	prop.PDFval[3] = prop.PDFval[5] + prop.PDFval[1] + prop.PDFval[7] + 2*(prop.PDFval[6] + prop.PDFval[8]) - rho / 3;
	prop.PDFval[4] = rho / 6 - prop.PDFval[5] - prop.PDFval[6];
	prop.PDFval[2] = rho / 6 - prop.PDFval[1] - prop.PDFval[8];

}