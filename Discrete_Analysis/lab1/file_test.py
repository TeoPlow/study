import subprocess
import time
import numpy as np
import matplotlib.pyplot as plot

out = open("C:/Programs/study/Discrete_Analysis/lab1/file_test/output.txt", 'w')
numberOfAttempts = 3

executable = "C:\\Programs\\study\\Discrete_Analysis\\lab1\\main.exe"
directory = "C:\\Programs\\study\\Discrete_Analysis\\lab1\\file_test\\"
testfiles = [
    "1.txt",
    "10.txt",
    "100.txt",
    "1000.txt",
    "10000.txt",
    "100000.txt"
]

# figure = plot.figure()
# ax1 = figure.add_subplot(1,1,1)

# N = np.zeros(len(testfiles))
# T = np.zeros(len(testfiles))
# i = 0

# for filename in testfiles:
#     file = open(directory + filename, 'r')
#     print("test file ", file.name)
#     t = np.zeros(numberOfAttempts)

#     for x in range(numberOfAttempts):
#         t0 = time.perf_counter()
#         subprocess.call([executable], stdin=file, stdout=out, shell=False)
#         t1 = time.perf_counter()
#         t[x] = (t1 - t0) * 1000
#     T[i] = np.median(t)

#     # Изменение способа определения N для соответствия степеням 10
#     N[i] = 10**i
#     i += 1

# # Установка логарифмического масштаба для оси X
# ax1.set_xscale('log')

# # Установка меток по оси X равных степеням 10
# ax1.set_xticks(N)

# ax1.plot(N, T)

# plot.show()



figure = plot.figure()
ax1 = figure.add_subplot(1,1,1)

N = np.zeros(len(testfiles))
T = np.zeros(len(testfiles))
i = 0

for filename in testfiles:
    file = open(directory + filename, 'r')
    print("test file ", file.name, end=' ')
    t = np.zeros(numberOfAttempts)
    returned = 0
    for x in range(numberOfAttempts):
        t0 = time.perf_counter()
        returned = subprocess.call([executable], stdin=file, stdout=out, shell=False)
        t1 = time.perf_counter()
        if returned != 0:
            break
        t[x] = (t1 - t0) * 1000
    T[i] = np.mean(t)
    N[i] = int(filename[0: -4])
    print(returned)
    i += 1

ax1.plot(N, T)

plot.show()
