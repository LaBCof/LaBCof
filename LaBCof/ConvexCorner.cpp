#include "ConvexCorner.h"

template <typename Int, typename Dub>
ConvexCorner<Int, Dub>::ConvexCorner(){

}

template <typename Int, typename Dub>
ConvexCorner<Int, Dub>::ConvexCorner(DataStBCIndirect<Int, Dub>& DataSt_) :D2Q9BC<Int, Dub>(DataSt_)
{
	this->schemeInx = 10000;

	std::cout << "ConvexCorner obj done." << std::endl;
}


template <typename Int, typename Dub>
Int ConvexCorner<Int, Dub>::findNodeForExtrapolate(RegProperties<Int, Dub> prop) {

	Int iPDF = this->DataSt.iNextPDF(prop.PDFidx[2]);

	Int iNode = this->DataSt.iNodePDF(iPDF);

	return iNode;
}


template <typename Int, typename Dub>
void ConvexCorner<Int, Dub>::scheme(RegProperties<Int, Dub> prop) {
	Dub rho = prop.rho;
	Dub u = prop.u;
	Dub v = prop.v;

	Int iNodeForExtrapolate = findNodeForExtrapolate(prop);

	if (rho == 10000) rho = this->DataSt.get_densityFromLBM(iNodeForExtrapolate);
	if (abs(u) == 10000) u = this->DataSt.get_xVelFromLBM(iNodeForExtrapolate);
	if (abs(v) == 10000) v = this->DataSt.get_yVelFromLBM(iNodeForExtrapolate);

	Int pos = prop.pos;

	bool flip = false;
	Int angle = 0;

	this->DataSt.specifyFlipRotation(pos, flip, angle);
	this->DataSt.vectorMapping(angle, flip, u, v);

	prop.PDFval[1] = prop.PDFval[5] + (2. / 3) * rho * v;
	prop.PDFval[3] = prop.PDFval[7] + (2. / 3) * rho * u;
	prop.PDFval[2] = prop.PDFval[6] + (1. / 6) * rho * (u + v);
	prop.PDFval[8] = -0.5 * (rho * (u - 1.0) + prop.PDFval[0] + prop.PDFval[1] + prop.PDFval[5] + 2 * prop.PDFval[6] + 2 * prop.PDFval[7]);
	prop.PDFval[4] = rho * u - prop.PDFval[2] - prop.PDFval[3] + prop.PDFval[6] + prop.PDFval[7] + prop.PDFval[8];

}




