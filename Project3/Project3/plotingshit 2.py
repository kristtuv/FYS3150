from pylab import *

def get_data(filename):
	x = []
	y = []
	infile = open(filename, "r")
	for line in infile:
		numbers = line.split()
		x.append(numbers[0])
		y.append(numbers[1])
	return array(x), array(y)
def plotting(filename):
	x, y = get_data(filename)

	return plot(x, y)
	

def printerror(filename):
	x, y = get_data(filename)
	timesteps = len(x)
	exact = 1.0; #Circular orbit, distance to the sun
	simulateddistance = sqrt(float(x[-1])**2 + float(y[-1])**2)
	relError = abs((simulateddistance - exact)/exact)
	print "RelativeError " + str(timesteps) + " timesteps:" , relError

"""figure(1)
title("Earth")
plotting("positionsTimesteps1000000Earth")
plotting("positionsTimesteps1000000EarthReal")
legend(["Sun center of mass", "Real center of mass"])


figure(2)
title("Jupiter")
plotting("positionsTimesteps1000000Jupiter")
plotting("positionsTimesteps1000000JupiterReal")
legend(["Sun center of mass", "Real center of mass"])

figure(3)
plotting("PerihelionAngle")

show()
"""
filenamesEuler = ["positionsTimesteps1000Euler", "positionsTimesteps10000Euler", 
			"positionsTimesteps50000Euler", "positionsTimesteps100000Euler"
			"positionsTimesteps1000000Euler", "positionsTimesteps5000000Euler"]

filenamesVerlet = ["positionsTimesteps1000Verlet", "positionsTimesteps10000Verlet", 
			"positionsTimesteps50000Verlet", "positionsTimesteps100000Verlet"
			"positionsTimesteps1000000Verlet", "positionsTimesteps5000000Verlet"]

filenamesEarth = ["positionsTimesteps1000Earth", "positionsTimesteps10000Earth", 
			"positionsTimesteps50000Earth", "positionsTimesteps100000Earth"
			"positionsTimesteps1000000Earth"]

filenamesJupiter = ["positionsTimesteps1000Jupiter", "positionsTimesteps10000Jupiter", 
			"positionsTimesteps50000Jupiter", "positionsTimesteps100000Jupiter"
			"positionsTimesteps1000000Jupiter"]


for i in range(0, 5, 1):
	figure(i)
	plotting(filenamesJupiter[i])
	hold("on")
	plotting(filenamesEarth[i])
	hold("off")


#printerror("positionsTimesteps10000000Euler")

