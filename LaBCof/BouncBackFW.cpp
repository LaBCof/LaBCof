#include "BouncBackFW.h"

template <typename Int, typename Dub>
BouncBackFW<Int, Dub>::BouncBackFW() {
}

template <typename Int, typename Dub>
BouncBackFW<Int, Dub>::BouncBackFW(DataStBCIndirect<Int, Dub>& DataSt_) :D2Q9BC<Int, Dub>(DataSt_) {
	this->schemeInx = 1;

	Int nFWregions = 0;
	for (Int iReg = 0; iReg < this->nReg; iReg++) {
		if (this->BCidx[iReg] == this->schemeInx) nFWregions++;
	}

	if (nFWregions != 0) {
		Int size = this->nBoundNode * this->nVec;
		fVal_tm1 = new Dub[size];
		fi_tm1 = new Dub[size];
		for (Int i = 0; i < size; i++) {
			fVal_tm1[i] = this->bcPDFv[i];
			fi_tm1[i] = this->bcPDFv[i];
		}
	}

	std::cout << "BouncBackFW obj done." << std::endl;

}


template <typename Int, typename Dub>
void BouncBackFW<Int, Dub>::scheme(RegProperties<Int, Dub> prop) {
	Int iPDF = prop.PDFidx[0];
	Int iNode = this->DataSt.iNodePDF(iPDF);

	for (Int i = 0; i < this->nVec; i++) {
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
		prop.PDFval[4] = fVal_tm1[iNode * this->nVec + 8];
		prop.PDFval[8] = fVal_tm1[iNode * this->nVec + 4];

		for (Int i = 0; i < this->nVec; i++) {
			fi[i] = fi_tm1[iNode * this->nVec + i];
		}

		Dub rho = Rho(fi);
		Dub u = Ux(fi);
		Dub v = Uy(fi);

		tmpFval[4] = collide(fi[4], u, v, rho, 1.0, -1.0, 1. / 36);
		tmpFval[8] = collide(fi[8], u, v, rho, -1.0, 1.0, 1. / 36);


		for (Int i = 0; i < this->nVec; i++) {
			fi_tm1[iNode * this->nVec + i] = prop.PDFval[i];
		}

	}
	else if (7 < prop.pos && prop.pos < 12) {
		prop.PDFval[6] = fVal_tm1[iNode * this->nVec + 2];
	}

	for (Int i = 0; i < this->nVec; i++) {
		fVal_tm1[iNode * this->nVec + i] = tmpFval[i];
	}

}


template <typename Int, typename Dub>
Dub BouncBackFW<Int, Dub>::collide(Dub fi, Dub u, Dub v, Dub rho, Dub Cx, Dub Cy, Dub w) {

	Dub tau = 1.0;

	Dub u2, uick, uick2, feq;

	u2 = u * u + v * v;

	uick = Cx * u + Cy * v;
	uick2 = uick * uick;

	feq = rho * w * (1.0 + 3.0 * uick + 4.5 * uick2 - 1.5 * u2);

	return  fi - (fi - feq) * tau;

}

template <typename Int, typename Dub>
Dub BouncBackFW<Int, Dub>::Rho(Dub* PDFv) {
	Dub rho = PDFv[0] + PDFv[1] + PDFv[2] + PDFv[3] + PDFv[4] + PDFv[5] + PDFv[6] + PDFv[7] + PDFv[8];
	return rho;
}

template <typename Int, typename Dub>
Dub BouncBackFW<Int, Dub>::Ux(Dub* PDFv) {
	Dub u = PDFv[2] + PDFv[3] + PDFv[4] - PDFv[6] - PDFv[7] - PDFv[8];


	Dub rho = Rho(PDFv);
	u /= rho;
	return u;
}

template <typename Int, typename Dub>
Dub BouncBackFW<Int, Dub>::Uy(Dub* PDFv) {
	Dub v = PDFv[1] + PDFv[2] - PDFv[4] - PDFv[5] - PDFv[6] + PDFv[8];
	Dub rho = Rho(PDFv);
	v /= rho;
	return v;

}