#pragma once
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <cmath>

//#include "..\TypeDefinition.h"

//typedef long long int int2;

template <typename int1, typename int2, typename Dub, class T>
class DataStBC
{

public:
	int2 nReg; /* Number of regions of regular grid */
	int2 nBoundNode; /* Number of boundary nodes */
	int2* nNodeReg; /* Number of nodes belong to each region */

	Dub* bcPDFv; /* PDF values of boundary nodes */
	int2* bcPDFi; /* PDF Intdexes of boundary PDFs */
	int2* orient; /* Orientation of boundary nodes */
	int2* iBondNode;

	int2* BCidx; /* Intdex of boundary condition */
	Dub* rho; /* Density */
	Dub* xVel; /* Velocity int2 x direction */
	Dub* yVel; /* Velocity int2 y direction */

	Dub* Cx; /* Coefficients of lattice stencil int2 x direction */
	Dub* Cy; /* Coefficients of lattice stencil int2 y direction */

protected:	
	int2 nVec; /* Number of vectors of lattice stensil */
	int1 nPDF; /* Number of PDFs formIntg the grid */
	int2 nNode; /* Number of nodes formIntg the grid */
	int2 nFluidNode; /* Number of fluid nodes formIntg the grid */


public:
	/*
	* Defult constructor.
	*/
	DataStBC<int1, int2, Dub, T>();

	/*
	 In this function all of the set_* methods are invoked to generate the data structure of the framework.
	*/
	void DataStPreProc();

	/*
	 set the number of regions forming the regular grid.
	*/
	void virtual set_nReg() = 0;

	/*
	 set the number of boundary nodes.
	*/
	void virtual set_nBoundNode() = 0;

	/*
	 set the number of nodes belonging to each region of the regular grid
	*/
	void virtual set_nNodeReg() = 0;

	/*
	 specifying the index of PDFs belonging to the boundary nodes.
	*/
	void virtual set_bcPDFi() = 0;

	/*
	 set the orienatation of the boundary nodes. Here, an index based approach are used to store
	 the orientation. Each index reperesent the following orientations:
	 Index  | orientation
	 --------------------
		0	| bottom side
		1	| top side
		2	| left side
		3	| right side
		4	| bottom-left corner
		5	| bottom-right corner
		6	| top-left corner
		7	| top-right corner
		8	| bottom-left concave corner
		9	| bottom-right concave corner
		10	| top-left concave corner
		11	| top-right concave corner
	*/
	void virtual set_orient() = 0;

	/*
	Each node has an index. In this function the inxes of each boundary node is stores in an array.
	*/
	void virtual set_iBondNode() = 0;

	/*
	The boundary condition index indicate which BC should be applied on a boundary. Untill now the following BC 
	are implemented in the framework:
	================ BC index ===============
	Fluid:                           -1
	Solid:                            0
	Full-Way:                         1
	ZouHe-Pressure:                   3
	ZouHe-Velocity:                   4
	Periodic:                         5
	Symmetry:                         6
	Open-Boundary:                    7
	Moment-Method:                    12
	Convex-Corner:                    10000
	Convex-Corner-Moment-Method:      10002
	================ BC index ===============
	*/
	void virtual set_BCidx() = 0;

	/*
	Set the value of density at each boundary. 
	Note: 10000 indicate that the value is not specified and an extrapolation is need to specify it.
	*/
	void virtual set_rho() = 0;

	/*
	Set the value of velocity in X direction at each boundary. 
	Note: 10000 indicate that the value is not specified and an extrapolation is need to specify it.
	*/
	void virtual set_xVel() = 0;

	/*
	Set the value of velocity in Y direction at each boundary. 
	Note: 10000 indicate that the value is not specified and an extrapolation is need to specify it.
	*/
	void virtual set_yVel() = 0;

	/*
	The unity vector value in X direction based on the bellow stencil:
     8----1---2
     | \  |  /|
     |  \ | / |
     7----0---3
     |  / | \ | 
     | /  |  \|
     6----5---4
	*/
	void virtual set_Cx() = 0;

	/*
	Set the unity vector value in Y direction based on the bellow stencil:
     8----1---2
     | \  |  /|
     |  \ | / |
     7----0---3
     |  / | \ | 
     | /  |  \|
     6----5---4
	*/
	void virtual set_Cy() = 0;

	/*
	Set the number of velocity vectors of the stencil.
	*/
	void virtual set_nVec() = 0;

	/*
	Set the number of PDFs constitue the grid. For example if there are 10 fluid and boundary nodes 
	and also using a D2Q9 then the number of PDFs=90.
	*/
	void virtual set_nPDF() = 0;

	/*
	Set the number of fluid and boundary nodes.
	*/
	void virtual set_nNode() = 0;

	/*
	Set the number of fluid nodes.
	*/
	void virtual set_nFluidNode() = 0; 

	/*
	* The required value of rotation int2 degree and the flip operation are specified int2 this method.
	* @param pos is the orientation of a node.
	* @param flip specify if the PDF should be flipped or not (This is Intput/output).
	* @param angle specify angle of rotation to mapp the PDFs (This is Intput/output).
	*/
	void specifyFlipRotation(int2 pos, bool& flip, int2& angle);

	/*
	* By applyIntg the flip and rotation values the velocity components are mapped.
	* @param angle specify angle of rotation to mapp the PDFs
	* @param flip specify if the PDF should be flipped or not.
	* @param U is the velocity int2 x-direction (This is Intput/output).
	* @param V is the velocity int2 y-direction (This is Intput/output).
	*/
	void vectorMapping(int2 angle_, bool flip, Dub& U, Dub& V);

	/*
	* By applyIntg the flip and rotation values the PDF Intdexes are mapped.
	* @param angle specify angle of rotation to mapp the PDFs
	* @param flip specify if the PDF should be flipped or not.
	* @param PDFidx is the Intdexes of a node (This is Intput/output).
	*/
	void stencilMapping(int2 angle, bool flip, int1* PDFidx);

	/*
	* The Intdexes of all the edges/corners boundary nodes are mapped to the "left side"/"bottom-left corner". 
	*/
	void bcPDFmapping();

	/*
	* Get the values of PDFs belong to all of the boundary nodes and store them int2 the array "bcPDFv".
	*/
	void virtual get_bcPDFvFromLBM() = 0;

	/*
	* Write the array "bcPDFv" to the data structure of base LBM code.
	*/
	void virtual write_bcPDFvToLBM() = 0;

	/*
	* Get the values of a PDF from the base LBM code.
	*/
	Dub virtual get_PDFvFromLBM (int2 iPDF) = 0;

	/*
	* Get density values of a node from the base LBM code.
	*/
	Dub virtual get_densityFromLBM(int2 Intode) = 0;

	/*
	* Get velocity in x-direction of a node from the base LBM code.
	*/
	Dub virtual get_xVelFromLBM(int2 Intode) = 0;

	/*
	* Get velocity in y-direction of a node from the base LBM code.
	*/
	Dub virtual get_yVelFromLBM(int2 Intode) = 0;

	/*
	* The Intdexes of PDFs belong to all the boundary nodes are stored int2 the array "bcPDFi".
	*/
	//void virtual findBoundPDF() = 0;

	/*
	* Get the node Intdex of a PDF based on the data structure of the base LBM code.
	*/
	int2 virtual iNodePDF(int1 iPDF) = 0;

	/*
	* Get the Intdex of next PDF based on the data structure of the base LBM code.
	* Nexet PDF: When streamIntg function is applied on a PDF int2 LBM it goes to 
	* another PDF. We call that PDF as "nextPDF". 
	*/
	int1 virtual iNextPDF(int1 iPDF) = 0;

	/*
	* Get the Intdex of the "iVel"th PDF belongIntg to a node.
	* @param Intode is the Intdex of a node.
	* @param iVel is the Intdex of a PDF based on the lattice stencil.
	* @return The Intdex of the PDF based on the data structure on the base LBM code.
	*/
	int1 virtual iPDFNode(int2 iNode, int2 iVel) = 0;

};


