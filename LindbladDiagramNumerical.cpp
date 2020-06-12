#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <math.h>
#include <sstream>
#include <iomanip>
using namespace std;

// M. Osorio & J. Serna. 2020.
// jmosorio@astro.unam.mx 
// j_serna@ciencias.unam.mx

int main( int argc , char **argv ) {

    //==============================
    //  CONSTANTS
    //==============================
  
	const double GalMassUnit = 4.613e37;   	// [kg] = 2.32 [Msun]
	const double pi = 3.1415;				// PI
	const double n=50000;					// ITERATIONS
  	const double Min=0.1;						// ITERATION INITIAL
  	const double dr=0.01;					// STEP
  	
/*
	// 	Original constants

	const double aH = 16.1;			// [kpc]							// HALO (NFW)
	const double rhoH = 2.78e37;	// [kg/kpc^3] = 1.4e7 [Msun/kpc^3]	// HALO (NFW)
	const double aHIso = 6;			// [kpc]							// HALO (ISO)
	const double mHIso = 9.94e40;	// [kg] = 5e10 [Msun]				// HALO (ISO)
	const double mD = 2e41;			// [kg] = 1e11 [Msun] 				// DISC
	const double aD = 6.5;			// [kpc]							// DISC
	const double bD = 0.26;			// [kpc]							// DISC 
	const double mB = 5.17e40;		// [kg] = 2.6e10 [Msun]				// BULGE
	const double aB = 0.4;			// [kpc]							// BULGE
	const double rhoC = 1.44e37; 	// [kg/kpc^3] = 7.25e6 [Msun/kpc^3] // CORONA
	const double aC = 80;			// [kpc]							// CORONA	
	const double mZ = 8.95e39;		// [kg] = 4.5e9 [Msun] 				// CORE
	const double aZ = 0.0;			// [kpc]							// CORE
	const double bZ = 0.25;			// [kpc]							// CORE
	const double aHCub = pow(aH,3);
	const double bDCuad = pow(bD,2);
*/

	//  Constants normalized to Galactic Mass Units (1 GMU = 3.32 Msun)

//	const double aH = 16.1;							// [kpc]							// HALO (NFW)
//	const double rhoH = (2.78e37)/GalMassUnit;		// [kg/kpc^3] = 1.4e7 [Msun/kpc^3]	// HALO (NFW)
	const double aH = 6;							// [kpc]							// HALO (ISO)
	const double mH = 9.94e40/GalMassUnit;			// [kg] = 5e10 [Msun]				// HALO (ISO)
	const double mD = 2e41/GalMassUnit;				// [kg] = 1e11 [Msun] 				// DISC
	const double aD = 6.5;							// [kpc]							// DISC
	const double bD = 0.26;							// [kpc]							// DISC 
	const double mB = 5.17e40/GalMassUnit;			// [kg] = 2.6e10 [Msun]				// BULGE
	const double aB = 0.4;							// [kpc]                            // BULGE
//	const double rhoC = 1.44e37/GalMassUnit; 		// [kg/kpc^3] = 7.25e6 [Msun/kpc^3] // CORONA (Phi')
//	const double aC = 80;							// [kpc]							// CORONA (Phi')
	const double rhoC = 2.72e37/GalMassUnit; 		// [kg/kpc^3] = 1.37e7 [Msun/kpc^3] // CORONA (-Phi)
	const double aC = 7.82;							// [kpc]							// CORONA (-Phi)	
	const double RCT = 150;							// [kpc]							// CORONA
	const double mZ = 8.95e39/GalMassUnit;			// [kg] = 4.5e9 [Msun] 				// CORE
	const double aZ = 0.0;							// [kpc]							// CORE
	const double bZ = 0.25;							// [kpc]							// CORE		
	const double aHCub = pow(aH,3);
	const double bDCuad = pow(bD,2);
	const double aCCuad = pow(aC,2);

    //==============================
    //  VARIABLES
    //==============================

	ofstream outfile_CurveHalo,outfile_CurveDisk,outfile_CurveBulge,outfile_CurveCorona,outfile_CurveCore,outfile_CurveTotal;		// OUTFILE
	string name_CurveHalo,name_CurveDisk,name_CurveBulge,name_CurveCorona,name_CurveCore,name_CurveTotal;							// OUTFILE' NAMES
  	double rCuad,r;																													// RADIUS
  	double LH,EH,LHCuad,LD,ED,LDCuad,LB,EB,LBCuad,LC,EC,LCCuad,ET,LT,LTCuad;														// ENERGY AND ANGULAR MOMENTUM

  	//==============================
    //  CIRCULAR ORBITS CURVE
    //==============================

  	//  Functions normalized to G=1

	name_CurveHalo = "CircularOrbitCurve_Halo.txt";
	name_CurveBulge = "CircularOrbitCurve_Bulge.txt";
	name_CurveDisk = "CircularOrbitCurve_Disk.txt";
	name_CurveCorona = "CircularOrbitCurve_Corona.txt";
	name_CurveTotal = "CircularOrbitCurve_Total.txt";

  	outfile_CurveHalo.open(name_CurveHalo.c_str(), ios::out);
  	outfile_CurveBulge.open(name_CurveBulge.c_str(), ios::out);
  	outfile_CurveDisk.open(name_CurveDisk.c_str(), ios::out);
  	outfile_CurveCorona.open(name_CurveCorona.c_str(), ios::out);
  	outfile_CurveTotal.open(name_CurveTotal.c_str(), ios::out);

  	for(int i=0; i<n; i++){
	  	r = Min + i*dr;
	  	rCuad = pow(r,2);

		//==============================
	    //  BULGE
	    //==============================

  		EB = -(mB*r)*pow(r+aB,-2)*(0.5+(aB/r));
  		
  		LBCuad = mB*pow(r,3)*pow(r+aB,-2);
	 	LB = pow(LBCuad,0.5);

	 	outfile_CurveBulge << EB << "\t" << LB << endl;

		//==============================
	    //  DISK
	    //==============================

	  	double auxD = rCuad + pow(aD+bD,2);

	  	ED = -mD*0.5*pow(auxD,-1.5)*((2*pow(aD+bD,2))+rCuad);

	  	LDCuad = mD*pow(r,4)*pow(auxD,-1.5);
	  	LD = pow(LDCuad,0.5);

	  	outfile_CurveDisk << ED << "\t" << LD << endl;

		//==============================
	    //  CORONA
	    //==============================

	  	double auxC = r/aC;

	  	EC = 2*pi*rhoC*pow(aC,2)*(((1/auxC)*atan(auxC))-1-log((1+pow(RCT/aC,2))/(1+pow(auxC,2))));

	  	LCCuad = 4*pi*rhoC*rCuad*pow(aC,2)*(1-((1/auxC)*atan(auxC)));
	  	if(r==0){
	  		LCCuad =0;
	  		LC =0;
	  	}
	  	else if(LCCuad<0){
	  		LC = pow(-LCCuad,0.5);
	  	}
	  	else{
	  		LC = pow(LCCuad,0.5);
	  	}

	  	outfile_CurveCorona << EC << "\t" << LC << endl;

		//==============================
	    //  HALO
	    //==============================

	  	double auxH = r/aH;

	  	EH = (mH/aH)*0.5*(1+log(1+pow(auxH,2))+((1/auxH)*atan(auxH)));

	  	LHCuad = mH*r*auxH*(1-(pow(auxH,-1)*atan(auxH)));
	  	LH = pow(LHCuad,0.5);

//	  	outfile_CurveHalo << EH << "\t" << LH << endl;
	  	outfile_CurveHalo << EH-1772 << "\t" << LH << endl;			// CORRECTION BECAUSE OF THE DISPLACEMENT (1772 UNITS)

		//==============================
	    //  TOTAL
	    //==============================

  		ET = EB + ED + EC + EH;

  		LTCuad = LBCuad + LDCuad + LCCuad + LHCuad;
  		LT = pow(LTCuad,0.5);	

  		outfile_CurveTotal << ET << "\t" << LT << endl;

  	}
 	outfile_CurveHalo.close();
 	outfile_CurveBulge.close();
 	outfile_CurveDisk.close();
 	outfile_CurveCorona.close();
 	outfile_CurveTotal.close();


//============================================================================================================================================


    //==============================
    //  CONSTANTS
    //==============================

 	const double de = 0.1;
 	const int m = 50000;
/*
	const double MH = 9.94e40/GalMassUnit;			// [kg] = 5e10 [Msun]				// HALO (ISO)
	const double MD = (2e41)/GalMassUnit;			// [kg] = 1e11 [Msun] 				// DISC
	const double MB = (5.17e40)/GalMassUnit;		// [kg] = 2.6e10 [Msun]				// BULGE
	const double RhoC = (1.44e37)/GalMassUnit; 		// [kg/kpc^3] = 7.25e6 [Msun/kpc^3] // CORONA
	const double MZ = 8.95e39/GalMassUnit;			// [kg] = 4.5e9 [Msun] 				// CORE
*/
    //==============================
    //  VARIABLES
    //==============================

 	ofstream outfile_ParT,outfile_ParH,outfile_ParD,outfile_ParB,outfile_ParC;								// OUTFILES
 	string name_ParT, name_ParH,name_ParD,name_ParB,name_ParC;												// OUTFILES' NAMES
 	double rB,rC,rH,rD,rT;																						// RADIUS
 	double EP,LP,LPCuad,EBP,LBP,LBPCuad,EHP,LHP,LHPCuad,EDP,LDP,LDPCuad,ECP,LCP,LCPCuad;					// PARABOLA ENERGY AND ANGULAR MOMENTUM
 	double pH,pB,pC,pD,pT;																						// GRAVITATIONAL POTENTIALS
 	double MinB,MinC,MinH,MinD,MinT;

  	//==============================
    //  CHARACTERISTIC PARABOLA
    //==============================

  	//==============================
    //  BULGE
    //==============================

	for(int ll=0; ll<5; ll++){ 
		rB= 1 + ll;
		
		pB = -mB/(rB+aB);
	 	MinB = pB;
		
		stringstream jj;  
		jj<<rB;  
		string radio;  
		jj>>radio;

		name_ParB = "Parabola_r" + radio + "_Bulge.txt";
		outfile_ParB.open(name_ParB.c_str(), ios::out);
		for(int kk=0; kk<m; kk++){

			EBP = MinB + kk*de;

			LBPCuad = 2*pow(rB,2)*(EBP-pB);
			LBP = pow(LBPCuad,0.5);

			outfile_ParB << EBP << "\t" << LBP << endl;

		}
		outfile_ParB.close();
	}

 	//==============================
    //  HALO
    //==============================

	for(int ll=0; ll<5; ll++){ 
		rH = 1 + ll;
		
		pH = (mH/aH)*(0.5*log(1+pow(rH/aH,2))+(aH/rH)*atan(rH/aH));
	 	MinH = pH;
		
		stringstream jj;  
		jj<<rH;  
		string radio;  
		jj>>radio;

		name_ParH = "Parabola_r" + radio + "_Halo.txt";
		outfile_ParH.open(name_ParH.c_str(), ios::out);
		for(int kk=0; kk<m; kk++){

			EHP = MinH + kk*de;

			LHPCuad = 2*pow(rH,2)*(EHP-pH);
			LHP = pow(LHPCuad,0.5);

//			outfile_ParH << EHP << "\t" << LHP << endl;
			outfile_ParH << EHP-1772 << "\t" << LHP << endl;			// CORRECTION BECAUSE OF THE DISPLACEMENT (1772 UNITS)

		}
		outfile_ParH.close();
	}

	//==============================
    //  DISK
    //==============================

	for(int ll=0; ll<5; ll++){ 
		rD = 1 + ll;
		
		pD = -mD*pow((pow(rD,2)+pow(aD+bD,2)),-0.5);
	 	MinD = pD;
		
		stringstream jj;  
		jj<<rD;  
		string radio;  
		jj>>radio;

		name_ParD = "Parabola_r" + radio + "_Disk.txt";
		outfile_ParD.open(name_ParD.c_str(), ios::out);
		for(int kk=0; kk<m; kk++){

			EDP = MinD + kk*de;

			LDPCuad = 2*pow(rD,2)*(EDP-pD);
			LDP = pow(LDPCuad,0.5);

			outfile_ParD << EDP << "\t" << LDP << endl;

		}
		outfile_ParD.close();
	}

  	//==============================
    //  CORONA
    //==============================

	for(int ll=0; ll<5; ll++){ 
		rC= 1 + ll;

//		pC = -4*pi*rhoC*pow(aC,2)*(1+log(pow((1+pow(RCT/aC,2))/(1+pow(rC/aC,2)),0.5))-pow(rC/aC,-1)*atan(rC/aC));		
		pC = -4*pi*rhoC*aCCuad*(1+log(pow((1+pow(RCT/aC,2))/(1+pow(rC/aC,2)),0.5))-((aC/rC)*atan(rC/aC)));
	 	MinC = pC;
		
		stringstream jj;  
		jj<<rC;  
		string radio;  
		jj>>radio;

		name_ParC = "Parabola_r" + radio + "_Corona.txt";
		outfile_ParC.open(name_ParC.c_str(), ios::out);
		for(int kk=0; kk<m; kk++){

			ECP = MinC + kk*de;

			LCPCuad = 2*pow(rC,2)*(ECP-pC);
			LCP = pow(LCPCuad,0.5);

			outfile_ParC << ECP << "\t" << LCP << endl;

		}
		outfile_ParC.close();
	}

  	//==============================
    //  TOTAL
    //==============================

	for(int ll=0; ll<30; ll++){ 
		rT= 1 + ll;

		pB = -mB/(rT+aB);
		pH = (mH/aH)*(0.5*log(1+pow(rT/aH,2))+(aH/rT)*atan(rT/aH));
		pD = -mD*pow((pow(rT,2)+pow(aD+bD,2)),-0.5);
		pC = -4*pi*rhoC*aCCuad*(1+log(pow((1+pow(RCT/aC,2))/(1+pow(rT/aC,2)),0.5))-((aC/rT)*atan(rT/aC)));
		pT = pB+pH+pD+pC;

	 	MinT = pT;
		
		stringstream jj;  
		jj<<rT;  
		string radio;  
		jj>>radio;

		name_ParT = "Parabola_r" + radio + "_Total.txt";
		outfile_ParT.open(name_ParT.c_str(), ios::out);
		for(int kk=0; kk<m; kk++){

			EP = MinT + kk*de;

			LPCuad = 2*pow(rT,2)*(EP-pT);
			LP = pow(LPCuad,0.5);

			outfile_ParT << EP << "\t" << LP << endl;

		}
		outfile_ParT.close();
	}

		
	






  return 0;
}
