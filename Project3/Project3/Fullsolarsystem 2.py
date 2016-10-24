from pylab import *

def get_data(filename):
	x1 = []
	y1 = []
	x2 = []
	y2 = []
	x3 = []
	y3 = []
	x4 = []
	y4 = []
	x5 = []
	y5 = []
	x6 = []
	y6 = []
	x7 = []
	y7 = []
	x8 = []
	y8 = []
	x9 = []
	y9 = []
	infile = open(filename, "r")
	for line in infile:
		numbers = line.split()
		x1.append(numbers[0])
		y1.append(numbers[1])
		x2.append(numbers[2])
		y2.append(numbers[3])
		x3.append(numbers[4])
		y3.append(numbers[5])
		x4.append(numbers[6])
		y4.append(numbers[7])
		x5.append(numbers[8])
		y5.append(numbers[9])
		x6.append(numbers[10])
		y6.append(numbers[11])
		x7.append(numbers[12])
		y7.append(numbers[13])
		x8.append(numbers[14])
		y8.append(numbers[15])
		x9.append(numbers[16])
		y9.append(numbers[17])

	return 	array(x1), array(y1), array(x2), array(y2)\
		,array(x3), array(y3), array(x4), array(y4)\
		,array(x5), array(y5), array(x6), array(y6)\
		,array(x7), array(y7), array(x8), array(y8)\
		,array(x9), array(y9)

def plotting(filename):
	x, y = get_data(filename)
	x1, y1, x2, y2, x3, y3, x4, y4, x5, y5, x6, y6, x7, y7, x8, y8, x9, y9 = get_data(filename)
	figure(1)
	plot(x1, y1)
	plot(x2, y2)
	plot(x3, y3)
	plot(x4, y4)

	#figure(2)
	plot(x5, y5)
	plot(x6, y6)
	plot(x7, y7)
	plot(x8, y8)
	plot(x9, y9)

plotting("FullSolarSystem")



