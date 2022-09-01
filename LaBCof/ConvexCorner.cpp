#include "ConvexCorner.h"

template <typename int1, typename int2, typename Dub, class T>
ConvexCorner<int1, int2, Dub, T>::ConvexCorner(){

}

template <typename int1, typename int2, typename Dub, class T>
ConvexCorner<int1, int2, Dub, T>::ConvexCorner(T& DataSt_) :D2Q9BC<int1, int2, Dub, T>(DataSt_)
{
	this->schemeInx = 10000;

	std::cout << "ConvexCorner obj done." << std::endl;
}


template <typename int1, typename int2, typename Dub, class T>
int2 ConvexCorner<int1, int2, Dub, T>::findNodeForExtrapolate(RegProperties<int1, int2, Dub, T> prop) {

	int1 iPDF = this->DataSt.iNextPDF(prop.PDFidx[3]);

	int2 iNode = this->DataSt.iNodePDF(iPDF);

	return iNode;
}


template <typename int1, typename int2, typename Dub, class T>
void ConvexCorner<int1, int2, Dub, T>::scheme(RegProperties<int1, int2, Dub, T> prop) {
	Dub rho = prop.rho;
	Dub u = prop.u;
	Dub v = prop.v;

	int2 iNodeForExtrapolate = findNodeForExtrapolate(prop);

	if (rho == 10000) rho = this->DataSt.get_densityFromLBM(iNodeForExtrapolate);
	if (abs(u) == 10000) u = this->DataSt.get_xVelFromLBM(iNodeForExtrapolate);
	if (abs(v) == 10000) v = this->DataSt.get_yVelFromLBM(iNodeForExtrapolate);

	int2 pos = prop.pos;

	bool flip = false;
	int2 angle = 0;

	this->DataSt.specifyFlipRotation(pos, flip, angle);
	this->DataSt.vectorMapping(angle, flip, u, v);

	prop.PDFval[1] = prop.PDFval[5] + (2. / 3) * rho * v;
	prop.PDFval[3] = prop.PDFval[7] + (2. / 3) * rho * u;
	prop.PDFval[2] = prop.PDFval[6] + (1. / 6) * rho * (u + v);
	prop.PDFval[8] = -0.5 * (rho * (u - 1.0) + prop.PDFval[0] + prop.PDFval[1] + prop.PDFval[5] + 2 * prop.PDFval[6] + 2 * prop.PDFval[7]);
	prop.PDFval[4] = rho * u - prop.PDFval[2] - prop.PDFval[3] + prop.PDFval[6] + prop.PDFval[7] + prop.PDFval[8];

}
