import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import math
from scipy.integrate import odeint

m_trap = 20     # Масса трапеции
m2 = 5     # Масса точки
r = 0.4     # Радиус движения точки (расстояние от точки подвеса до центра масс)
g = 9.81    # Ускорение свободного падения

# y0
s0 = 0  # Начальное перемещение
teta0 = 2   # Начальный угол отклонения маятника
ds0 = 0     # Начальная скорость
dteta0 = 0  # Начальная угловая скорость

t = np.linspace(0, 10, 1000)

def DvizhMayatnik(y, t, m_trap, m2, r, g):
    dy = np.zeros_like(y)
    dy[0] = y[2]
    dy[1] = y[3]

    a11 = m_trap + m2
    a12 = m2 * r * np.cos(y[1])
    a21 = np.cos(y[1])
    a22 = r

    b1 = m2 * r * np.sin(y[1]) * (y[3] ** 2)
    b2 = -g * np.sin(y[1])

    dy[2] = (b1 * a22 - b2 * a12)/(a11 * a22 - a12 * a21)
    dy[3] = (b2 * a11 - b1 * a21)/(a11 * a22 - a12 * a21)
    return dy # Вектор состояния системы по времени

y0 = [s0, teta0, ds0, dteta0]

Y = odeint(DvizhMayatnik, y0, t, (m_trap, m2, r, g))
x = Y[:, 0]
teta = Y[:, 1]

XTrC = 2.5 + x
YTrC = 1.5

XA = 2.5 + x + r * np.sin(teta)
YA = 1.5 - r * np.cos(teta)
Xtr = np.array([1, 1.5, 3.5, 4, 1])
Ytr = np.array([0, 3, 3, 0, 0])

fig = plt.figure(figsize = [1, 1])

fig.set_size_inches (16,9)

ax = fig.add_subplot(1, 2, 1)
ax.plot([0, 6], [0, 0], color="black")
ax.plot([0, 0], [0, 4], color="black")
ax.set(xlim = [-1, 7], ylim = [-1, 5])
ax.set_aspect('equal')

TRAP = ax.plot(x[0] + Xtr, Ytr, "black")[0]
radius = ax.plot([XTrC[0], XA[0]], [YTrC, YA[0]], 'black')[0]
PTrC = ax.plot(XTrC[0], YTrC)[0]
PA = ax.plot(XA[0], YA[0], marker = 'o', markersize = 5, color='green')[0]

varphi = np.linspace(0, 2*math.pi, 40)
R1 = r - 1/15
R2 = r + 1/15
Circ1 = ax.plot(XTrC[0] + R1 * np.cos(varphi), YTrC + R1 * np.sin(varphi), 'black')[0]
Circ2 = ax.plot(XTrC[0] + R2 * np.cos(varphi), YTrC + R2 * np.sin(varphi), 'black')[0]

ax1 = fig.add_subplot(3, 2, 2)
ax1.plot(XA, 'blue')
plt.title(' ')
plt.ylabel('X point')

ax1 = fig.add_subplot(3, 2, 4)
ax1.plot(YA, 'orange')
plt.title(' ')
plt.ylabel('Y point')

ax1 = fig.add_subplot(3, 2, 6)
ax1.plot(XTrC, 'purple')
plt.title(' ')
plt.ylabel('X trapeze')

def foo(i):
    PTrC.set_data(XTrC[i], YTrC)
    PA.set_data(XA[i], YA[i])
    radius.set_data([XTrC[i], XA[i]], [YTrC, YA[i]])
    Circ1.set_data(XTrC[i] + R1 * np.cos(varphi), YTrC + R1 * np.sin(varphi))
    Circ2.set_data(XTrC[i] + R2 * np.cos(varphi), YTrC + R2 * np.sin(varphi))
    TRAP.set_data(x[i] + Xtr, Ytr)
    return [PTrC, PA, TRAP, Circ1, Circ2, radius]

animation = FuncAnimation(fig, foo, frames = 1000, interval = 10)

plt.show()