from pylab import *



def get_data(filename):
	infile = open(filename, "r")
	EnergyT1 = []
	EnergyT2 = []
	for line in infile:
		numbers = line.split()
		if float(numbers[0]) == 1.0000000:
			EnergyT1.append(float(numbers[1]))
		if float(numbers[0]) == 2.4000000:
			EnergyT2.append(float(numbers[1]))
	return EnergyT1, EnergyT2
Energies = linspace(-800, 800, 401)
T1, T2 = get_data("CountingEnergies")

print Energies