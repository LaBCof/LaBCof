#include "Symmetry.h"
template <typename Int, typename Dub, class T>
Symmetry<Int, Dub, T>::Symmetry() {

}

template <typename Int, typename Dub, class T>
Symmetry<Int, Dub, T>::Symmetry(T& DataSt_) : D2Q9BC<Int, Dub, T>(DataSt_) {
	this->schemeInx = 6;

	std::cout << "Symmetry obj done" << std::endl;
}

template <typename Int, typename Dub, class T>
void Symmetry<Int, Dub, T>::scheme(RegProperties<Int, Dub, T> prop) {

	prop.PDFval[2] = prop.PDFval[8];
	prop.PDFval[3] = prop.PDFval[7];
	prop.PDFval[4] = prop.PDFval[6];

}
