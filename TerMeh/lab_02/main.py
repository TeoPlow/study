import numpy as np
import sympy as sp
import math
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

def Trapez(x0, y0):
    PX = [x0 - 10, x0 - (2/3) * 10, x0 + (2/3) * 10, x0 + 10, x0 - 10]
    PY = [y0 - 7.5, y0 + 10, y0 + 10, y0 - 7.5, y0 - 7.5]
    return PX, PY

alpha = math.pi

t = sp.Symbol('t')

s = sp.sin(t)
teta = sp.cos(t)
r = 5

X_trap = s * sp.cos(alpha) + 0.8
Y_trap = 7.5

VmodSignTrap = sp.diff(s, t)

VX_trap = VmodSignTrap * sp.cos(alpha)
VY_trap = sp.sin(alpha) * VmodSignTrap

xA = X_trap - r * sp.sin(teta)
yA = Y_trap + r * sp.cos(teta)

omega = sp.diff(teta, t)

VxA = VX_trap - omega * r * sp.cos(teta)
VyA = VY_trap - omega * r * sp.sin(teta)

F_X_trap = sp.lambdify(t, X_trap)
F_VX_trap = sp.lambdify(t, VX_trap)
F_VY_trap = sp.lambdify(t, VY_trap)
F_Teta = sp.lambdify(t, teta)
F_XA = sp.lambdify(t, xA)
F_YA = sp.lambdify(t, yA)
F_VXA = sp.lambdify(t, VyA)
F_VYA = sp.lambdify(t, VyA)

T = np.linspace(0, 20, 1000)

X_trap = F_X_trap(T)
VX_trap = F_VX_trap(T)
VY_trap = F_VY_trap(T)
Teta = F_Teta(T)
XA = F_XA(T)
YA = F_YA(T)
VXA = F_VXA(T)
VYA = F_VYA(T)

fig = plt.figure(figsize=(17, 10))

ax1 = fig.add_subplot(1, 2, 1)
ax1.axis('equal')
ax1.set(xlim=[X_trap.min() - 20, X_trap.max() + 20], ylim=[Y_trap - 20, Y_trap + 20])
ax1.plot([X_trap.min() - 10, X_trap.max() + 10], [-(X_trap.min() - 10) * sp.tan(alpha), -(X_trap.max() + 10) * sp.tan(alpha)], 'black')

PrX, PrY = Trapez(X_trap[0], Y_trap)
Trap = ax1.plot(PrX, PrY, 'black')[0]

radius = ax1.plot([X_trap[0], XA[0]], [Y_trap, YA[0]], 'black')[0]

varphi = np.linspace(0, 2 * math.pi, 40)
R1 = r - 5 / 15
R2 = r + 5 / 15
Point = ax1.plot(XA[0], YA[0], marker='o', markersize=10, color='green')[0]
circle_1 = ax1.plot(X_trap[0] + R1 * np.cos(varphi), Y_trap + R1 * np.sin(varphi), 'black')[0]
circle_2 = ax1.plot(X_trap[0] + R2 * np.cos(varphi), Y_trap + R2 * np.sin(varphi), 'black')[0]

ax2 = fig.add_subplot(3, 2, 2)
ax2.plot(T, VX_trap)
ax2.set_ylabel('VX Trapeze')

ax3 = fig.add_subplot(3, 2, 4)
ax3.plot(T, VXA)
ax3.set_ylabel('VX Point')

ax4 = fig.add_subplot(3, 2, 6)
ax4.plot(T, VYA)
ax4.set_ylabel('VY Point')

plt.subplots_adjust(wspace=0.3, hspace=0.7)


def foo(i):
    PrX, PrY = Trapez(X_trap[i], Y_trap)
    Trap.set_data(PrX, PrY)
    radius.set_data([X_trap[i], XA[i]], [Y_trap, YA[i]])
    Point.set_data(XA[i], YA[i])
    circle_1.set_data(X_trap[i] + R1 * np.cos(varphi), Y_trap + R1 * np.sin(varphi))
    circle_2.set_data(X_trap[i] + R2 * np.cos(varphi), Y_trap + R2 * np.sin(varphi))
    return Trap, Point, radius, circle_1, circle_2


kino = FuncAnimation(fig, foo, frames=1000, interval=0.01, blit=True)

plt.show()