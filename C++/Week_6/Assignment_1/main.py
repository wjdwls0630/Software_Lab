import os

import numpy
from matplotlib import pyplot

os.chdir("../Assignment_1")
print(os.getcwd())


def rm_space(data_set: list) -> list:
    data_real = numpy.array([])
    index = 0
    for data in data_set:
        if data != '':
            data_real = numpy.append(data_real, float(data))

    return data_real


try:
    dx = dy = pow(10, -2)
    a0 = 0
    a1 = 1
    b0 = 0
    b1 = 1
    x = numpy.array([])
    y = numpy.array([])
    z = numpy.array([])

    local_x = numpy.array([])
    local_y = numpy.array([])
    local_z = numpy.array([])
    with open("cmake-build-debug/data_local.txt", 'r') as dataFile_local:
        while True:
            line = dataFile_local.readline()
            if not line:
                break
            data = line.split(" ")
            local_x = numpy.append(local_x, float(data[0]))
            local_y = numpy.append(local_y, float(data[1]))
            local_z = numpy.append(local_z, float(data[2]))

    with open("cmake-build-debug/data.txt", 'r') as dataFile:
        line_x = dataFile.readline()
        data_set = line_x.split(" ")

        x = rm_space(data_set)

        for i in range(0, int(b1 / dy)):
            line_yz = dataFile.readline()
            data_set = line_yz.split(" ")
            data_set = rm_space(data_set)
            y = numpy.append(y, float(data_set[0]))
            data_set = numpy.delete(data_set, 0)
            z = numpy.append(z, data_set)

        line_min_max = dataFile.read()

    print(line_min_max)

    Z = z.reshape(int(b1 / dy), int(a1 / dx))
    print(len(Z))
    X, Y = numpy.meshgrid(x, y)

    # plot results
    fig = pyplot.figure()
    ax = fig.gca(projection='3d')
    surf = ax.plot_surface(X, Y, Z, rstride=1, cstride=1, cmap='RdYlGn', linewidth=3, antialiased=False)

    fig.colorbar(surf, shrink=0.5, aspect=5)
    pyplot.title("Assignment_1")
    pyplot.xlabel(r'$x$')
    pyplot.ylabel(r'$y$')
    pyplot.plot(local_x, local_y, local_z, marker='o', markersize=6)
    pyplot.legend()
    pyplot.grid()
    pyplot.savefig("Assignment_1.png")
    pyplot.show()

    pyplot.show()

except FileNotFoundError as e:
    print(e)
