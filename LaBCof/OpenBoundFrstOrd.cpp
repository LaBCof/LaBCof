#include "OpenBoundFrstOrd.h"
template <typename Int, typename Dub, class T>
OpenBoundFrstOrd<Int, Dub, T>::OpenBoundFrstOrd() {

}

template <typename Int, typename Dub, class T>
OpenBoundFrstOrd<Int, Dub, T>::OpenBoundFrstOrd(T& DataSt_) :D2Q9BC<Int, Dub, T>(DataSt_) {
	this->schemeInx = 7;

	std::cout <<"OpenBoundFrstOrd obj done" << std::endl;
}

template <typename Int, typename Dub, class T>
void OpenBoundFrstOrd<Int, Dub, T>::scheme(RegProperties<Int, Dub, T> prop) {

	//Unknown boundary PDF index
	ULLI iPDF = prop.PDFidx[3];

	//Find next PDF index
	ULLI iNextPDF = this->DataSt.iNextPDF(iPDF);

	//Get PDF value from LBM
	Int iNextNode = this->DataSt.iNodePDF(iNextPDF);

	//Get PDF value from LBM
	Int pos = prop.pos;
	ULLI iPDF2;
	ULLI iPDF3;
	ULLI iPDF4;
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








////void OpenBoundFrstOrd::scheme(RegProperties prop) {
////
////	Int iPDF;
////	Int iPDFnext;
////	Int iNode;
////	Int iBoundPDF;
////
////	//=================== Specify unknown f3 ===================
////	//Unknown boundary PDF index
////	Int iPDF3 = prop.PDFidx[3];
////
////	//Find next PDF index
////	iPDFnext = DataStruct.iNextPDF(iPDF3);
////
////	//Get PDF value from LBM
////	prop.PDFval[3] = DataStruct.get_PDFvFromLBM(iPDFnext);
////
////	//=================== Specify unknown f2 ===================
////	//find f5 PDF index
////	Int iPDF5 = prop.PDFidx[5];
////
////	//Find index of below node
////	iPDFnext = DataStruct.iNextPDF(iPDF5);
////	iNode = DataStruct.iNodePDF(iPDFnext);
////
////	//index of f2 PDF belong to iNode
////	iBoundPDF = bcPDFi[nVec * iNode + 2];
////
////	iPDF = DataStruct.iNextPDF(iBoundPDF);
////
////	prop.PDFval[2] = DataStruct.get_PDFvFromLBM(iPDF);
////
////	//=================== Specify unknown f4 ===================
////	//find f1 PDF index
////	Int iPDF1 = prop.PDFidx[1];
////
////	//Find index of the above node
////	iPDF = DataStruct.iNextPDF(iPDF1);
////	iNode = DataStruct.iNodePDF(iPDF);
////
////	//index of f4 PDF belong to iNode
////	iBoundPDF = bcPDFi[nVec * iNode + 4];
////
////	iPDF = DataStruct.iNextPDF(iBoundPDF);
////
////	prop.PDFval[4] = DataStruct.get_PDFvFromLBM(iPDF);
////
////}


//
//void OpenBoundFrstOrd::scheme(RegProperties prop) {
//
//	////std::cout  << "============================" << std::endl;
//	Int iPDF;
//	Int iPDFnext;
//	Int iNode;
//	Int iBoundPDF;
//
//	//=================== Specify unknown f3 ===================
//	//Unknown boundary PDF index
//	Int iPDF3 = prop.PDFidx[3];
//
//	//Find next PDF index
//	iPDFnext = DataStruct.iNextPDF(iPDF3);
//
//	iNode = DataStruct.iNodePDF(iPDFnext);
//
//	Dub u = DataStruct.get_xVelFromLBM(iNode);
//	Dub v = DataStruct.get_yVelFromLBM(iNode);
//
//
//	Int pos = prop.pos;
//
//	bool flip = false;
//	Int angle = 0;
//
//	DataStruct.specifyFlipRotation(pos, flip, angle);
//	DataStruct.vectorMapping(angle, flip, u, v);
//
//
//	////std::cout  << "ZH u " << u << "ZH v " << v << std::endl;
//	Dub rho = (prop.PDFval[0] + prop.PDFval[1] + prop.PDFval[5] + 2 * (prop.PDFval[6] + prop.PDFval[7] + prop.PDFval[8])) / (1 - u);
//
//	prop.PDFval[3] = prop.PDFval[7] + (2. / 3) * rho * u;
//	prop.PDFval[2] = prop.PDFval[6] + 0.5 * (prop.PDFval[5] - prop.PDFval[1]) + 0.5 * rho * v + (1. / 6) * rho * u;
//	prop.PDFval[4] = prop.PDFval[8] - 0.5 * (prop.PDFval[5] - prop.PDFval[1]) - 0.5 * rho * v + (1. / 6) * rho * u;
//
//
//
//
//}
