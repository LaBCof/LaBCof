#include "ZouHeVelocity.h"

template <typename int1, typename int2, typename Dub, class T>
ZouHeVelocity<int1, int2, Dub, T>::ZouHeVelocity() {
}

template <typename int1, typename int2, typename Dub, class T>
ZouHeVelocity<int1, int2, Dub, T>::ZouHeVelocity(T& DataSt_):D2Q9BC<int1, int2, Dub, T>(DataSt_) {
	this->schemeInx = 4;

	std::cout  << "ZouHeVelocity obj done" << std::endl;
}

template <typename int1, typename int2, typename Dub, class T>
void ZouHeVelocity<int1, int2, Dub, T>::scheme(RegProperties<int1, int2, Dub, T> prop) {

	Dub u = prop.u;
	Dub v = prop.v;

	int2 pos = prop.pos;

	bool flip = false;
	int2 angle = 0;
	
	this->DataSt.specifyFlipRotation(pos, flip, angle);
	this->DataSt.vectorMapping(angle, flip, u, v);
	
	Dub rho = (prop.PDFval[0] + prop.PDFval[1] + prop.PDFval[5] + 2 * (prop.PDFval[6] + prop.PDFval[7] + prop.PDFval[8])) / (1 - u);

	prop.PDFval[3] = prop.PDFval[7] + (2. / 3)*rho*u;
	prop.PDFval[2] = prop.PDFval[6] + 0.5*(prop.PDFval[5] - prop.PDFval[1]) + 0.5*rho * v + (1. / 6)*rho*u;
	prop.PDFval[4] = prop.PDFval[8] - 0.5*(prop.PDFval[5] - prop.PDFval[1]) - 0.5*rho * v + (1. / 6)*rho*u;
	
	rho = prop.PDFval[0] + prop.PDFval[1] + prop.PDFval[2] + prop.PDFval[3] + prop.PDFval[4] + prop.PDFval[5] + prop.PDFval[6] + prop.PDFval[7] + prop.PDFval[8];
	u = prop.PDFval[2] + prop.PDFval[3] + prop.PDFval[4] - prop.PDFval[6] - prop.PDFval[7] - prop.PDFval[8];

}