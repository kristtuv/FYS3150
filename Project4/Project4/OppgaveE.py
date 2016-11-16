from pylab import *

#T = [2.0000000, 2.0200000, 2.0400000, 2.0600000, 2.0800000, 2.1000000, 2.1200000, 2.1400000, 2.1600000, 2.1800000, 2.2000000, 2.2200000, 2.2400000, 2.2450000, 2.2500000, 2.2550000, 2.2600000, 2.2650000, 2.2700000, 2.2750000, 2.2800000, 2.2850000, 2.2900000, 2.2950000, 2.3000000, 2.3050000, 2.3100000, 2.3150000, 2.3200000]
#Cv = [0.73887409, 0.76639349, 0.87751784, 0.85616138, 0.90486258, 0.96142160,  1.0305038,  1.1001856,  1.1848050,  1.2818649,  1.4133993,  1.5835510, 1.8210444, 1.8998721, 2.2065573, 2.1405000, 2.4102672, 2.4245702, 2.6066572, 2.5860198, 2.6184734, 2.4893054, 2.3086965, 2.1317311, 1.9869159, 1.8547385, 1.7703133, 1.6894982, 1.5934405]
#plot(T, Cv, "r-o")
##axes = gca()
##axes.set_ylim([0, 4])
##axes.set_xlim([1.6, 2.6])
#show()
#exit()
def get_data(filename, filnavn):
	#MCc, T, <E>, Cv, <M>, Xi, <|M|>
	
	T = []

	E40 	= []
	E60 	= []
	E100	 = []
	E140	 = []

	Cv40 	= []
	Cv60 	= []
	Cv100	 = []
	Cv140	 = []

	Chi40 	= []
	Chi60 	= []
	Chi100	 = []
	Chi140	 = []

	M40 	= []
	M60 	= []
	M100	 = []
	M140	 = []

	infile = open(filename, "r")
	for line in infile:
		numbers = line.split()
		if float(numbers[1]) == 40:
			T.append(numbers[2])
			E40.append[numbers[3]]
			Cv40.append[numbers[4]]
			Chi40.append[numbers[6]]
			M40.append[numbers[7]]

		elif float(numbers[1]) == 60:
			E60.append[numbers[3]]
			Cv60.append[numbers[4]]
			Chi60.append[numbers[6]]
			M60.append[numbers[7]]

		elif float(numbers[1]) == 100:
			E100.append[numbers[3]]
			Cv100.append[numbers[4]]
			Chi100.append[numbers[6]]
			M100.append[numbers[7]]

		elif float(numbers[1]) == 140:
			E100.append[numbers[3]]
			Cv100.append[numbers[4]]
			Chi100.append[numbers[6]]
			M100.append[numbers[7]]



	infile = open(filnavn, "r")
	for line in infile:
		numbers = line.split()
		if float(numbers[1]) == 40:
			T.append(numbers[2])
			E40.append[numbers[3]]
			Cv40.append[numbers[4]]
			Chi40.append[numbers[6]]
			M40.append[numbers[7]]

		elif float(numbers[1]) == 60:
			E60.append[numbers[3]]
			Cv60.append[numbers[4]]
			Chi60.append[numbers[6]]
			M60.append[numbers[7]]

		elif float(numbers[1]) == 100:
			E100.append[numbers[3]]
			Cv100.append[numbers[4]]
			Chi100.append[numbers[6]]
			M100.append[numbers[7]]

		elif float(numbers[1]) == 140:
			E100.append[numbers[3]]
			Cv100.append[numbers[4]]
			Chi100.append[numbers[6]]
			M100.append[numbers[7]]
	return T,E40 , E60 , E100, E140, Cv40 , Cv60 , Cv100, Cv140, Chi40, Chi60, Chi10, Chi14, M40 , M60 , M100, M140



T,E40 , E60 , E100, E140, Cv40 , Cv60 , Cv100, Cv140, Chi40, Chi60, Chi10, Chi14, M40 , M60 , M100, M140 = get_data("LongInterval", "ShortInterval")









exit()

values = [-1.9967000 ,-1.9971200 , -1.9971180,-1.9971346 , -1.9971550]
Mc = [100, 1000, 10000, 100000, 1000000]

plot(Mc, values, "r-o")
show()