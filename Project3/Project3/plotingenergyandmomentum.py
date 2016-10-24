from pylab import *

def get_data(filename):
	p_energy = []
	k_energy = []
	a_momentum = []
	infile = open(filename, "r")
	for line in infile:
		numbers = line.split()
		p_energy.append(numbers[0])
		k_energy.append(numbers[1])
		a_momentum.append(numbers[2])
	return array(p_energy), array(k_energy), array(a_momentum)
def plotting(filename):
	x, y, z = get_data(filename)

	plot(x)

	return plot(x, y)

x, y, z = get_data("EnergyAndMomentumEuler")
a, b, c = get_data("EnergyAndMomentumVerlet")


"""figure(7)
plot(x)
plot(y)
plot(z)
figure(8)
plot(a)
plot(b)
plot(c)
show()
exit(1)
figure(1)
plot(x)
xlabel("Timesteps")
ylabel("Energy")
figure(2)
plot(y)
xlabel("Timesteps")
ylabel("Energy")
figure(3)
plot(z)
xlabel("Timesteps")
ylabel("Angular momentum")"""


subplot(3, 1 , 1)
axes = gca()
plot(a)
title("Potential energy")
axes.set_ylim([0.9999*float(min(a)), 1.0001*float(max(a))])
xlabel("Timesteps")
ylabel("$kg AU^2/yr^2$")

subplot(3, 1, 2)

plot(b)
title("Kinetic energy")
axes = gca()
axes.set_ylim([0.9999*float(min(b)), 1.0001*float(max(b))])
xlabel("Timesteps")
ylabel("$kg AU^2/yr^2$")

subplot(3, 1, 3)
axes = gca()
plot(c)
title("Angularmomentum")
axes.set_ylim([0.9999*float(min(c)), 1.0001*float(max(c))])
xlabel("Timesteps")
ylabel("$kg AU^2/yr$")

tight_layout()
show()
savefig("ConservationofEandM")