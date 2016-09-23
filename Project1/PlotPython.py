from pylab import *
def extractdata(filename, PowerOfN):
	filename = str(filename) + str(PowerOfN)
	infile = open(filename, "r")
	xx = []
	approxx = []	
	exactx = []
	errx = []
	for line in infile:
		numbers = line.split()
		x = float(numbers[0])
		xx.append(x)
		approx = float(numbers[1])
		approxx.append(approx)
		exact = float(numbers[2])
		exactx.append(exact)
		err = float(numbers[3])
		errx.append(err)
	infile.close()
	return xx, approxx, exactx, errx


for i in range(1, 6):
	PowerOfN = i
	filename1 = "GeneralAlgorithm"
	
	values = extractdata(filename1, PowerOfN)

	
	figure(1)


	title("1D Poisson equation, n = %d, %s" % (10**(PowerOfN), filename1))
	plot(values[0], values[1], 'b-')
	plot(values[0], values[2], 'r-')

	legend(["Nummerical solution", "Exact solution"])
	xlabel("x-values")
	ylabel("u-values")

	savefig('%s%d' % (filename1, PowerOfN))

	figure(2)
	title("Logarithmic Relative error, n =%d, %s" % (10**(PowerOfN), filename1))
	plot(values[0], values[3])
	xlabel("x-values")
	ylabel("Log10(Rel.Error)")
	savefig('LogaErr%d %s' % (PowerOfN, filename1))
	show()

