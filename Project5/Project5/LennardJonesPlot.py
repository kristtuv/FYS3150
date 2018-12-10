from pylab import *

def LennardJones(r,sigma,epsilon):
	return 4*epsilon*((sigma/r)**12 - (sigma/r)**6)

r_values = np.linspace(3.3,20,2000)
epsilon =1# 119.8 # [K]
sigma =3.405# 3.405 # [Angstrom]

potential_values = LennardJones(r_values,sigma,epsilon)



plot(r_values,potential_values/epsilon,label=r'$U(r) = 4\epsilon ((\frac{\sigma}{r})^{12} - (\frac{\sigma}{r})^6)$')
axhline(y=0,color='k')
axvline(x=0,color='k')
grid('on')
legend()
xlabel("r", fontsize = 18)
ylabel(r'$U(r)/\epsilon$',fontsize=18)
savefig("Lennardjones")


show()