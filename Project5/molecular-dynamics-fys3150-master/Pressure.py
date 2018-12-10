from pylab import *
import numpy
from matplotlib import pyplot

#Pa = kg/m s^2

gamma = 5.26e-10 # m
kb = 1.3806e-23 #m^2 kg / s^2 K


a = 1.355*0.1/(6.022**2)*10**(-52) #Pa m^6
b = 0.03201/(10**3*6022*10**26) # m^3
T = linspace(0, 2000, 2001)
#T = 600 
#P = (4*kb*T/(gamma**3 - 4*b) - 16*a/(gamma**6))
#print P
#exit()

P = [(4*kb*t/(gamma**3 - 4*b) - 16*a/(gamma**6))/10**9 for t in T] #Giga Pascal
fig = figure(1)
axes = gca()
ax = fig.add_subplot(111)
plot(T, P)
plot([0,300, 300], [P[300],P[300], 0])
plot([0,600, 600], [P[600],P[600], 0])
plot([0,900, 900], [P[900],P[900], 0])
plot([0,1200, 1200], [P[1200],P[1200], 0])
ax.annotate(str(round(P[300],2)) + "GPa",xy=(90,P[320]))
ax.annotate(str(round(P[600],2)) + "GPa",xy=(300,P[620]))
ax.annotate(str(round(P[900],2)) + "GPa",xy=(600,P[920]))
ax.annotate(str(round(P[1200],2)) + "GPa",xy=(900,P[1220]))
xlabel("Temperature [K]")
ylabel("Pressure [GPa]")
legend(["Pressure", "T = 300", "T = 600", "T = 900", "T = 1200"])
axes.set_ylim(0, 1)
savefig("PressureVanderWaals")
show()
