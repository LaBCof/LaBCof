#include "D2Q9BC.h"

template <typename Int, typename Dub>
D2Q9BC<Int, Dub>::D2Q9BC()
{
}


template <typename Int, typename Dub>
D2Q9BC<Int, Dub>::~D2Q9BC()
{
}


template <typename Int, typename Dub>
D2Q9BC<Int, Dub>::D2Q9BC(DataStBCIndirect<Int, Dub>&DataSt_)
{

	DataSt = DataSt_;

	nReg = DataSt.nReg;
	nNodeReg = DataSt.nNodeReg;
	nBoundNode = DataSt.nBoundNode;

	bcPDFi = DataSt.bcPDFi;
	bcPDFv = DataSt.bcPDFv;
	orient = DataSt.orient;

	BCidx = DataSt.BCidx;
	rho = DataSt.rho;
	xVel = DataSt.xVel;
	yVel = DataSt.yVel;

	nVec = 9;

	regPropContaInter.PDFidx = new Int[nVec];
	regPropContaInter.PDFval = new Dub[nVec];

}


template <typename Int, typename Dub>
void D2Q9BC<Int, Dub>::execut() {

	Int sum = 0;
	for (Int iReg = 0; iReg < nReg; iReg++) {

		Int nNodeRegion = nNodeReg[iReg];
		if (BCidx[iReg] != schemeInx) goto label;

		regPropContaInter.rho = rho[iReg];
		regPropContaInter.u = xVel[iReg];
		regPropContaInter.v = yVel[iReg];

		for (Int i = sum; i < sum + nNodeRegion; i++) {

			Int Intode = DataSt.iBondNode[i];

			for (Int j = 0; j < nVec; j++) {
				Int idx = nVec * Intode + j;
				regPropContaInter.PDFidx[j] = bcPDFi[idx];
				regPropContaInter.PDFval[j] = bcPDFv[idx];
			}

			regPropContaInter.pos = orient[i];

			scheme(regPropContaInter);

			for (Int j = 0; j < nVec; j++) {
				Int idx = nVec * Intode + j;
				bcPDFv[idx] = regPropContaInter.PDFval[j];
			}
		
		}
		
	label:	sum += nNodeRegion;
	}

}



