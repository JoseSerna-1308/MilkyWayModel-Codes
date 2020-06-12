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
	const double n=20000;					// ITERATIONS
  	const int Min=0;						// ITERATION INITIAL
  	const int Max=100;						// ITERATION FINAL
  	const double dr=(Max-Min)/n;			// STEP

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

	const double aH = 16.1;							// [kpc]							// HALO (NFW)
	const double rhoH = (2.78e37)/GalMassUnit;		// [kg/kpc^3] = 1.4e7 [Msun/kpc^3]	// HALO (NFW)
	const double aHIso = 6;							// [kpc]							// HALO (ISO)
	const double mHIso = 9.94e40/GalMassUnit;		// [kg] = 5e10 [Msun]				// HALO (ISO)
	const double mD = (2e41)/GalMassUnit;			// [kg] = 1e11 [Msun] 				// DISC
	const double aD = 6.5;							// [kpc]							// DISC
	const double bD = 0.26;							// [kpc]							// DISC 
	const double mB = (5.17e40)/GalMassUnit;		// [kg] = 2.6e10 [Msun]				// BULGE
	const double aB = 0.4;							// [kpc]                            // BULGE
//	const double rhoC = (1.44e37)/GalMassUnit; 		// [kg/kpc^3] = 7.25e6 [Msun/kpc^3] // CORONA (Phi')
//	const double aC = 80;							// [kpc]							// CORONA (Phi')
	const double rhoC = 2.72e37/GalMassUnit; 		// [kg/kpc^3] = 1.37e7 [Msun/kpc^3] // CORONA (-Phi)
//	const double rhoC = 2.72e37;			 		// [kg/kpc^3] = 1.37e7 [Msun/kpc^3] // CORONA (-Phi)
	const double aC = 7.82;							// [kpc]							// CORONA (-Phi)		
	const double mZ = 8.95e39/GalMassUnit;			// [kg] = 4.5e9 [Msun] 				// CORE
	const double aZ = 0.0;							// [kpc]							// CORE
	const double bZ = 0.25;							// [kpc]							// CORE		
	const double aHCub = pow(aH,3);
	const double bDCuad = pow(bD,2);
	const double aCCuad = pow(aC,2);  

	//==============================
  	//  VARIABLES
	//==============================

	ofstream outfile_Halo,outfile_Disk,outfile_Bulge,outfile_Corona,outfile_Core,outfile_Total;	// OUTFILE FILES
	string name_Halo,name_Disk,name_Bulge,name_Corona,name_Core,name_Total;						// OUTFILE FILES' NAMES
	double r,rCuad;																				// RADIUS AND RADIUS SQUARED
	double vH,vD,vB,vC,vZ,vT;                         											// VELOCITIES
	double vHCuad,vHCuadA,vDCuad,vBCuad,vCCuad,vZCuad,vTCuad;   								// VELOCITIES SQUARED
	double vHEsc,vDEsc,vBEsc,vCEsc,vZEsc,vTEsc;               									// ESCALATED VELOCITIES

	ofstream outfile_HaloIso;
	string name_HaloIso;
	double vHIso, vHIsoCuad, vHIsoCuadA, vHIsoEsc;

	ofstream outfile_TotalwIso;
	string name_TotalwIso;
	double vTIso,vTIsoCuad,vTIsoEsc;

	ofstream outfile_Corona1;
	string name_Corona1;
/*
	ofstream outfile_TotalwoZ;
	string name_TotalwoZ;
	double vTZ,vTZCuad,vTZEsc;
*/

	//==============================
  	//  SPEED ROTATION CURVES
	//==============================

	// Velocities normalized to G=1

	name_HaloIso = "Velocity_HaloIso.txt";
	name_Disk = "Velocity_Disk.txt";
  	name_Bulge = "Velocity_Bulge.txt";
  	name_Corona = "Velocity_Corona.txt";
  	name_Corona1 = "Velocity_Corona1.txt";
  	name_Total = "Velocity_Total.txt";
//		name_Halo = "Velocity_Halo.txt";
//  	name_Core = "Velocity_Core.txt";
//  	name_TotalwoC = "Velocity_TotalwoC.txt";
//  	name_TotalwoZ = "Velocity_TotalwoZ.txt";
//  	name_TotalwIso = "Velocity_TotalIso.txt";
//  	outfile_Halo.open( name_Halo.c_str(), ios::out );
  	outfile_HaloIso.open( name_HaloIso.c_str(), ios::out );
  	outfile_Disk.open( name_Disk.c_str(), ios::out );
  	outfile_Bulge.open( name_Bulge.c_str(), ios::out );
  	outfile_Corona.open( name_Corona.c_str(), ios::out );
  	outfile_Corona1.open( name_Corona1.c_str(), ios::out );
  	outfile_Total.open( name_Total.c_str(), ios::out );
//  	outfile_Core.open( name_Core.c_str(), ios::out );
//  	outfile_TotalwoC.open( name_TotalwoC.c_str(), ios::out );
//  	outfile_TotalwoZ.open( name_TotalwoZ.c_str(), ios::out );
//  	outfile_TotalwIso.open( name_TotalwIso.c_str(), ios::out );
    for(int ii=0; ii<n; ii++){
   	  r = Min + ii*dr;
   	  rCuad = pow(r,2);


      //==============================
      // HALO CONTRIBUTION (ISO)
      //==============================
      
      double auxHIso = r/aHIso;

   	  vHIsoCuad = (mHIso/aHIso)*(1-((1/auxHIso)*atan(auxHIso)));

   	  if(r==0){
      	vHIsoCuad = 0;
      	vHIsoCuadA = 0;
      	vHIso = 0;
      }
      else if(vHIsoCuad>0){
        vHIso = pow(vHIsoCuad,0.5);
        vHIsoCuadA = vHIsoCuad;
      }
      else{
        vHIso = pow(-vHIsoCuad,0.5);
        vHIsoCuadA = -vHIsoCuad;
      }
      vHIsoEsc = vHIso*10;
      outfile_HaloIso << r << "\t" << vHIsoEsc << endl;


      //==============================
      // DISK CONTRIBUTION
      //==============================

      double auxD = pow((aD+bD),2);

      vDCuad = (mD*rCuad)/(pow((rCuad + auxD),1.5));

      if(vDCuad>0){
        vD = pow(vDCuad,0.5);
      }
      else{
        vD = pow(-vDCuad,0.5);
      }
      vDEsc = vD*10;
      outfile_Disk << r << "\t" << vDEsc << endl;

      //==============================
      // BULGE CONTRIBUTION
      //==============================
      
   	  vBCuad = (mB*r)/(pow(r+aB,2));

      if(vBCuad>0){
        vB = pow(vBCuad,0.5);
      }
      else{
        vB = pow(-vBCuad,0.5);
      }
      vBEsc = vB*10;
      outfile_Bulge << r << "\t" << vBEsc << endl;

      //==============================
      // CORONA CONTRIBUTION (M&J)
      //==============================
      
//   	  vCCuad = 4*pi*rhoC*aCCuad*(2*aC*atan(r/aC)-((2*aCCuad*r+pow(r,3))/(aCCuad+rCuad)))/(rCuad);	// Phi'
      vCCuad = 4*pi*rhoC*pow(aC,2)*(1-((aC/r)*atan(r/aC)));

   	  if(r==0){
   	  	vCCuad = 0;
   	  	vC = 0;
   	  }
      else if(vCCuad>0){
//	  if(vCCuad>0){
        vC = pow(vCCuad,0.5);
      }
      else{
        vC = pow(-vCCuad,0.5);
      }
      vCEsc = vC*1;
      outfile_Corona << r << "\t" << vCEsc << endl;

/*
      //==============================
      // CORONA CONTRIBUTION (L&D)
      //==============================
      
//      double vCCuad1 = (453.812*pow(r,3)+(-3546.54*pow(r,2)-216602)*atan(0.127959*r)+27716.2*r)/(r*(pow(r,2)+61.0742));
//      double vCCuad1 = 4*3.1416*pow(7.81,2)*pow(1.37,-2)*((7.81*atan(0.128*r)-r)/r);
      double vcLDC = pow(10,(3/2))*pow(-4*3.1416*pow(7.81,2)*pow(1.37,-2)*((7.81*atan(0.128*r)-r)/r),0.5); 
      double vC1,vCCuad1;

   	  if(r==0){
   	  	vCCuad1 = 0;
   	  	vC1 = 0;
   	  }
      else if(vCCuad1>0){
//	  if(vCCuad>0){
        vC1 = pow(vCCuad1,0.5);
      }
      else{
        vC1 = pow(-vCCuad1,0.5);
      }
      double vC1Esc = vC1*1;
//      outfile_Corona1 << r << "\t" << vC1Esc << endl;
      outfile_Corona1 << r << "\t" << vcLDC << endl;
*/

      //==============================
      // TOTAL CONTRIBUTION A
      //==============================

      vTIsoCuad = 100*(vHIsoCuadA + vDCuad + vBCuad) + vCCuad; 

      if(r==0){
        vTIso = 0;
      }
      else if(vTIsoCuad>0){
        vTIso = pow(vTIsoCuad,0.5);
      }
      else{
        vTIso = pow(-vTIsoCuad,0.5);
      }

      vTIsoEsc = vTIso*1;
      outfile_Total << r << "\t" << vTIsoEsc << endl;

/*
      //==============================
      // HALO CONTRIBUTION (NFW)
      //==============================
    
      vHCuad = 4*pi*rhoH*aHCub*(r-((aH+r)*log(1+(r/aH))))/(r*(r+aH));

      if(r==0){
      	vHCuad = 0;
      	vHCuadA = 0;
      	vH = 0;
      }
      else if(vHCuad>0){
        vH = pow(vHCuad,0.5);
        vHCuadA = vHCuad;
      }
      else{
        vH = pow(-vHCuad,0.5);
        vHCuadA = -vHCuad;
      }
      vHEsc = vH*10;
      outfile_Halo << r << "\t" << vHEsc << endl;

      //==============================
      // CORE CONTRIBUTION
      //==============================

      double auxZ = pow((aZ+bZ),2);

      vZCuad = (mZ*rCuad)/(pow((rCuad + auxZ),1.5));

      if(vZCuad>0){
        vZ = pow(vZCuad,0.5);
      }
      else{
        vZ = pow(-vZCuad,0.5);
      }
      vZEsc = vZ*10;
      outfile_Core << r << "\t" << vZEsc << endl;

      //==============================
      // TOTAL CONTRIBUTION B
      //==============================

      vTZCuad = vHCuadA + vDCuad + vBCuad + vCCuad; 

      if(r==0){
        vTZ = 0;
      }
      else if(vTZCuad>0){
        vTZ = pow(vTZCuad,0.5);
      }
      else{
        vTZ = pow(-vTZCuad,0.5);
      }
      vTZEsc = vTZ*10;
      outfile_TotalwoZ << r << "\t" << vTZEsc << endl;

      //==============================
      // TOTAL CONTRIBUTION C
      //==============================

      vTwoCCuad = vHCuadA + vDCuad + vBCuad; 

      if(r==0){
        vTwoC = 0;
      }
      else if(vTwoCCuad>0){
        vTwoC = pow(vTwoCCuad,0.5);
      }
      else{
        vTwoC = pow(-vTwoCCuad,0.5);
      }
      vTwoCEsc = vTwoC*10;
      outfile_TotalwoC << r << "\t" << vTwoCEsc << endl;

      //==============================
      // TOTAL CONTRIBUTION D
      //==============================

      vTCuad = vHCuadA + vDCuad + vBCuad + vCCuad; 

      if(r==0){
        vT = 0;
      }
      else if(vTCuad>0){
        vT = pow(vTCuad,0.5);
      }
      else{
        vT = pow(-vTCuad,0.5);
      }
      vTEsc = vT*10;
      outfile_Total << r << "\t" << vTEsc << endl;
*/

    }
	outfile_HaloIso.close();
  	outfile_Disk.close();
  	outfile_Bulge.close();
  	outfile_Corona.close();
  	outfile_Corona1.close();
  	outfile_Total.close();
//		outfile_Halo.close();
//  	outfile_Core.close();
//  	outfile_TotalwoZ.close();
//  	outfile_TotalwoC.close();
//  	outfile_TotalwIso.close();












  return 0;
}
