#include "BouncBackFW.h"

template <typename int1, typename int2, typename Dub, class T>
BouncBackFW<int1, int2, Dub, T>::BouncBackFW() {
}

template <typename int1, typename int2, typename Dub, class T>
BouncBackFW<int1, int2, Dub, T>::BouncBackFW(T& DataSt_) :D2Q9BC<int1, int2, Dub, T>(DataSt_) {
	this->schemeInx = 1;

	int2 nFWregions = 0;
	for (int2 iReg = 0; iReg < this->nReg; iReg++) {
		if (this->BCidx[iReg] == this->schemeInx) nFWregions++;
	}

	if (nFWregions != 0) {
		int2 size = this->nBoundNode * this->nVec;
		fVal_tm1 = new Dub[size];
		fi_tm1 = new Dub[size];
		for (int2 i = 0; i < size; i++) {
			fVal_tm1[i] = this->bcPDFv[i];
			fi_tm1[i] = this->bcPDFv[i];
		}
	}

	std::cout << "BouncBackFW obj done." << std::endl;

}


template <typename int1, typename int2, typename Dub, class T>
void BouncBackFW<int1, int2, Dub, T>::scheme(RegProperties<int1, int2, Dub, T> prop) {
	int1 iPDF = prop.PDFidx[0];
	int2 iNode = this->DataSt.iNodePDF(iPDF);

	for (int2 i = 0; i < this->nVec; i++) {
		tmpFval[i] = prop.PDFval[i];
	}

	if (prop.pos < 4) {

		prop.PDFval[2] = fVal_tm1[iNode * this->nVec + 6];
		prop.PDFval[3] = fVal_tm1[iNode * this->nVec + 7];
		prop.PDFval[4] = fVal_tm1[iNode * this->nVec + 8];

	}
	else if (3 < prop.pos && prop.pos < 8) {

		prop.PDFval[1] = fVal_tm1[iNode * this->nVec + 5];
		prop.PDFval[2] = fVal_tm1[iNode * this->nVec + 6];
		prop.PDFval[3] = fVal_tm1[iNode * this->nVec + 7];
		//prop.PDFval[4] = 0.1111;
		//prop.PDFval[8] = 0.1111;
		prop.PDFval[4] = fVal_tm1[iNode * this->nVec + 8];
		prop.PDFval[8] = fVal_tm1[iNode * this->nVec + 4];

		for (int2 i = 0; i < this->nVec; i++) {
			fi[i] = fi_tm1[iNode * this->nVec + i];
		}

		Dub rho = Rho(fi);
		Dub u = Ux(fi);
		Dub v = Uy(fi);

		tmpFval[4] = collide(fi[4], u, v, rho, 1.0, -1.0, 1. / 36);
		tmpFval[8] = collide(fi[8], u, v, rho, -1.0, 1.0, 1. / 36);


		for (int2 i = 0; i < this->nVec; i++) {
			fi_tm1[iNode * this->nVec + i] = prop.PDFval[i];
		}

	}
	else if (7 < prop.pos && prop.pos < 12) {

		prop.PDFval[6] = fVal_tm1[iNode * this->nVec + 2];
	}

	for (int2 i = 0; i < this->nVec; i++) {
		fVal_tm1[iNode * this->nVec + i] = tmpFval[i];
	}


}
