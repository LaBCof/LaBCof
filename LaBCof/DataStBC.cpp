#include "DataStBC.h"

template <typename Int, typename Dub>
DataStBC<Int, Dub>::DataStBC() {

}

template <typename Int, typename Dub>
void DataStBC<Int, Dub>::DataStPreProc(){

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

	set_orient();

	this->bcPDFmapping();

	this->bcPDFv = new double[this->nVec * this->nBoundNode];
	get_bcPDFvFromLBM();

}

template <typename Int, typename Dub>
void DataStBC<Int, Dub>::bcPDFmapping()
{

	Int* PDFidx = new Int[nVec];

	bool flip = false;
	Int angle = 0;
	Int pos = -1;

	for (Int i = 0; i < nBoundNode; i++) {

		pos = orient[i];

		specifyFlipRotation(pos, flip, angle);

		for (Int j = 0; j < nVec; j++) {
			PDFidx[j] = bcPDFi[nVec * i + j];
		}

		stencilMapping(angle, flip, PDFidx);

		for (Int j = 0; j < nVec; j++) {
			bcPDFi[i * nVec + j] = PDFidx[j];
		}

	}

}

template <typename Int, typename Dub>
void DataStBC<Int, Dub>::stencilMapping(Int angle, bool flip, Int* PDFidx) {

	Int nVec = 9;
	Int tmpPDFidx[9];
	Int shift = angle / (45);

	for (Int i = 1; i < nVec; i++) {
		Int j = i - shift;
		if (j > nVec - 1) j = j - (nVec - 1);
		if (j < 1) j = j + (nVec - 1);
		tmpPDFidx[j] = PDFidx[i];
	}

	for (Int i = 1; i < nVec; i++) {
		PDFidx[i] = tmpPDFidx[i];
	}


	if (flip == true) {
		Int tmp;

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

template <typename Int, typename Dub>
void DataStBC<Int, Dub>::specifyFlipRotation(Int pos, bool& flip, Int& angle) {

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

template <typename Int, typename Dub>
void DataStBC<Int, Dub>::vectorMapping(Int angle_, bool flip, Dub& U, Dub& V) {
	Dub pi = 4 * atan(1.0);
	Dub angle = angle_ * pi / 180;

	Dub u = U * cos(angle) - V * sin(angle);
	Dub v = U * sin(angle) + V * cos(angle);

	if (flip == true) v = -v;

	U = u;
	V = v;
}
