# LaBCof: Lattice Boltzmann Boundary Condition Framework

In this implementation object-oriented programming has been used to develop the framework.
Here a kind of adapter pattern in object-oriented programming is used to link the framework 
to the base LBM code. So, it is not needed to modify the framework code and the base LBM 
code when someone wants to use this framework.
 
1. Download the framework:
The following files are the implemented framework:
The main class of the framework
MainBC.h, MainBC.cpp
Data structure class
DataStBC.h, DataStBC.cpp
Existing boundary condition
D2Q9BC.h, D2Q9BC.cpp
BouncBackFW.h, BouncBackFW.cpp
ConvexCorner.h, ConvexCorner.cpp
ConvexCornerMomentMethod.h, ConvexCornerMomentMethod.cpp
Momentmethod.h, Momentmethod.cpp
OpenBoundFrstOrd.h, OpenBoundFrstOrd.cpp
Periodic.h, Periodic.cpp
Symmetry.h, Symmetry.cpp
ZouHePress.h, ZouHePress.cpp
ZouHeVelocity.h, ZouHeVelocity.cpp

2. Implement the DataStBC class:
To develop a new data structure for the boundary condition framework it is required to implement
 the DataStBC class provided in DataStBC.h and DataStBC.cpp. Let's call this implemented class 
 DataStructure. To do that, all the virtual functions should be implemented. Each of the virtual 
 functions is documented in the code as a guide for the developer.
 
3. Create an object from the implemented DataStructure class:
Let's call this object dataSt.

4. Create an object from the MainBC class:
First of all, let's create an object from the MainBC class from the provided constructor and call 
it mainBC. To create this object it is needed to pass the dataSt object as an argument of the 
constructor of the MainBC class. In this way, the BC framework and LBM code are linked. Also, 
it is required to include the following files where you want to use the MainBC class (be careful 
of the relative path, if any):
"MainBC.h"
"MainBC.cpp"

5. Calculate unknown boundary PDFs:
Now, in the LBM code at some points, it is required to calculate unknown PDFs of boundary nodes. 
In order to perform that the main function of the boundary condition framework, i.e. bcPDFvCalculation(), 
is invoked. Inside this function, at first, the PDF values of the boundary nodes from the base LBM code 
are copied into the framework. Then the unknown PDFs are calculated and finally, they are written back 
to the base LBM code data structure. 

