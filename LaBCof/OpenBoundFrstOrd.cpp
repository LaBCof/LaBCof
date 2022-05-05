#include "OpenBoundFrstOrd.h"
template <typename Int, typename Dub>
OpenBoundFrstOrd<Int, Dub>::OpenBoundFrstOrd() {

}

template <typename Int, typename Dub>
OpenBoundFrstOrd<Int, Dub>::OpenBoundFrstOrd(DataStBCIndirect<Int, Dub>& DataSt_) :D2Q9BC<Int, Dub>(DataSt_) {
	this->schemeInx = 7;

	std::cout <<"OpenBoundFrstOrd obj done" << std::endl;
}

template <typename Int, typename Dub>
void OpenBoundFrstOrd<Int, Dub>::scheme(RegProperties<Int, Dub> prop) {

	//Unknown boundary PDF index
	Int iPDF = prop.PDFidx[3];

	//Find next PDF index
	Int iNextPDF = this->DataSt.iNextPDF(iPDF);

	//Get PDF value from LBM
	Int iNextNode = this->DataSt.iNodePDF(iNextPDF);

	//Get PDF value from LBM
	Int pos = prop.pos;
	Int iPDF2;
	Int iPDF3;
	Int iPDF4;
	if (pos==2) {
		iPDF2 = this->DataSt.iPDFNode(iNextNode, 2);
		iPDF3 = this->DataSt.iPDFNode(iNextNode, 3);
		iPDF4 = this->DataSt.iPDFNode(iNextNode, 4);
	}
	else if (pos == 1) {
		iPDF2 = this->DataSt.iPDFNode(iNextNode, 4);
		iPDF3 = this->DataSt.iPDFNode(iNextNode, 5);
		iPDF4 = this->DataSt.iPDFNode(iNextNode, 6);
	}
	else if (pos == 3) {
		iPDF2 = this->DataSt.iPDFNode(iNextNode, 6);
		iPDF3 = this->DataSt.iPDFNode(iNextNode, 7);
		iPDF4 = this->DataSt.iPDFNode(iNextNode, 8);
	}
	else if (pos == 0) {
		iPDF2 = this->DataSt.iPDFNode(iNextNode, 8);
		iPDF3 = this->DataSt.iPDFNode(iNextNode, 1);
		iPDF4 = this->DataSt.iPDFNode(iNextNode, 2);
	}

	//find f5 PDF index
	prop.PDFval[2] = this->DataSt.get_PDFvFromLBM(iPDF2);
	prop.PDFval[3] = this->DataSt.get_PDFvFromLBM(iPDF3);
	prop.PDFval[4] = this->DataSt.get_PDFvFromLBM(iPDF4);

}
