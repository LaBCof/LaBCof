#include "Open.h"
template <typename int1, typename int2, typename Dub, class T>
Open<int1, int2, Dub, T>::Open() {

}

template <typename int1, typename int2, typename Dub, class T>
Open<int1, int2, Dub, T>::Open(T& DataSt_) :D2Q9BC<int1, int2, Dub, T>(DataSt_) {
	this->schemeInx = 7;

	std::cout <<"Open obj done" << std::endl;
}

template <typename int1, typename int2, typename Dub, class T>
void Open<int1, int2, Dub, T>::scheme(RegProperties<int1, int2, Dub, T> prop) {

	//Unknown boundary PDF index
	int1 iPDF = prop.PDFidx[3];

	//Find next PDF index
	int1 iNextPDF = this->DataSt.iNextPDF(iPDF);

	//Get PDF value from LBM
	int2 iNextNode = this->DataSt.iNodePDF(iNextPDF);

	//Get PDF value from LBM
	int2 pos = prop.pos;
	int1 iPDF2;
	int1 iPDF3;
	int1 iPDF4;
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


