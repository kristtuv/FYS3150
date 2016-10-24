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
	
def plottingEarth(filename):
	x, y = get_data(filename)

	return plot(x[: len(x)/10], y[:len(x)/10])

def printerror(filename):
	x, y = get_data(filename)
	timesteps = len(x)
	exact = 1.0; #Circular orbit, distance to the sun
	relError = zeros(timesteps)
	for i in range(timesteps):
		simulateddistance = sqrt(float(x[i])**2 + float(y[i])**2)

		relError[i] = abs((simulateddistance - exact)/exact)
	return relError

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
			"positionsTimesteps50000Euler", "positionsTimesteps100000Euler",
			"positionsTimesteps1000000Euler", "positionsTimesteps5000000Euler"]

filenamesVerlet = ["positionsTimesteps1000Verlet", "positionsTimesteps10000Verlet", 
			"positionsTimesteps50000Verlet", "positionsTimesteps100000Verlet",
			"positionsTimesteps1000000Verlet", "positionsTimesteps5000000Verlet"]

filenamesEarth = ["positionsTimesteps1000Earth", "positionsTimesteps10000Earth", 
			"positionsTimesteps50000Earth", "positionsTimesteps100000Earth",
			"positionsTimesteps1000000Earth"]

filenamesJupiter = ["positionsTimesteps1000Jupiter", "positionsTimesteps10000Jupiter", 
			"positionsTimesteps50000Jupiter", "positionsTimesteps100000Jupiter",
			"positionsTimesteps1000000Jupiter"]

filenamesEarthReal = ["positionsTimesteps1000EarthReal", "positionsTimesteps10000EarthReal", 
			"positionsTimesteps50000EarthReal", "positionsTimesteps100000EarthReal",
			"positionsTimesteps1000000EarthReal"]

filenamesJupiterReal = ["positionsTimesteps1000JupiterReal", "positionsTimesteps10000JupiterReal", 
			"positionsTimesteps50000JupiterReal", "positionsTimesteps100000JupiterReal",
			"positionsTimesteps1000000JupiterReal"]

timesteps = [1000, 10000, 50000, 100000, 1000000, 5000000]
#plotting("positionsTimesteps50000000Verlet")
#xlabel("AU")
#ylabel("AU")
#show()

for i in range(0, 5, 1):
	figure(i)
	
	plotting(filenamesJupiterReal[i])
	plottingEarth(filenamesEarthReal[i])
	legend(["Jupiter", "Earth"])
	xlabel("AU")
	ylabel("AU")
	savefig("Mass1JRER" + str(timesteps[i]))
	show()
	figure(i+5)

	plottingEarth(filenamesEarth[i])
	plotting(filenamesJupiter[i])
	#title(str(timesteps[i]) + " timesteps")
	#legend(["EarthReal", "Earth"])
	legend(["Earth", "Jupiter"])
	xlabel("AU")
	ylabel("AU")
	savefig("Mass1JE" + str(timesteps[i]))
	
	show()


exit(1)
for i in range(4, 5, 1):
	figure(i+6)
	axes = gca()

	plot(printerror(filenamesEuler[i]))
	hold("on")
	plot(printerror(filenamesVerlet[i]))
	title(str(timesteps[i]) + " timesteps")
	legend(["Euler", "Verlet"])
	axes.set_ylim([-0.6*max(printerror(filenamesEuler[i])), max(printerror(filenamesEuler[0]))])
	xlabel("Timesteps")
	ylabel("Relative Error")
	savefig("Relativeerror" + str(timesteps[i]))
	hold("off")

	


