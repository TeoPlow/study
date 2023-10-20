import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

x = np.linspace(0, 2*np.pi, 100)
y = np.sin(x)

# Нарисуйте кривую греха
fig = plt.figure(tight_layout=True)

# Установить диапазон оси
plt.xlim((-1, 7))
plt.ylim((-2, 2))

#      
point_ani,=plt.plot(x[0], y[0], "r-")# Должен иметь ,, означает получить кортеж
text_pt = plt.text(3.5, 0.8, '', fontsize=16)

def update(num):
    '''Обновить точки данных
         .set_data () означает замену (x [num], y [num]) выше (x [0], y [0])
         Вы также можете .set_ydata, вам нужно изменить указанное выше x [0] на x, здесь x [num] удаляется
    '''
    xx = np.linspace(0, 2*np.pi*num/100, num)
    yy = np.sin(xx)
    point_ani.set_data(xx, yy)
    # text_pt.set_position ([num], y [num]) # Обновить позицию текста
    text_pt.set_text("x=%.3f, y=%.3f"%(x[num], y[num]))
    return point_ani, text_pt,

# Начать делать анимацию
ani = animation.FuncAnimation(fig=fig, func=update, frames=np.arange(0, 100),
                              interval=80, blit=True)

#ani.save('sin.gif', writer='imagegick', fps=10)
plt.show()            