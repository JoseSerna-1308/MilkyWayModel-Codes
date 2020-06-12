import matplotlib
import numpy as np
import matplotlib.cm as cm 
import matplotlib.pyplot as plt

# M. Osorio & J. Serna. 2020. 
# jmosorio@astro.unam.mx
# j_serna@ciencias.unam.mx

delta = 0.025
x = np.arange(-0.0, 30.0, delta) 
y = np.arange(-20.0, 20.0, delta) 

############################
#  CONSTANTS
############################

GalMassUnit = 4.613e37		# [kg] = 2.32 [Msun]

#aH = 16.1					# [kpc]								# HALO (NFW)
#rhoH = 2.78e37/GalMassUnit	# [kg/kpc^3] = 1.4e7 [Msun/kpc^3]	# HALO (NFW)
aH = 6.0					# [kpc]								# HALO (ISO)
rhoH = 3.68e37/GalMassUnit	# [kg/kpc^3] = 1.8e7 [Msun/kpc^3] 	# HALO (ISO)
mH = 9.94e40/GalMassUnit	# [kg] = 5e10 [Msun]				# HALO (ISO)
mD = 2e41/GalMassUnit		# [kg] = 1e11 [Msun] 				# DISC
aD = 6.5					# [kpc]								# DISC
bD = 0.26					# [kpc]								# DISC 
mB = 5.17e40/GalMassUnit	# [kg] = 2.6e10 Msun				# BULGE
aB = 0.4					# [kpc]								# BULGE
# rhoC = 1.44e37/GalMassUnit 	# [kg/kpc^3] = 7.25e6 [Msun/kpc^3]	# CORONA (Phi')
# aC = 80						# [kpc]								# CORONA (Phi')
rhoC = 2.72e37/GalMassUnit 	# [kg/kpc^3] = 1.37e7 [Msun/kpc^3] 	# CORONA (-Phi)
aC = 7.82					# [kpc]								# CORONA (-Phi)		
mZ = 8.95e39/GalMassUnit	# [kg] = 4.5e9 [Msun] 				# CORE
aZ = 0.0					# [kpc]								# CORE
bZ = 0.25					# [kpc]								# CORE 	

X, Y = np.meshgrid(x, y)	# X = r; Y = z


############################
# POTENCIALS
############################

# Potentials normalized to G=1

#------ TRANSFORMATION-------------------
#------ ESPH <-> CILIND -----------------

R = (X**2 + Y**2)**(0.5)

#------ FUNCTIONS -----------------------
#------ HALO ----------------------------

#pH = -4*(3.1415)*rhoH*(np.log(1 + (R/aH)))*(aH**2)*(aH/R)		# HALO (NFW)
pH = (mH/aH)*(0.5*np.log(1+(R/aH)**2)+(aH/R)*np.arctan(R/aH))

#------ DISC ----------------------------

pD = -mD*((X**2)+(aD + ((Y**2) + (bD**2))**(0.5))**2)**(-0.5)

#------ BULGE ---------------------------

pB = -mB/(R+aB)

#------ CORONA --------------------------

#pC = 4*(3.1416)*rhoC*aC*(((R/aC) - np.arctan(R/aC))/(R/aC))
pC = -4*(3.1415)*rhoC*(aC**2)*(1+np.log(((1+(150/aC)**2)/(1+(R/aC)**2))**(0.5))-((np.arctan(R/aC))/(R/aC)))

#------ CORE ----------------------------

# pZ = -mZ*((X**2)+(aZ + ((Y**2) + (bZ**2))**(0.5))**2)**(-0.5)

#------ TOTAL ---------------------------

pT = pH + pD + pB + pC


############################
# PLOT
############################

matplotlib.rcParams['contour.negative_linestyle'] = 'solid' 
fig, ax = plt.subplots()
CS = ax.contour(X, Y, pT, 500,
cmap=plt.cm.Spectral,
#colors='b', # negative contours will be dashed by default
)

#ax.set_title('EQUIPOTENTIALS FOR THE MILKY WAY') 
plt.xlabel('r [kpc]')
plt.ylabel('z [kpc]')
plt.grid(True)
plt.show()










