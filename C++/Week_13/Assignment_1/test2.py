import numpy
from matplotlib import pyplot


def rm_space(data_set: list) -> list:
    data_real = numpy.array([])
    index = 0
    for data in data_set:
        if data != '':
            data_real = numpy.append(data_real, float(data))

    return data_real


data_num = 0
X_k_1_mag = numpy.array([])
with open("./data/Test2/DFTofSquare.txt", 'r') as dataFile:
    while True:
        line = dataFile.readline()
        if not line:
            break

        X_k_1_mag = numpy.append(X_k_1_mag, float(line))
        data_num = data_num + 1

x_n_1_mag = numpy.array([])
x_n_1_ph = numpy.array([])
with open("./data/Test2/DFTofSquare_IDFT.txt", 'r') as dataFile:
    while True:
        line = dataFile.readline()
        if not line:
            break

        data_set = line.split("\t")
        x_n_1_mag = numpy.append(x_n_1_mag, float(data_set[0]))
        x_n_1_ph = numpy.append(x_n_1_ph, float(data_set[1]))

x_n_2_mag = numpy.array([])
with open("./data/Test2/IDFTofLPF.txt", 'r') as dataFile:
    while True:
        line = dataFile.readline()
        if not line:
            break

        x_n_2_mag = numpy.append(x_n_2_mag, float(line))

X_k_2_mag = numpy.array([])
X_k_2_ph = numpy.array([])
with open("./data/Test2/IDFTofLPF_DFT.txt", 'r') as dataFile:
    while True:
        line = dataFile.readline()
        if not line:
            break

        data_set = line.split("\t")
        X_k_2_mag = numpy.append(X_k_2_mag, float(data_set[0]))
        X_k_2_ph = numpy.append(X_k_2_ph, float(data_set[1]))

n = numpy.linspace(0, data_num - 1, data_num)

fig = pyplot.figure(figsize=(10, 8), dpi=100)
fig.subplots_adjust(hspace=0.7, wspace=0.2)
fig.suptitle('Test2_DFT')
ax = fig.add_subplot(4, 1, 1)
ax.set(title="X[k]_DFTofSquare")
ax.stem(n, X_k_1_mag, use_line_collection=True)
ax.set_xlabel(r'$k$')
ax.set_ylabel(r'$X[k]$')
ax.grid()

ax = fig.add_subplot(4, 1, 2)
ax.set(title="x[n]")
ax.stem(n, x_n_1_mag, use_line_collection=True)
ax.set_xlabel(r'$n$')
ax.set_ylabel(r'$x[n]$')
ax.grid()

ax = fig.add_subplot(4, 1, 3)
ax.set(title="x[n]_IDFTofLPF")
ax.stem(n, x_n_2_mag, use_line_collection=True)
ax.set_xlabel(r'$n$')
ax.set_ylabel(r'$x[n]$')
ax.grid()

ax = fig.add_subplot(4, 1, 4)
ax.set(title="X[k]")
ax.stem(n, X_k_2_mag, use_line_collection=True)
ax.set_xlabel(r'$k$')
ax.set_ylabel(r'$X[k]$')
ax.grid()
pyplot.savefig("./data/Test2/Test2.png")
pyplot.show()
