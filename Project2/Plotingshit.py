from pylab import *

def get_data(filename):
	infile = open(filename, "r")
	A = [] #Eigenmatrix
	lamda = [] #Eigenvectors

	for line in infile:
		numbers = line.split()
		lamda.append(float(numbers[0]))
		A.append(numbers[1:])
		#for i in range(0, len(numbers), 1):
		#	A.append(float(numbers[1:]))
	infile.close()

	A = array(A, dtype=float)
	Vecs = zeros([len(A[0]), len(A[0])])
	lamda = array(lamda)
	for i in range(0, len(A[0]), 1):

		for j in range(0, len(A[0]), 1):
			Vecs[i, j] = A[j, i]
	
	permute = lamda.argsort()
	lamda = lamda[permute]
	Eigenvectors = Vecs[permute, :]
	print "Lowest eigenvalue: %.10f " % lamda[0]
	return Eigenvectors


def makeProb(filename):
	Eigenvectors = get_data(filename)
	Sqared = square(Eigenvectors)
	
	return Sqared
Eigvec1 = get_data("InteractivecaseW1")
Eigvec2 = get_data("InteractivecaseW2")
Eigvec3 = get_data("InteractivecaseW3")
Eigvec4 = get_data("InteractivecaseW4")

Eigvec12 = get_data("NoninteractingcaseW1")
Eigvec22 = get_data("NoninteractingcaseW2")
Eigvec32 = get_data("NoninteractingcaseW3")
Eigvec42 = get_data("NoninteractingcaseW4")


Sqared1 = makeProb("InteractivecaseW1")
Sqared2 = makeProb("InteractivecaseW2")
Sqared3 = makeProb("InteractivecaseW3")
Sqared4 = makeProb("InteractivecaseW4")



Sqared12 = makeProb("NoninteractingcaseW1")
Sqared22 = makeProb("NoninteractingcaseW2")
Sqared32 = makeProb("NoninteractingcaseW3")
Sqared42 = makeProb("NoninteractingcaseW4")

####
#Ploting probability
####

x1 = linspace(0, 45, 250)
x2 = linspace(0, 7, 250)

figure(1)
plot(x1, Sqared1[0])
#title("$\lambda$ = 0.1058, $\omega$ = 0.01")
hold("on")
plot(x1, Sqared12[0])
ylabel("Probability")
xlabel("Rho")
legend(["Interacting $\lambda= 0.1057 $", "Noninteracting $\lambda= 0.0300$"])
savefig("ProbW001")
hold("off")


figure(2)
plot(x2, Sqared2[0])
#title("$\lambda$ = 2.2301, $\omega$ = 0.5")
hold("on")
plot(x2, Sqared22[0])
ylabel("Probability")
xlabel("Rho")
legend(["Interacting $\lambda= 2.2301 $", "Noninteracting $\lambda= 1.5000$"])
savefig("ProbW05")
hold("off")

figure(3)
plot(x2, Sqared3[0])
#title("$\lambda$ = 0.1058, $\omega$ = 0.01")
hold("on")
plot(x2, Sqared32[0])
ylabel("Probability")
xlabel("Rho")
legend(["Interacting $\lambda= 4.0576 $", "Noninteracting $\lambda= 3.0000$"])
savefig("ProbW1")
hold("off")

figure(4)
plot(x2, Sqared4[0])
#title("$\lambda$ = 0.1058, $\omega$ = 0.01")
hold("on")
plot(x2, Sqared42[0])
ylabel("Probability")
xlabel("Rho")
legend(["Interacting $\lambda= 17.4423 $", "Noninteracting $\lambda= 14.9940$"])
savefig("ProbW5")
hold("off")



####
#Ploting wavefunction
####

figure(5)
plot(x1, Eigvec1[0])
hold("on")
plot(x1, Eigvec12[0])
xlabel("Rho")
legend(["Interacting $\lambda= 0.1057 $", "Noninteracting $\lambda= 0.0300$"])
savefig("W001")
hold("off")

figure(6)
plot(x2, Eigvec2[0])
hold("on")
plot(x2, Eigvec22[0])
xlabel("Rho")
legend(["Interacting $\lambda= 2.2301 $", "Noninteracting $\lambda= 1.5000$"])
savefig("W05")
hold("off")

figure(7)
plot(x2, Eigvec3[0])
hold("on")
plot(x2, Eigvec32[0])
xlabel("Rho")
legend(["Interacting $\lambda= 4.0576 $", "Noninteracting $\lambda= 3.0000$"])
savefig("W1")
hold("off")

figure(8)
plot(x2, Eigvec4[0])
hold("on")
plot(x2, Eigvec42[0])
xlabel("Rho")
legend(["Interacting $\lambda= 17.4423 $", "Noninteracting $\lambda= 14.9940$"])
savefig("W5")
hold("off")



show()

