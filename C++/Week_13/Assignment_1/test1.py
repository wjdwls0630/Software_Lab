import numpy
from matplotlib import pyplot


def rm_space(data_set: list) -> list:
    data_real = numpy.array([])
    index = 0
    for data in data_set:
        if data != '':
            data_real = numpy.append(data_real, float(data))

    return data_real


x_n_mag = numpy.array([])
x_n_ph = numpy.array([])
X_k_mag = numpy.array([])
X_k_ph = numpy.array([])
data_num = 0
with open("./data/x_n_1_MagPh.txt", 'r') as dataFile:
    while True:
        line = dataFile.readline()
        if not line:
            break

        data_set = line.split("\t")
        x_n_mag = numpy.append(x_n_mag, float(data_set[0]))
        x_n_ph = numpy.append(x_n_ph, float(data_set[1]))
        data_num = data_num+1


with open("./data/X_k_1_MagPh.txt", 'r') as dataFile:
    while True:
        line = dataFile.readline()
        if not line:
            break

        data_set = line.split("\t")
        X_k_mag = numpy.append(X_k_mag, float(data_set[0]))
        X_k_ph = numpy.append(X_k_ph, float(data_set[1]))


n = numpy.linspace(0, data_num-1, data_num)

fig = pyplot.figure(figsize=(10, 8), dpi=100)
fig.subplots_adjust(hspace=0.7, wspace=0.2)
fig.suptitle('DFT')
ax = fig.add_subplot(2, 1, 1)
ax.set(title="x[n]")
ax.stem(n, x_n_mag, use_line_collection=True)
ax.set_xlabel(r'$n$')
ax.set_ylabel(r'$x[n]$')
ax.grid()

ax = fig.add_subplot(2, 1, 2)
ax.set(title="X[k]")
ax.stem(n, X_k_mag, use_line_collection=True)
ax.set_xlabel(r'$k$')
ax.set_ylabel(r'$X[k]$')
ax.grid()
pyplot.show()
