import os
import numpy as np
import matplotlib.pyplot as plt

data = np.loadtxt("Clase_28.dat")
angle= 45
v_0= 22
v_0x = v_0*np.cos(angle*np.pi/180);
v_0y = v_0*np.sin(angle*np.pi/180);
tmax= np.abs(2*v_0y/-9.8)
t=np.linspace(0,tmax,100)
x=v_0x*t
y=v_0y*t+((-9.8*(t**2)/2))


plt.figure(1, figsize=(10,8)) 
plt.plot(data[:,1], data[:,3],label=(" With air resistance "))
plt.plot(x, y,label=(" Ideal "))
plt.xlabel('X')
plt.ylabel('Y')
plt.legend(loc='0')
plt.savefig("grafica.png")
