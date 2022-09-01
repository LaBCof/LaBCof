#include "Periodic.h"

template <typename Int, typename Dub, class T>
Periodic<Int, Dub, T>::Periodic() {

}

template <typename Int, typename Dub, class T>
Periodic<Int, Dub, T>::Periodic(T& DataSt_) : D2Q9BC<Int, Dub>(DataSt_) {

	this->schemeInx = 5;

	nNodeReg = this->DataSt.nNodeReg;
	nBoundNode = this->DataSt.nBoundNode;
	
	Int reg1 = -1;
	Int reg2 = -1;

	findPeriodicRegions(reg1, reg2);

	if (reg1 != -1 && reg2 != -1) {
		findCorespondingNodes(reg1, reg2);
	}

	std::cout  << "Periodic obj done" << std::endl;
}

template <typename Int, typename Dub, class T>
void Periodic<Int, Dub, T>::findCorespondingNodes(Int reg1, Int reg2) {

	Int nPriodicNode = this->nNodeReg[reg1];

	Int n1_1 = 0;
	for (Int iReg = 0; iReg < reg1; iReg++) {
		n1_1 += this->nNodeReg[iReg];
	}
	Int n1_2 = n1_1 + this->nNodeReg[reg1];


	Int n2_1 = 0;
	for (Int iReg = 0; iReg < reg2; iReg++) {
		n2_1 += this->nNodeReg[iReg];
	}
	Int n2_2 = n2_1 + this->nNodeReg[reg2];


	corespondingNode = new Int[this->nBoundNode];

	Int cnt = 0;
	for (Int i = n1_1; i < n1_2; i++) {
		corespondingNode[i] = n2_1 + cnt;
		cnt++;
	}
	
	cnt = 0;
	for (Int i = n2_1; i < n2_2; i++) {
		corespondingNode[i] = n1_1 + cnt;
		cnt++;
	}

}

template <typename Int, typename Dub, class T>
void Periodic<Int, Dub, T>::findPeriodicRegions(Int& reg1, Int& reg2) {

	for (Int iReg = 0; iReg < this->nReg; iReg++) {
		Int BCindx = this->DataSt.BCidx[iReg];
		if (BCindx == this->schemeInx) {
			reg1 = iReg;
			break;
		}
	}

	for (Int iReg = 0; iReg < this->nReg; iReg++) {
		Int BCindx = this->DataSt.BCidx[iReg];

		if (BCindx == this->schemeInx && iReg != reg1) {
			reg2 = iReg;
			break;
		}
	}

}

template <typename Int, typename Dub, class T>
void Periodic<Int, Dub, T>::scheme(RegProperties<Int, Dub, T> prop) {
	
	ULLI iPDF = prop.PDFidx[0];
	
	Int pt = this->DataSt.iNodePDF(iPDF);
	
	Int pt1 = corespondingNode[pt];

	ULLI iPDF2 = pt1 * this->nVec + 6;
	ULLI iPDF3 = pt1 * this->nVec + 7;
	ULLI iPDF4 = pt1 * this->nVec + 8;

	prop.PDFval[2] = this->bcPDFv[iPDF2];
	prop.PDFval[3] = this->bcPDFv[iPDF3];
	prop.PDFval[4] = this->bcPDFv[iPDF4];

}

