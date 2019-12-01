import numpy
from matplotlib import pyplot


def rm_space(data_set: list) -> list:
    data_real = numpy.array([])
    index = 0
    for data in data_set:
        if data != '':
            data_real = numpy.append(data_real, float(data))

    return data_real


# signal 1
x_n_1_re = numpy.array([])
x_n_1_im = numpy.array([])
data_num = 0
with open("./data/main/x_n_1_ReIm.txt", 'r') as dataFile:
    while True:
        line = dataFile.readline()
        if not line:
            break

        data_set = line.split("\t")
        x_n_1_re = numpy.append(x_n_1_re, float(data_set[0]))
        x_n_1_im = numpy.append(x_n_1_im, float(data_set[1]))
        data_num = data_num + 1

X_k_1_mag_DFT = numpy.array([])
X_k_1_ph_DFT = numpy.array([])
with open("./data/main/X_k_1_MagPh_DFT.txt", 'r') as dataFile:
    while True:
        line = dataFile.readline()
        if not line:
            break

        data_set = line.split("\t")
        X_k_1_mag_DFT = numpy.append(X_k_1_mag_DFT, float(data_set[0]))
        X_k_1_ph_DFT = numpy.append(X_k_1_ph_DFT, float(data_set[1]))

X_k_1_mag_FFT = numpy.array([])
X_k_1_ph_FFT = numpy.array([])
with open("./data/main/X_k_1_MagPh_FFT.txt", 'r') as dataFile:
    while True:
        line = dataFile.readline()
        if not line:
            break

        data_set = line.split("\t")
        X_k_1_mag_FFT = numpy.append(X_k_1_mag_FFT, float(data_set[0]))
        X_k_1_ph_FFT = numpy.append(X_k_1_ph_FFT, float(data_set[1]))

# signal 2
x_n_2_re = numpy.array([])
x_n_2_im = numpy.array([])
with open("./data/main/x_n_2_ReIm.txt", 'r') as dataFile:
    while True:
        line = dataFile.readline()
        if not line:
            break

        data_set = line.split("\t")
        x_n_2_re = numpy.append(x_n_2_re, float(data_set[0]))
        x_n_2_im = numpy.append(x_n_2_im, float(data_set[1]))

X_k_2_mag_DFT = numpy.array([])
X_k_2_ph_DFT = numpy.array([])
with open("./data/main/X_k_2_MagPh_DFT.txt", 'r') as dataFile:
    while True:
        line = dataFile.readline()
        if not line:
            break

        data_set = line.split("\t")
        X_k_2_mag_DFT = numpy.append(X_k_2_mag_DFT, float(data_set[0]))
        X_k_2_ph_DFT = numpy.append(X_k_2_ph_DFT, float(data_set[1]))

X_k_2_mag_FFT = numpy.array([])
X_k_2_ph_FFT = numpy.array([])
with open("./data/main/X_k_2_MagPh_FFT.txt", 'r') as dataFile:
    while True:
        line = dataFile.readline()
        if not line:
            break

        data_set = line.split("\t")
        X_k_2_mag_FFT = numpy.append(X_k_2_mag_FFT, float(data_set[0]))
        X_k_2_ph_FFT = numpy.append(X_k_2_ph_FFT, float(data_set[1]))

# signal 3
x_n_3_re = numpy.array([])
x_n_3_im = numpy.array([])
with open("./data/main/x_n_3_ReIm.txt", 'r') as dataFile:
    while True:
        line = dataFile.readline()
        if not line:
            break

        data_set = line.split("\t")
        x_n_3_re = numpy.append(x_n_3_re, float(data_set[0]))
        x_n_3_im = numpy.append(x_n_3_im, float(data_set[1]))

X_k_3_mag_DFT = numpy.array([])
X_k_3_ph_DFT = numpy.array([])
with open("./data/main/X_k_3_MagPh_DFT.txt", 'r') as dataFile:
    while True:
        line = dataFile.readline()
        if not line:
            break

        data_set = line.split("\t")
        X_k_3_mag_DFT = numpy.append(X_k_3_mag_DFT, float(data_set[0]))
        X_k_3_ph_DFT = numpy.append(X_k_3_ph_DFT, float(data_set[1]))

X_k_3_mag_FFT = numpy.array([])
X_k_3_ph_FFT = numpy.array([])
with open("./data/main/X_k_3_MagPh_FFT.txt", 'r') as dataFile:
    while True:
        line = dataFile.readline()
        if not line:
            break

        data_set = line.split("\t")
        X_k_3_mag_FFT = numpy.append(X_k_3_mag_FFT, float(data_set[0]))
        X_k_3_ph_FFT = numpy.append(X_k_3_ph_FFT, float(data_set[1]))

# plot
n = numpy.linspace(0, data_num - 1, data_num)

# signal 1
fig1 = pyplot.figure(figsize=(8, 6), dpi=100)
fig1.subplots_adjust(hspace=0.7, wspace=0.2)
fig1.suptitle('x[n] =1 (n<10, n>118)')
ax = fig1.add_subplot(3, 1, 1)
ax.set(title="x[n]")
ax.stem(n, x_n_1_re, use_line_collection=True)
ax.set_xlabel(r'$n$')
ax.set_ylabel(r'$x[n]$')
ax.grid()

ax = fig1.add_subplot(3, 1, 2)
ax.set(title="X[k]_DFT")
ax.stem(n, X_k_1_mag_DFT, use_line_collection=True)
ax.set_xlabel(r'$k$')
ax.set_ylabel(r'$X[k]$')
ax.grid()

ax = fig1.add_subplot(3, 1, 3)
ax.set(title="X[k]_FFT")
ax.stem(n, X_k_1_mag_FFT, use_line_collection=True)
ax.set_xlabel(r'$k$')
ax.set_ylabel(r'$X[k]$')
ax.grid()
pyplot.savefig("./data/main/signal_1.png")

# signal 2
fig2 = pyplot.figure(figsize=(8, 6), dpi=100)
fig2.subplots_adjust(hspace=0.7, wspace=0.2)
fig2.suptitle('x[n] =cos(8*pi*n/N)')
ax = fig2.add_subplot(3, 1, 1)
ax.set(title="x[n]")
ax.stem(n, x_n_2_re, use_line_collection=True)
ax.set_xlabel(r'$n$')
ax.set_ylabel(r'$x[n]$')
ax.grid()

ax = fig2.add_subplot(3, 1, 2)
ax.set(title="X[k]_DFT")
ax.stem(n, X_k_2_mag_DFT, use_line_collection=True)
ax.set_xlabel(r'$k$')
ax.set_ylabel(r'$X[k]$')
ax.grid()

ax = fig2.add_subplot(3, 1, 3)
ax.set(title="X[k]_FFT")
ax.stem(n, X_k_2_mag_FFT, use_line_collection=True)
ax.set_xlabel(r'$k$')
ax.set_ylabel(r'$X[k]$')
ax.grid()
pyplot.savefig("./data/main/signal_2.png")

# signal 3
fig3 = pyplot.figure(figsize=(8, 6), dpi=100)
fig3.subplots_adjust(hspace=0.7, wspace=0.2)
fig3.suptitle('x[n] =sin(16*pi*n/N)')
ax = fig3.add_subplot(3, 1, 1)
ax.set(title="x[n]")
ax.stem(n, x_n_3_re, use_line_collection=True)
ax.set_xlabel(r'$n$')
ax.set_ylabel(r'$x[n]$')
ax.grid()

ax = fig3.add_subplot(3, 1, 2)
ax.set(title="X[k]_DFT")
ax.stem(n, X_k_3_mag_DFT, use_line_collection=True)
ax.set_xlabel(r'$k$')
ax.set_ylabel(r'$X[k]$')
ax.grid()

ax = fig3.add_subplot(3, 1, 3)
ax.set(title="X[k]_FFT")
ax.stem(n, X_k_3_mag_FFT, use_line_collection=True)
ax.set_xlabel(r'$k$')
ax.set_ylabel(r'$X[k]$')
ax.grid()
pyplot.savefig("./data/main/signal_3.png")
pyplot.show()
