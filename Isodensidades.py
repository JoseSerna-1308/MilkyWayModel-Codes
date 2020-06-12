import matplotlib
import numpy as np
import matplotlib.cm as cm 
import matplotlib.pyplot as plt

# M. Osorio & J. Serna. 2020. 
# jmosorio@astro.unam.mx
# j_serna@ciencias.unam.mx

delta = 1
x = np.arange( 0, 30.0, delta) 
y = np.arange(-20.0, 20.0, delta) 

############################
#  CONSTANTS
############################

GalMassUnit = 4.613e37		# [kg] = 2.32 [Msun]

aH = 16.1					# [kpc]								# HALO (NFW)
rhoH = 2.78e37/GalMassUnit	# [kg/kpc^3] = 1.4e7 [Msun/kpc^3]	# HALO (NFW)
aH = 6.0					# [kpc]							# HALO Pseudo-Isothermic sphere
rhoH = 3.68e37/GalMassUnit	# [kg/kpc^3]=1.8e7 [Msun/kpc^3] # HALO Pseudo-Isothermic sphere
mD = 2e41/GalMassUnit		# [kg] = 1e11 [Msun] 				# DISC
aD = 6.5					# [kpc]								# DISC
bD = 0.26					# [kpc]								# DISC 
mB = 5.17e40/GalMassUnit	# [kg] = 2.6e10 Msun				# BULGE
aB = 0.4					# [kpc]								# BULGE
# rhoC = 1.44e37/GalMassUnit 	# [kg/kpc^3] = 7.25e6 [Msun/kpc^3]	# CORONA (Phi')
# aC = 80						# [kpc]								# CORONA (Phi')
rhoC = 2.72e37/GalMassUnit 	# [kg/kpc^3] = 1.37e7 [Msun/kpc^3] 	# CORONA (-Phi)
aC = 7.82;					# [kpc]								# CORONA (-Phi)	
mZ = 8.95e39/GalMassUnit	# [kg] = 4.5e9 [Msun] 				# CORE
aZ = 0.0					# [kpc]								# CORE
bZ = 0.25					# [kpc]								# CORE 

X, Y = np.meshgrid(x, y)	# X = r; Y = z


############################
# DENSITIES
############################

#------ TRANSFORMATION-------------------
#------ ESPH <-> CILIND -----------------

R = (X**2 + Y**2)**(0.5)

#------ FUNCTIONS -----------------------
#------ HALO ----------------------------

#dH = rhoH*((aH**3)/R)*(aH+R)**(-2) 	# HALO (NFW)
dH = (rhoH/(1 + (R**2/aH**2)))

#------ DISC ----------------------------

dD = (bD**2)*(mD/(4*(3.1416)))*((aD*(X**2))+(aD + 3*(((Y**2)+(bD**2))**(0.5)))*(aD + ((Y**2)+(bD**2))**(0.5))**2) *(X**2+(aD+((Y**2)+(bD**2))**(0.5))**2)**(-5/2)*((Y**2)+(bD**2))**(-3/2)

#------ BULGE ---------------------------

dB = ((aB*mB)/(2*(3.1416)*(R+15)))*(R+aB)**(-3)			# WITHOUT INDETERMINATION
#	dB = ((aB*mB)/(2*(3.1416)*(R)))*(R+aB)**(-3)		# WITH INDETERMINATION

#------ CORONA --------------------------

# dC = (rhoC/(R**3))*(aC**2)*((2*aC*(R**2))/((R**2 + aC**2)**2) - (1/R)*(np.arctan(R/aC) - (aC*R)/(R**2 + aC**2)))		# THROUGH POISSON
dC = rhoC/(1+(R/aC)**2)

#------ CORE ----------------------------

# dZ = (bZ**2)*(mZ/(4*(3.1416)))*((aZ*(X**2))+(aZ + 3*(((Y**2)+(bZ**2))**(0.5)))*(aZ + ((Y**2)+(bZ**2))**(0.5))**2) *(X**2+(aZ+((Y**2)+(bZ**2))**(0.5))**2)**(-5/2)*((Y**2)+(bZ**2))**(-3/2)

#------ TOTAL ---------------------------

dT = dH + dD + dB + dC

############################
# PLOT
############################

matplotlib.rcParams['contour.negative_linestyle'] = 'solid' 
fig, ax = plt.subplots()
CS = ax.contour(X, Y, dT, 1000,
cmap=plt.cm.Spectral,
#colors='b', # negative contours will be dashed by default
)

#ax.set_title('ISODENSITIES FOR THE MILKY WAY') 
plt.xlabel('r [kpc]')
plt.ylabel('z [kpc]')
plt.grid(True)
plt.show()
