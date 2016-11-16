from pylab import *

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
			E40.append(numbers[3])
			Cv40.append(numbers[4])
			Chi40.append(numbers[6])
			M40.append(numbers[7])

		elif float(numbers[1]) == 60:
			E60.append(numbers[3])
			Cv60.append(numbers[4])
			Chi60.append(numbers[6])
			M60.append(numbers[7]) 

		elif float(numbers[1]) == 100:
			E100.append(numbers[3])
			Cv100.append(numbers[4])
			Chi100.append(numbers[6])
			M100.append(numbers[7]) 

		elif float(numbers[1]) == 140:
			E140.append(numbers[3])
			Cv140.append(numbers[4])
			Chi140.append(numbers[6])
			M140.append(numbers[7]) 



	kulio = open(filnavn, "r")
	for line in kulio:
		numbers = line.split()
		if float(numbers[1]) == 40:
			T.append(numbers[2])
			E40.append(numbers[3])
			Cv40.append(numbers[4])
			Chi40.append(numbers[6])
			M40.append(numbers[7])

		elif float(numbers[1]) == 60:
			E60.append(numbers[3])
			Cv60.append(numbers[4])
			Chi60.append(numbers[6])
			M60.append(numbers[7]) 

		elif float(numbers[1]) == 100:
			E100.append(numbers[3])
			Cv100.append(numbers[4])
			Chi100.append(numbers[6])
			M100.append(numbers[7]) 

		elif float(numbers[1]) == 140:
			E140.append(numbers[3])
			Cv140.append(numbers[4])
			Chi140.append(numbers[6])
			M140.append(numbers[7]) 
	return T,E40 , E60 , E100, E140, Cv40 , Cv60 , Cv100, Cv140, Chi40, Chi60, Chi100, Chi140, M40 , M60 , M100, M140



T,E40 , E60 , E100, E140, Cv40 , Cv60 , Cv100, Cv140, Chi40, Chi60, Chi100, Chi140, M40 , M60 , M100, M140 = get_data("LongInterval", "ShortInterval")

###
#Ploting Cv
###
figure(1)
plot(T, Cv40)
plot(T, Cv60)
plot(T, Cv100)
plot(T, Cv140)
plot([2.269, 2.269], [0, 3])
legend(["40x40", "60x60", "100x100", "140x140", "Onsager exact"], loc=0)
xlabel(r"$k_bT$", size=20, labelpad=3)
ylabel(r"$\frac{C_v}{Jk_b}$", size=24, rotation=0, labelpad=20)
savefig("Cv")
########################

###
#Ploting E
###
figure(2)
axes = gca()
plot(T, E40)
plot(T, E60)
plot(T, E100)
plot(T, E140)
plot([2.269, 2.269], [-2, -1])
axes.set_ylim([-2, -1])
legend(["40x40", "60x60", "100x100", "140x140", "Onsager exact"], loc=0)
xlabel(r"$k_bT$", size=20, labelpad=3)
ylabel(r"$\frac{E}{J}$", size=24, rotation=0, labelpad=20)
savefig("E")

###
#Ploting M
###
figure(3)
axes = gca()
plot(T, M40)
plot(T, M60)
plot(T, M100)
plot(T, M140)
plot([2.269, 2.269], [0, 1])
#axes.set_ylim([0, 1.4])
legend(["40x40", "60x60", "100x100", "140x140", "Onsager exact"], loc=0)
xlabel(r"$k_bT$", size=20, labelpad=3)
ylabel(r"$<|M|>$", size=20, labelpad=10)
savefig("M")

###
#Ploting Chi
###
figure(4)
axes = gca()
plot(T, Chi40)
plot(T, Chi60)
plot(T, Chi100)
plot(T, Chi140)
plot([2.269, 2.269],[0, 300])
#axes.set_ylim([0, 1.4])
legend(["40x40", "60x60", "100x100", "140x140", "Onsager exact"], loc=0)
xlabel(r"$k_bT$", size=20, labelpad=3)
ylabel(r"$\chi$", size=24, rotation=0, labelpad=10)
savefig("Chi")
show()
