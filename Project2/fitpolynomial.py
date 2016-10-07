from numpy import *
from matplotlib.pyplot import *
#Size of square-matrices
x = array([10, 50, 100, 150, 200])
#Iterations to make all non diagonals
#close to zero
y = array([128, 3956, 16239, 36917, 65900])
z = polyfit(x, y, 2)
print z
plot(x,y, 'ro')
y = z[0]*x**2 + z[1]*x + z[2]
hold('on')
plot(x,y)
xlabel("N")
ylabel("Iterations")
legend(["Measured points", "Polyfit"])
hold("off")
savefig("Polyfit")
show()