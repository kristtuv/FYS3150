from pylab import *

def get_data(filename):
	#MCc, T, <E>, Cv, <M>, Xi, <|M|>
	MCc1 = []
	E1 = []
	Cv1 = []
	Xi1 = []
	M1 = []

	MCc2 = []
	E2 = []
	Cv2 = []
	Xi2 = []
	M2 = []

	infile = open(filename, "r")
	for line in infile:
		numbers = line.split()
		if numbers[1] == 1.0:
			MCc1.append(numbers[0])		
			E1.append(numbers[2])
			Cv1.append(numbers[3])
			Xi1.append(numbers[5])
			M1.append(numbers[6])

		else:
			MCc2.append(numbers[0])		
			E2.append(numbers[2])
			Cv2.append(numbers[3])
			Xi2.append(numbers[5])
			M2.append(numbers[6])
	return array(MCc1), array(E1), array(Cv1), array(Xi1), array(M1),\
			array(MCc2), array(E2), array(Cv2), array(Xi2), array(M2) 


def plotting(filename):
	MCc1, E1,Cv1, Xi1, M1, MCc2, E2 , Cv2, Xi2, M2 = get_data(filename)
	print size(get_data(filename))
	


plotting("Lattice2")







exit()

values = [-1.9967000 ,-1.9971200 , -1.9971180,-1.9971346 , -1.9971550]
Mc = [100, 1000, 10000, 100000, 1000000]

plot(Mc, values, "r-o")
show()