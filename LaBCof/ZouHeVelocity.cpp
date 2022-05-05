#include "ZouHeVelocity.h"

template <typename Int, typename Dub>
ZouHeVelocity<Int, Dub>::ZouHeVelocity() {
}

template <typename Int, typename Dub>
ZouHeVelocity<Int, Dub>::ZouHeVelocity(DataStBCIndirect<Int, Dub>& DataSt_):D2Q9BC<Int, Dub>(DataSt_) {
	this->schemeInx = 4;

	std::cout  << "ZouHeVelocity obj done" << std::endl;
}

template <typename Int, typename Dub>
void ZouHeVelocity<Int, Dub>::scheme(RegProperties<Int, Dub> prop) {

	Dub u = prop.u;
	Dub v = prop.v;

	Int pos = prop.pos;

	bool flip = false;
	Int angle = 0;
	
	this->DataSt.specifyFlipRotation(pos, flip, angle);
	this->DataSt.vectorMapping(angle, flip, u, v);
	
	Dub rho = (prop.PDFval[0] + prop.PDFval[1] + prop.PDFval[5] + 2 * (prop.PDFval[6] + prop.PDFval[7] + prop.PDFval[8])) / (1 - u);

	prop.PDFval[3] = prop.PDFval[7] + (2. / 3)*rho*u;
	prop.PDFval[2] = prop.PDFval[6] + 0.5*(prop.PDFval[5] - prop.PDFval[1]) + 0.5*rho * v + (1. / 6)*rho*u;
	prop.PDFval[4] = prop.PDFval[8] - 0.5*(prop.PDFval[5] - prop.PDFval[1]) - 0.5*rho * v + (1. / 6)*rho*u;
	
	rho = prop.PDFval[0] + prop.PDFval[1] + prop.PDFval[2] + prop.PDFval[3] + prop.PDFval[4] + prop.PDFval[5] + prop.PDFval[6] + prop.PDFval[7] + prop.PDFval[8];
	u = prop.PDFval[2] + prop.PDFval[3] + prop.PDFval[4] - prop.PDFval[6] - prop.PDFval[7] - prop.PDFval[8];

}