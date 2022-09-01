#include "D2Q9BC.h"

template <typename int1, typename int2, typename Dub, class T>
D2Q9BC<int1, int2, Dub, T>::D2Q9BC()
{
}


template <typename int1, typename int2, typename Dub, class T>
D2Q9BC<int1, int2, Dub, T>::~D2Q9BC()
{
}


template <typename int1, typename int2, typename Dub, class T>
D2Q9BC<int1, int2, Dub, T>::D2Q9BC(T&DataSt_)
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

	regPropContaInter.PDFidx = new int1[nVec];
	regPropContaInter.PDFval = new Dub[nVec];

}


template <typename int1, typename int2, typename Dub, class T>
void D2Q9BC<int1, int2, Dub, T>::execut() {

	int2 sum = 0;
	for (int2 iReg = 0; iReg < nReg; iReg++) {

		int2 nNodeRegion = nNodeReg[iReg];
		if (BCidx[iReg] != schemeInx) goto label;

		regPropContaInter.rho = rho[iReg];
		regPropContaInter.u = xVel[iReg];
		regPropContaInter.v = yVel[iReg];

		for (int2 i = sum; i < sum + nNodeRegion; i++) {

			int2 Intode = DataSt.iBondNode[i];

			for (int2 j = 0; j < nVec; j++) {
				int2 idx = nVec * Intode + j;
				regPropContaInter.PDFidx[j] = bcPDFi[idx];
				regPropContaInter.PDFval[j] = bcPDFv[idx];
			}

			regPropContaInter.pos = orient[i];

			scheme(regPropContaInter);

			for (int2 j = 0; j < nVec; j++) {
				int2 idx = nVec * Intode + j;
				bcPDFv[idx] = regPropContaInter.PDFval[j];
			}
		
		}
		
	label:	sum += nNodeRegion;
	}

}



