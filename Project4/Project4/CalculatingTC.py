from pylab import *
L = [40, 60, 100, 140]
T = [2.285, 2.280, 2.275, 2.275]
a = []
b = zip(L, T)

for i in range(0, len(T)-1):
	for j in range(i+1, len(T)):
		
		a.append( float(T[i] - T[j])/(1./L[i] - 1./L[j]))

#print sum(a)/len(a)
print a
print sum(a)/len(a)
Tinfty = -sum(a)/len(a) *1./L[1] + 2.280;
print Tinfty