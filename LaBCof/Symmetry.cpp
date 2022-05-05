#include "Symmetry.h"
template <typename Int, typename Dub>
Symmetry<Int, Dub>::Symmetry() {

}

template <typename Int, typename Dub>
Symmetry<Int, Dub>::Symmetry(DataStBCIndirect<Int, Dub>& DataSt_) : D2Q9BC<Int, Dub>(DataSt_) {
	this->schemeInx = 6;

	std::cout << "Symmetry obj done" << std::endl;
}

template <typename Int, typename Dub>
void Symmetry<Int, Dub>::scheme(RegProperties<Int, Dub> prop) {

	prop.PDFval[2] = prop.PDFval[8];
	prop.PDFval[3] = prop.PDFval[7];
	prop.PDFval[4] = prop.PDFval[6];

}
