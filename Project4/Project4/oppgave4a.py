"""

2x2 lattice with T = 1.0

"""
from pylab import *

beta = 1.0
J = 1.0

exponent = beta*J

E = (-8*exp(8) + 8*exp(-8))/(exp(8)+ exp(-8)+ 6)

sigma2E = 64*(6*exp(8) + 6*exp(-8) + 4)/((exp(8) + exp(-8) + 6)**2)

sigma2M = 16*(3*exp(8*exponent) + exp(-8*exponent) + 3)/((exp(8*exponent) + exp(-8*exponent) + 6 )**2)

M = 4*(exp(8*exponent) + 2)/(exp(8*exponent) + exp(-8*exponent) + 6)
E = E*0.25
sigma2E = sigma2E*0.25
sigma2M = sigma2M*0.25
M = M*0.25

print ("E = %f , sigmaE = %f , sigmaM = %f, M = %f " % (E, sigma2E, sigma2M, M))

"""
Results from c++ program with 10^8 mtc:
(-1.9959789 ,0.032108924 ,0.0039958766 ,0.99866270)
"""

T = [1.0, 2.4]
deltaE = [-8, -4, 0, 4, 8]

for t in T:
	for E in deltaE:
		w = exp(-1./t * E)
		print ("T = %f  deltaE = %f  Probability= %f " % (t, E, w))



