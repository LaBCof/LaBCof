#include "DataStBC.h"

template <typename Int, typename Dub, class T>
DataStBC<Int, Dub, T>::DataStBC() {

}

template <typename Int, typename Dub, class T>
void DataStBC<Int, Dub, T>::DataStPreProc(){

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

template <typename Int, typename Dub, class T>
void DataStBC<Int, Dub, T>::bcPDFmapping()
{

	ULLI* PDFidx = new ULLI[nVec];

	bool flip = false;
	Int angle = 0;
	Int pos = -1;

	for (Int i = 0; i < nBoundNode; i++) {

		pos = orient[i];

		specifyFlipRotation(pos, flip, angle);

		//std::cout << pos << " 70 specifyFlipRotation "<< angle << std::endl;

		for (Int j = 0; j < nVec; j++) {
			PDFidx[j] = bcPDFi[nVec * i + j];
			//std::cout << j << " PDFidx " << PDFidx[j] << std::endl;

		}

		stencilMapping(angle, flip, PDFidx);

		for (Int j = 0; j < nVec; j++) {
			bcPDFi[i * nVec + j] = PDFidx[j];
		}

	}

}

template <typename Int, typename Dub, class T>
void DataStBC<Int, Dub, T>::stencilMapping(Int angle, bool flip, ULLI* PDFidx) {

	Int nVec = 9;
	ULLI tmpPDFidx[9];
	Int shift = angle / 45;

	for (Int i = 1; i < nVec; i++) {
		Int j = i - shift;
		//std::cout << j << " tmpPDFidx " << tmpPDFidx[j] << std::endl;
		if (j > nVec - 1) j = j - (nVec - 1);
		if (j < 1) j = j + (nVec - 1);
		tmpPDFidx[j] = PDFidx[i];
	}

	for (Int i = 1; i < nVec; i++) {
		PDFidx[i] = tmpPDFidx[i];
	}


	if (flip == true) {
		ULLI tmp;

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

template <typename Int, typename Dub, class T>
void DataStBC<Int, Dub, T>::specifyFlipRotation(Int pos, bool& flip, Int& angle) {

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

template <typename Int, typename Dub, class T>
void DataStBC<Int, Dub, T>::vectorMapping(Int angle_, bool flip, Dub& U, Dub& V) {
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
//	Int pos;
//	Int* PDFidx = new Int[nVec];
//
//	for (Int i = 0; i < nBoundNode; i++) {
//
//		for (Int j = 0; j < nVec; j++) {
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
//	////Int sum;
//	////Int nNodeRegion;
//
//	////sum = 0;
//	////for (Int iReg = 0; iReg < nReg; iReg++) {
//
//	////	nNodeRegion = nNodeReg[iReg];
//	////	if (BCidx[iReg] > 0) {
//
//	////		for (Int i = sum; i < sum + nNodeRegion; i++) {
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
//Int DataStBC::nodeOrient(Int*& PDFidx) {
//	Int pos = -1;
//	Int iPDF;
//
//	iPDF = IntextPDF(PDFidx[1]);    Int p1 = IntodePDF(iPDF);
//	iPDF = IntextPDF(PDFidx[2]);    Int p2 = IntodePDF(iPDF);
//	iPDF = IntextPDF(PDFidx[3]);    Int p3 = IntodePDF(iPDF);
//	iPDF = IntextPDF(PDFidx[4]);    Int p4 = IntodePDF(iPDF);
//	iPDF = IntextPDF(PDFidx[5]);    Int p5 = IntodePDF(iPDF);
//	iPDF = IntextPDF(PDFidx[6]);    Int p6 = IntodePDF(iPDF);
//	iPDF = IntextPDF(PDFidx[7]);    Int p7 = IntodePDF(iPDF);
//	iPDF = IntextPDF(PDFidx[8]);    Int p8 = IntodePDF(iPDF);
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
