import os
import numpy as np
import matplotlib.pyplot as plt

data = np.loadtxt("Clase_28.dat")


plt.figure(1) 
plt.plot(data[:,1], data[:,3],label=(""))
plt.xlabel('X')
plt.ylabel('Y')
plt.savefig("grafica.png")