import os
import numpy as np
import matplotlib.pyplot as plt

data = np.loadtxt("Clase_28.dat")
data1 = data[0:403]
data2 = data[404:4405]
data3 = data[4406:4447]
data4 = data[4448:4849]
data5 = data[4850:8851]
data6 = data[8852:8893]

plt.figure(1) 
plt.plot(data1[:,0], data1[:,1],label=(""))
plt.plot(data2[:,0], data2[:,1],label=(""))
plt.plot(data3[:,0], data3[:,1],label=(""))
plt.plot(data4[:,0], data4[:,1],label=(""))
plt.plot(data5[:,0], data5[:,1],label=(""))
plt.plot(data6[:,0], data6[:,1],label=(""))
plt.xlabel('X')
plt.ylabel('Y')
plt.savefig("grafica.png")