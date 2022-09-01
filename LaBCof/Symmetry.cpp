#include "Symmetry.h"
template <typename int1, typename int2, typename Dub, class T>
Symmetry<int1, int2, Dub, T>::Symmetry() {

}

template <typename int1, typename int2, typename Dub, class T>
Symmetry<int1, int2, Dub, T>::Symmetry(T& DataSt_) : D2Q9BC<int1, int2, Dub, T>(DataSt_) {
	this->schemeInx = 6;

	std::cout << "Symmetry obj done" << std::endl;
}

template <typename int1, typename int2, typename Dub, class T>
void Symmetry<int1, int2, Dub, T>::scheme(RegProperties<int1, int2, Dub, T> prop) {

	prop.PDFval[2] = prop.PDFval[8];
	prop.PDFval[3] = prop.PDFval[7];
	prop.PDFval[4] = prop.PDFval[6];

}
