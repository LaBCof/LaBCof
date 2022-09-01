#include "Periodic.h"

template <typename int1, typename int2, typename Dub, class T>
Periodic<int1, int2, Dub, T>::Periodic() {

}

template <typename int1, typename int2, typename Dub, class T>
Periodic<int1, int2, Dub, T>::Periodic(T& DataSt_) : D2Q9BC<int2, Dub>(DataSt_) {

	this->schemeInx = 5;

	nNodeReg = this->DataSt.nNodeReg;
	nBoundNode = this->DataSt.nBoundNode;
	
	int2 reg1 = -1;
	int2 reg2 = -1;

	findPeriodicRegions(reg1, reg2);

	if (reg1 != -1 && reg2 != -1) {
		findCorespondingNodes(reg1, reg2);
	}

	std::cout  << "Periodic obj done" << std::endl;
}

template <typename int1, typename int2, typename Dub, class T>
void Periodic<int1, int2, Dub, T>::findCorespondingNodes(int2 reg1, int2 reg2) {

	int2 nPriodicNode = this->nNodeReg[reg1];

	int2 n1_1 = 0;
	for (int2 iReg = 0; iReg < reg1; iReg++) {
		n1_1 += this->nNodeReg[iReg];
	}
	int2 n1_2 = n1_1 + this->nNodeReg[reg1];


	int2 n2_1 = 0;
	for (int2 iReg = 0; iReg < reg2; iReg++) {
		n2_1 += this->nNodeReg[iReg];
	}
	int2 n2_2 = n2_1 + this->nNodeReg[reg2];


	corespondingNode = new int2[this->nBoundNode];

	int2 cnt = 0;
	for (int2 i = n1_1; i < n1_2; i++) {
		corespondingNode[i] = n2_1 + cnt;
		cnt++;
	}
	
	cnt = 0;
	for (int2 i = n2_1; i < n2_2; i++) {
		corespondingNode[i] = n1_1 + cnt;
		cnt++;
	}

}

template <typename int1, typename int2, typename Dub, class T>
void Periodic<int1, int2, Dub, T>::findPeriodicRegions(int2& reg1, int2& reg2) {

	for (int2 iReg = 0; iReg < this->nReg; iReg++) {
		int2 BCindx = this->DataSt.BCidx[iReg];
		if (BCindx == this->schemeInx) {
			reg1 = iReg;
			break;
		}
	}

	for (int2 iReg = 0; iReg < this->nReg; iReg++) {
		int2 BCindx = this->DataSt.BCidx[iReg];

		if (BCindx == this->schemeInx && iReg != reg1) {
			reg2 = iReg;
			break;
		}
	}

}

template <typename int1, typename int2, typename Dub, class T>
void Periodic<int1, int2, Dub, T>::scheme(RegProperties<int1, int2, Dub, T> prop) {
	
	int1 iPDF = prop.PDFidx[0];
	
	int2 pt = this->DataSt.iNodePDF(iPDF);
	
	int2 pt1 = corespondingNode[pt];

	int1 iPDF2 = pt1 * this->nVec + 6;
	int1 iPDF3 = pt1 * this->nVec + 7;
	int1 iPDF4 = pt1 * this->nVec + 8;

	prop.PDFval[2] = this->bcPDFv[iPDF2];
	prop.PDFval[3] = this->bcPDFv[iPDF3];
	prop.PDFval[4] = this->bcPDFv[iPDF4];

}

