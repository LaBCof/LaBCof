#include "DataStBC.h"

template <typename int1, typename int2, typename Dub, class T>
DataStBC<int1, int2, Dub, T>::DataStBC() {

}

template <typename int1, typename int2, typename Dub, class T>
void DataStBC<int1, int2, Dub, T>::DataStPreProc(){

	set_nReg();

	set_nNode();

	set_nPDF();

	set_nBoundNode();

	set_iBondNode();

	set_nFluidNode();

	set_nNodeReg();

	set_nVec();

	set_Cx();

	set_Cy();

	set_BCidx();

	set_rho();

	set_xVel();

	set_yVel();

	set_bcPDFi();

	//std::cout << nBoundNode << " set_bcPDFi " /*<< i*/ << std::endl;

	set_orient();

	//std::cout << nBoundNode << " set_orient " /*<< i*/ << std::endl;

	this->bcPDFmapping();

	this->bcPDFv = new double[this->nVec * this->nBoundNode];
	get_bcPDFvFromLBM();

}

template <typename int1, typename int2, typename Dub, class T>
void DataStBC<int1, int2, Dub, T>::bcPDFmapping()
{

	int1* PDFidx = new int1[nVec];

	bool flip = false;
	int2 angle = 0;
	int2 pos = -1;

	for (int2 i = 0; i < nBoundNode; i++) {

		pos = orient[i];

		specifyFlipRotation(pos, flip, angle);

		//std::cout << pos << " 70 specifyFlipRotation "<< angle << std::endl;

		for (int2 j = 0; j < nVec; j++) {
			PDFidx[j] = bcPDFi[nVec * i + j];
			//std::cout << j << " PDFidx " << PDFidx[j] << std::endl;

		}

		stencilMapping(angle, flip, PDFidx);

		for (int2 j = 0; j < nVec; j++) {
			bcPDFi[i * nVec + j] = PDFidx[j];
		}

	}

}

template <typename int1, typename int2, typename Dub, class T>
void DataStBC<int1, int2, Dub, T>::stencilMapping(int2 angle, bool flip, int1* PDFidx) {

	int2 nVec = 9;
	int1 tmpPDFidx[9];
	int2 shift = angle / 45;

	for (int2 i = 1; i < nVec; i++) {
		int2 j = i - shift;
		//std::cout << j << " tmpPDFidx " << tmpPDFidx[j] << std::endl;
		if (j > nVec - 1) j = j - (nVec - 1);
		if (j < 1) j = j + (nVec - 1);
		tmpPDFidx[j] = PDFidx[i];
	}

	for (int2 i = 1; i < nVec; i++) {
		PDFidx[i] = tmpPDFidx[i];
	}


	if (flip == true) {
		int1 tmp;

		tmp = PDFidx[1];
		PDFidx[1] = PDFidx[5];
		PDFidx[5] = tmp;

		tmp = PDFidx[2];
		PDFidx[2] = PDFidx[4];
		PDFidx[4] = tmp;

		tmp = PDFidx[8];
		PDFidx[8] = PDFidx[6];
		PDFidx[6] = tmp;
	}

}

template <typename int1, typename int2, typename Dub, class T>
void DataStBC<int1, int2, Dub, T>::specifyFlipRotation(int2 pos, bool& flip, int2& angle) {

	if (pos == 0) {
		angle = -90;
		flip = false;
	}
	else if (pos == 1) {
		angle = 90;
		flip = false;
	}
	else if (pos == 2) {
		angle = 0;
		flip = false;
	}
	else if (pos == 3) {
		angle = 180;
		flip = false;
	}
	else if (pos == 4) {
		angle = 0;
		flip = false;
	}
	else if (pos == 5) {
		angle = 180;
		flip = true;
	}
	else if (pos == 6) {
		angle = 0;
		flip = true;
	}
	else if (pos == 7) {
		angle = 180;
		flip = false;
	}
	else if (pos == 8) {
		angle = 0;
		flip = false;
	}
	else if (pos == 9) {
		angle = 180;
		flip = true;
	}
	else if (pos == 10) {
		angle = 0;
		flip = true;
	}
	else if (pos == 11) {
		angle = 180;
		flip = false;
	}

}

template <typename int1, typename int2, typename Dub, class T>
void DataStBC<int1, int2, Dub, T>::vectorMapping(int2 angle_, bool flip, Dub& U, Dub& V) {
	Dub pi = 4 * atan(1.0);
	Dub angle = angle_ * pi / 180;

	Dub u = U * cos(angle) - V * sin(angle);
	Dub v = U * sin(angle) + V * cos(angle);

	if (flip == true) v = -v;

	U = u;
	V = v;
}





















//void DataStBC::fIntdBoundNodeOrient()
//{
//
//	int2 pos;
//	int2* PDFidx = new int2[nVec];
//
//	for (int2 i = 0; i < nBoundNode; i++) {
//
//		for (int2 j = 0; j < nVec; j++) {
//			PDFidx[j] = bcPDFi[nVec * i + j];
//		}
//
//		pos = nodeOrient(PDFidx);
//		orient[i] = pos;
//		////std::cout  << i << "  --- " << pos << std::endl;
//	}
//
//
//
//	////int2 sum;
//	////int2 nNodeRegion;
//
//	////sum = 0;
//	////for (int2 iReg = 0; iReg < nReg; iReg++) {
//
//	////	nNodeRegion = nNodeReg[iReg];
//	////	if (BCidx[iReg] > 0) {
//
//	////		for (int2 i = sum; i < sum + nNodeRegion; i++) {
//
//	////			//orient[i] = settIntg.pos;
//	////		}
//	////	}
//	////label:	sum += nNodeRegion;
//	////}
//
//
//
//}


//
//int2 DataStBC::nodeOrient(int2*& PDFidx) {
//	int2 pos = -1;
//	int2 iPDF;
//
//	iPDF = IntextPDF(PDFidx[1]);    int2 p1 = IntodePDF(iPDF);
//	iPDF = IntextPDF(PDFidx[2]);    int2 p2 = IntodePDF(iPDF);
//	iPDF = IntextPDF(PDFidx[3]);    int2 p3 = IntodePDF(iPDF);
//	iPDF = IntextPDF(PDFidx[4]);    int2 p4 = IntodePDF(iPDF);
//	iPDF = IntextPDF(PDFidx[5]);    int2 p5 = IntodePDF(iPDF);
//	iPDF = IntextPDF(PDFidx[6]);    int2 p6 = IntodePDF(iPDF);
//	iPDF = IntextPDF(PDFidx[7]);    int2 p7 = IntodePDF(iPDF);
//	iPDF = IntextPDF(PDFidx[8]);    int2 p8 = IntodePDF(iPDF);
//
//	if (!isFluid(p3) && !isFluid(p7) && isFluid(p1)) return pos = 0;
//	if (!isFluid(p3) && !isFluid(p7) && isFluid(p5)) return pos = 1;
//	if (!isFluid(p1) && !isFluid(p5) && isFluid(p3)) return pos = 2;
//	if (!isFluid(p1) && !isFluid(p5) && isFluid(p7)) return pos = 3;
//
//	if (!isFluid(p1) && !isFluid(p3) && isFluid(p2)) return pos = 4;
//	if (!isFluid(p1) && !isFluid(p7) && isFluid(p8)) return pos = 5;
//	if (!isFluid(p3) && !isFluid(p5) && isFluid(p4)) return pos = 6;
//	if (!isFluid(p5) && !isFluid(p7) && isFluid(p6)) return pos = 7;
//
//	if (!isFluid(p1) && !isFluid(p3) && isFluid(p6)) return pos = 8;
//	if (!isFluid(p1) && !isFluid(p7) && isFluid(p4)) return pos = 9;
//	if (!isFluid(p3) && !isFluid(p5) && isFluid(p8)) return pos = 10;
//	if (!isFluid(p5) && !isFluid(p7) && isFluid(p2)) return pos = 11;
//
//	return pos = 100;
//}
