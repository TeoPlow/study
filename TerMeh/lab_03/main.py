import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import math
from scipy.integrate import odeint

m1 = 20 #масса трапеции
m2 = 5 #масса точки
r = 0.4 #радиус движения точки
teta0 = 2 #начальный угол отклонения
g = 9.81
s0 = 0 #перемещение
ds0 = 0 #скорость
dteta0 = 0 #угловая скорость

def EqOfMovement(y, t, m1, m2, r, g):
    dy = np.zeros_like(y)
    dy[0] = y[2]
    dy[1] = y[3]

    a11 = m1 + m2
    a12 = m2 * r * np.cos(y[1])
    a21 = np.cos(y[1])
    a22 = r

    b1 = m2 * r * np.sin(y[1]) * (y[3] ** 2) 
    b2 = -g * np.sin(y[1])

    dy[2] = (b1 * a22 - b2 * a12)/(a11 * a22 - a12 * a21)
    dy[3] = (b2 * a11 - b1 * a21)/(a11 * a22 - a12 * a21)
    return dy

t = np.linspace(0, 10, 1000)

 
y0 = [s0, teta0, ds0, dteta0]

Y = odeint(EqOfMovement, y0, t, (m1, m2, r, g))
x = Y[:, 0]
teta = Y[:, 1]

XTrC = 2.5 + x
YTrC = 1.5

XA = 2.5 + x + r * np.sin(teta)
YA = 1.5 - r * np.cos(teta)
Xtr = np.array([1, 1.5, 3.5, 4, 1])
Ytr = np.array([0, 3, 3, 0, 0])

fig = plt.figure(figsize = [1, 1])
ax = fig.add_subplot(1, 2, 1)
ax.set(xlim = [0, 10], ylim = [0, 5])
ax.set_aspect('equal')

TRAP = ax.plot(x[0] + Xtr, Ytr, "red")[0]
radius = ax.plot([XTrC[0], XA[0]], [YTrC, YA[0]], 'black')[0]
PTrC = ax.plot(XTrC[0], YTrC)[0]
PA = ax.plot(XA[0], YA[0], marker = 'o', markersize = 5, color='green')[0]

varphi = np.linspace(0, 2*math.pi, 40)
R1 = r - 1/15
R2 = r + 1/15
Circ1 = ax.plot(XTrC[0] + R1 * np.cos(varphi), YTrC + R1 * np.sin(varphi), 'red')[0]
Circ2 = ax.plot(XTrC[0] + R2 * np.cos(varphi), YTrC + R2 * np.sin(varphi), 'red')[0]

ax1 = fig.add_subplot(4, 2, 2)
ax1.plot(XA)
plt.ylabel('x point')

ax1 = fig.add_subplot(4, 2, 4)
ax1.plot(YA)
plt.ylabel('y point')

ax1 = fig.add_subplot(4, 2, 6)
ax1.plot(XTrC)
plt.ylabel('x trap')

def kadr(i):
    PTrC.set_data(XTrC[i], YTrC)
    PA.set_data(XA[i], YA[i])
    radius.set_data([XTrC[i], XA[i]], [YTrC, YA[i]])
    Circ1.set_data(XTrC[i] + R1 * np.cos(varphi), YTrC + R1 * np.sin(varphi))
    Circ2.set_data(XTrC[i] + R2 * np.cos(varphi), YTrC + R2 * np.sin(varphi))
    TRAP.set_data(x[i] + Xtr, Ytr)
    return [PTrC, PA, TRAP, Circ1, Circ2, radius]

kino = FuncAnimation(fig, kadr, frames = 1000, interval = 10)

plt.show()