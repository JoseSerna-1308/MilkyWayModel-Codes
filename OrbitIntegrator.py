import numpy as np
import matplotlib.pyplot as plt

# M. Osorio & J. Serna. 2020.
# jmosorio@astro.unam.mx 
# j_serna@ciencias.unam.mx

#====================================
#  CONSTANTS
#====================================

GalMassUnit = 4.613e37		# [kg] = 2.32 [Msun]
pi = 3.1415                 # PI
G = 1                       # Universal Gravitational Constant
mB = 5.17e40/GalMassUnit    # [kg] = 2.6e10 [Msun]              # BULGE
aB = 0.4                    # [kpc]                             # BULGE
aH = 6                      # [kpc]                             # HALO (ISO)
mH = 9.94e40/GalMassUnit    # [kg] = 5e10 [Msun]                # HALO (ISO)
mD = 2e41/GalMassUnit       # [kg] = 1e11 [Msun]                # DISC
aD = 6.5                    # [kpc]                             # DISC
bD = 0.26                   # [kpc]                             # DISC 
rhoC = 2.72e37/GalMassUnit  # [kg/kpc^3] = 1.37e7 [Msun/kpc^3]  # CORONA (-Phi)
aC = 7.82                   # [kpc]                             # CORONA (-Phi)    
RCT = 150                   # [kpc]                             # CORONA
Lz = 0.5                    # ANGULAR MOMENTUM

#====================================
#  FUNCTION
#====================================

def f(r,t): 

    #====================================
    #  CONSTANTS
    #====================================

    GalMassUnit = 4.613e37		# [kg] = 2.32 [Msun]
    G = 1                       # UNIVERSAL GRAVITATIONAL CONSTANT
    mB = 5.17e40/GalMassUnit    # [kg] = 2.6e10 [Msun]              # BULGE
    aB = 0.4                    # [kpc]                             # BULGE
    aH = 6                      # [kpc]                             # HALO (ISO)
    mH = 9.94e40/GalMassUnit    # [kg] = 5e10 [Msun]                # HALO (ISO)
    mD = 2e41/GalMassUnit		# [kg] = 1e11 [Msun] 				# DISC
    aD = 6.5					# [kpc]								# DISC
    bD = 0.26					# [kpc]								# DISC 
    rhoC = 2.72e37/GalMassUnit  # [kg/kpc^3] = 1.37e7 [Msun/kpc^3]  # CORONA (-Phi)
    aC = 7.82                   # [kpc]                             # CORONA (-Phi)    
    RCT = 150                   # [kpc]                             # CORONA
    Lz = 0.5                    # ANGULAR MOMENTUM

    #====================================
    #  ELEMENTS IN THE r VECTOR
    #====================================

    R = r[0]                    # POSITION R
    dvR = r[1]                  # VELOCITY R
    Z = r[2]                    # POSITION Z
    dvZ = r[3]                  # VELOCITY Z
    E = r[4]                    # ENERGY
    r = (R**2 + Z**2)**(0.5)

    #====================================
    #  FUNCTION EQUATIONS
    #====================================

    #-- RK FUNCIONS ---------------------
    #-- FOR COMPONENTS AND TOTAL ONE ----

    fvR = dvR 
    fdvRdt = -(G*mD*R/((R**2 + (aD + np.sqrt(Z**2 + bD**2))**2)**(1.5))) - (G*mB*R/(np.sqrt(R**2+Z**2)*(np.sqrt(R**2+Z**2)+aB)**2)) - 4*pi*G*rhoC*aC*(-(aC*R/(R**2+Z**2)**(1.5)) - ((aC**3)*R/((R**2+Z**2)**(1.5)*(R**2+Z**2+aC**2))) + (2*(aC**2)*R*np.arctan(np.sqrt(R**2+Z**2)/aC)/(R**2+Z**2)**2)) - G*mH/aH*((R/(aH**2+R**2+Z**2)) + (aH**2*R/((R**2+Z**2)*(R**2+Z**2+aH**2))) - (aH*R*np.arctan(np.sqrt(R**2+Z**2)/aH)/(R**2+Z**2)**(1.5))) + Lz**2/(R**3)   # BLUE b
#    fdvRdt = -(G*mD*R/((R**2 + (aD + np.sqrt(Z**2 + bD**2))**2)**(1.5))) + Lz**2/(R**3)     # DISC -- N = 15    CYAN c
#    fdvRdt = -(G*mB*R/(np.sqrt(R**2+Z**2)*(np.sqrt(R**2+Z**2)+aB)**2)) + Lz**2/(R**3)      # BULB -- N = 1e6   RED r
#    fdvRdt = -4*pi*G*rhoC*aC*(-(aC*R/(R**2+Z**2)**(1.5)) - ((aC**3)*R/((R**2+Z**2)**(1.5)*(R**2+Z**2+aC**2))) + (2*(aC**2)*R*np.arctan(np.sqrt(R**2+Z**2)/aC)/(R**2+Z**2)**2)) + Lz**2/(R**3)    # CORONA -- N > 1e6   GREEN g
#    fdvRdt = -G*mH/aH*((R/(aH**2+R**2+Z**2)) + (aH**2*R/((R**2+Z**2)*(R**2+Z**2+aH**2))) - (aH*R*np.arctan(np.sqrt(R**2+Z**2)/aH)/(R**2+Z**2)**(1.5))) + Lz**2/(R**3)   # Halo -- N > 1e6  YELLOW y

    fvZ = dvZ
    fdvZdt = -((G*mD*Z*(aD + np.sqrt(Z**2 + bD**2)))/((np.sqrt(Z**2 + bD**2))*((R**2 + (aD + np.sqrt(Z**2 + bD**2))**2)**(1.5)))) - (G*mB*Z/(np.sqrt(R**2+aB**2)*(aB+np.sqrt(R**2+Z**2))**2)) - 4*pi*G*rhoC*aC*(-(aC*Z/(R**2+Z**2)**(1.5)) - (aC**3*Z/((R**2+Z**2)**(1.5)*(R**2+Z**2+aC**2))) + (2*(aC**2)*Z*np.arctan(np.sqrt(R**2+Z**2)/aC)/(R**2+Z**2)**2)) - G*mH/aH*((Z/(aH**2+R**2+Z**2)) + (aH**2*Z/((R**2+Z**2)*(R**2+Z**2+aH**2))) - (aH*Z*np.arctan(np.sqrt(R**2+Z**2)/aH)/(R**2+Z**2)**(1.5)))
#    fdvZdt = -((G*mD*Z*(aD + np.sqrt(Z**2 + bD**2)))/((np.sqrt(Z**2 + bD**2))*((R**2 + (aD + np.sqrt(Z**2 + bD**2))**2)**(1.5))))      # DISC -- N = 15
#    fdvZdt = -(G*mB*Z/(np.sqrt(R**2+aB**2)*(aB+np.sqrt(R**2+Z**2))**2))        # BULB -- N = 1e6
#    fdvZdt = -4*pi*G*rhoC*aC*(-(aC*Z/(R**2+Z**2)**(1.5)) - (aC**3*Z/((R**2+Z**2)**(1.5)*(R**2+Z**2+aC**2))) + (2*(aC**2)*Z*np.arctan(np.sqrt(R**2+Z**2)/aC)/(R**2+Z**2)**2))   # CORONA -- N > 1e6
#    fdvZdt = -G*mH/aH*((Z/(aH**2+R**2+Z**2)) + (aH**2*Z/((R**2+Z**2)*(R**2+Z**2+aH**2))) - (aH*Z*np.arctan(np.sqrt(R**2+Z**2)/aH)/(R**2+Z**2)**(1.5)))  # Halo -- N > 1e6

    #-- POTENTIALS ---------------------

    pB = - G*mB/(np.sqrt(R**2+Z**2) + aB)
    pD = - G*mD/np.sqrt(R**2 + (aD + np.sqrt(Z**2+bD**2))**2)
    pC = 4*pi*G*rhoC*aC*((np.sqrt(R**2+Z**2)/aC - np.arctan(np.sqrt(R**2+Z**2)/aC))/((R**2+Z**2)/(aC**2)))
    pH = G*(mH/aH)*(0.5*np.log(1+((R**2+Z**2)/aH**2)) + (aH/(R**2+Z**2))*np.arctan(np.sqrt(R**2+Z**2)/aH))

    #-- ENERGY DIAGNOSTIC --------------

    E = (0.5)*(dvR**2+dvZ**2) + pB + pD + pC + pH - Lz**2/(R**3)
    dE = np.abs((E-E0)/E0)

    return(np.array([fvR, fdvRdt, fvZ, fdvZdt, dE],float))

#====================================
#  PARAMETERS
#====================================

a = 0           # INITIAL TIME [Gye]
b = 12          # FINAL TIME [Gyr]
N = 1000000     # NUMBER OF ITERATIONS
h = (b-a)/N
time = np.arange(a,b,h)   # TIME ARRAY

#====================================
#  INITIAL PARAMETERS
#====================================

#  (R, velR, Z, velZ, E)
#  E = K+U = 0.5(vR**2 + vZ**2) + pEff

#-- SUN -----------------------------
# R=8 kpc, Vr=10 km/s 
# Z=0 kpc, Vz=7 kpc/s 

#CONFIG 1
#R0 = 8
#vR0 = 1e-8
#Z0 = 0
#vZ0 = 7e-9

#CONFIG 2
#R0 = 1
#vR0 = 0
#Z0 = 0
#vZ0 = 0.3

#CONFIG 3
Rsun = 8.2;
R0 = 8.2/Rsun;
vR0 = 0
Z0 = 0
vZ0 = 0.3


pB0 = - G*mB/(np.sqrt(R0**2+Z0**2) + aB)
pD0 = - G*mD/np.sqrt(R0**2 + (aD + np.sqrt(Z0**2+bD**2))**2)
pC0 = 4*pi*G*rhoC*aC*((np.sqrt(R0**2+Z0**2)/aC - np.arctan(np.sqrt(R0**2+Z0**2)/aC))/((R0**2+Z0**2)/(aC**2)))
pH0 = G*(mH/aH)*(0.5*np.log(1+((R0**2+Z0**2)/aH**2)) + (aH/(R0**2+Z0**2))*np.arctan(np.sqrt(R0**2+Z0**2)/aH))

E0 = np.abs((0.5)*(vR0**2+vZ0**2) + pB0 + pD0 + pC0 + pH0 - Lz**2/(R0**3))

r = np.array([R0, vR0, Z0, vZ0, E0],float) 

#====================================
#  ENERGY DIAGNOSTIC
#====================================


#====================================
#  4TH ORDER RUNGE-KUTTA METHOD
#====================================

Rpositions = [] 
velR = []
Zpositions = []
velZ = []
RpositionsN = [] 
velRN = []
ZpositionsN = []
velZN = []
Energy = []
Steps = []

for t in time: 
    k1=h*f(r,t)
    k2=h*f(r+0.5*k1,t+(h*0.5))
    k3=h*f(r+0.5*k2,t+(h*0.5))
    k4=h*f(r+k3,t+h)
    r+=(1/6)*(k1+2*k2+2*k3+k4)
    Rpositions.append(r[0])     
    velR.append(r[1])
    Zpositions.append(r[2])
    velZ.append(r[3])
    RpositionsN.append(-r[0])     
    velRN.append(-r[1])
    ZpositionsN.append(-r[2])
    velZN.append(-r[3])
    Energy.append(r[4])
    Steps.append(t)
#    print(t)
    print(t)

DiffE = (r[4]-E0)/E0
#print(N,DiffE)             # UNCOMMENT TO PRINT THE ENERGY DIAGNOSTIC FOR THIS N VALUE

#====================================
#  PLOTS
#====================================

#-- DATA FILES ----------------------

#np.savetxt('R-VR-Positive.txt', np.transpose([Rpositions,velR]) , fmt='%.08e', delimiter='\t', newline='\n')
#np.savetxt('R-VR-Negative.txt', np.transpose([RpositionsN,velRN]) , fmt='%.08e', delimiter='\t', newline='\n')
#np.savetxt('Z-VZ-Positive.txt', np.transpose([Zpositions,velZ]) , fmt='%.08e', delimiter='\t', newline='\n')
#np.savetxt('Z-VZ-Negative.txt', np.transpose([ZpositionsN,velZN]) , fmt='%.08e', delimiter='\t', newline='\n')
#np.savetxt('R-Z.txt', np.transpose([Rpositions,Zpositions]) , fmt='%.08e', delimiter='\t', newline='\n')

#-- R-Z PLOT- ----------------------

#plt.plot(Rpositions,Zpositions,'y-')
#plt.xlabel('R [x8.2 kpc]', horizontalalignment='right', x=1.0)
#plt.ylabel('Z [kpc]', horizontalalignment='right', y=1.0)

#-- R-VR PLOT- ----------------------

#plt.plot(Rpositions,velR,'k-')
#plt.plot(RpositionsN,velRN,'k-')
#plt.xlabel('R [kpc]', horizontalalignment='right', x=1.0)
#plt.ylabel('dR/dt [kpc/Gyr]', horizontalalignment='right', y=1.0)

#-- Z-VZ PLOT- ----------------------

plt.plot(Zpositions,velZ,'m-')
plt.plot(ZpositionsN,velZN,'m-')
plt.xlabel('Z [kpc]', horizontalalignment='right', x=1.0)
plt.ylabel('dV/dt [kpc/Gyr]', horizontalalignment='right', y=1.0)

plt.grid(True)
plt.show()

