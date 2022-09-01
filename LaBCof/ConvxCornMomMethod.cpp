#include "ConvxCornMomMethod.h"

template <typename int1, typename int2, typename Dub, class T>
ConvxCornMomMethod<int1, int2, Dub, T>::ConvxCornMomMethod(){

}
template <typename int1, typename int2, typename Dub, class T>
ConvxCornMomMethod<int1, int2, Dub, T>::ConvxCornMomMethod(T& DataSt_) :D2Q9BC<int1, int2, Dub, T>(DataSt_){
	this->schemeInx = 10002;

	std::cout << "ConvxCornMomMethod obj done" << std::endl;
}

template <typename int1, typename int2, typename Dub, class T>
void ConvxCornMomMethod<int1, int2, Dub, T>::scheme(RegProperties<int1, int2, Dub, T> prop) {

	Dub rho = prop.PDFval[0] + 2 * (prop.PDFval[5] + prop.PDFval[7]) + 4 * prop.PDFval[6];

	prop.PDFval[1] = (2. / 3) * rho - prop.PDFval[0] - prop.PDFval[5];
	prop.PDFval[3] = (2. / 3) * rho - prop.PDFval[0] - prop.PDFval[7];
	prop.PDFval[8] = (1. / 6) * rho - prop.PDFval[7] - prop.PDFval[6];
	prop.PDFval[2] = -(2. / 3) * rho + prop.PDFval[0] + prop.PDFval[7] + prop.PDFval[5] + prop.PDFval[6];
	prop.PDFval[4] = (1. / 6) * rho - prop.PDFval[5] - prop.PDFval[6];

}










