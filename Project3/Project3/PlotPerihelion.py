from pylab import *

def get_data(filename):
	x = []
	
	infile = open(filename, "r")
	for line in infile:
		numbers = line.split()
		x.append(numbers[0])
		
	return array(x)
def plotting(filename):
	x = get_data(filename)

	return plot(x)
x = get_data("PerihelionAngleRelativistic")
print x[-3]
print x[0]
print (float(x[-1]) - float(x[0]))
exit(1)
figure(1)

plotting("PerihelionAngle")
plotting("PerihelionAngleRelativistic")
legend(["Without relativistic correction", "With relativistic correction"], 0)
xlabel("Mercur-years")
ylabel("Arcseconds")
savefig("PerihelionAngle")
show()

