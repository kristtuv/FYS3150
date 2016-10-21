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
def plot(filename):
	x, y = get_data(filename)
	plot(x, y)
	show()

plot("positionsTimesteps1000Euler")

