import os

import numpy
from matplotlib import pyplot

print(os.getcwd())


def rm_space(data_set: list) -> list:
    data_real = numpy.array([])
    index = 0
    for data in data_set:
        if data != '':
            data_real = numpy.append(data_real, float(data))

    return data_real


try:
    dx = dy = 0.1
    a0 = -3
    a1 = 3
    b0 = -3
    b1 = 3
    x = numpy.array([])
    y = numpy.array([])
    z = numpy.array([])

    local_x = numpy.array([])
    local_y = numpy.array([])
    local_z = numpy.array([])

    coord_from_x = numpy.array([])
    coord_to_x = numpy.array([])
    coord_from_y = numpy.array([])
    coord_to_y = numpy.array([])
    coord_from_z = numpy.array([])
    coord_to_z = numpy.array([])

    eta_list = numpy.array([])
    psi_list = numpy.array([])
    accuracy_list = numpy.array([])
    time_list = numpy.array([])

    # graph

    with open("cmake-build-debug/data.txt", 'r') as dataFile:
        line_x = dataFile.readline()
        data_set = line_x.split(" ")

        x = rm_space(data_set)

        for i in range(0, int((b1 - b0) / dy)):
            line_yz = dataFile.readline()
            data_set = line_yz.split(" ")
            data_set = rm_space(data_set)
            y = numpy.append(y, float(data_set[0]))
            data_set = numpy.delete(data_set, 0)
            z = numpy.append(z, data_set)

    # marker local point

    with open("cmake-build-debug/data_local.txt", 'r') as dataFile_local:
        while True:
            line = dataFile_local.readline()
            if not line:
                break
            data = line.split(" ")
            local_x = numpy.append(local_x, float(data[0]))
            local_y = numpy.append(local_y, float(data[1]))
            local_z = numpy.append(local_z, float(data[2]))

    # how to move

    with open("cmake-build-debug/data_log_coord.txt", 'r') as dataFile_log_coord:
        while True:
            line = dataFile_log_coord.readline()
            if not line:
                break
            data = line.split(" ")
            coord_from_x = numpy.append(coord_from_x, float(data[0]))
            coord_to_x = numpy.append(coord_to_x, float(data[3]))
            coord_from_y = numpy.append(coord_from_y, float(data[1]))
            coord_to_y = numpy.append(coord_to_y, float(data[4]))
            coord_from_z = numpy.append(coord_from_z, float(data[2]))
            coord_to_z = numpy.append(coord_to_z, float(data[5]))

    # accuracy vs time

    with open("cmake-build-debug/data_pe.txt", 'r') as dataFile_pe:
        while True:
            line = dataFile_pe.readline()
            if not line:
                break
            data = line.split(" ")
            psi_list = numpy.append(psi_list, float(data[0]))
            eta_list = numpy.append(eta_list, float(data[1]))
            accuracy_list = numpy.append(accuracy_list, float(data[2]))
            time_list = numpy.append(time_list, float(data[3]))

    # make 3D
    Z = z.reshape(int((b1 - b0) / dy), int((a1 - a0) / dx))
    X, Y = numpy.meshgrid(x, y)

    # plot results
    fig = pyplot.figure()
    ax = fig.gca(projection='3d')
    surf = ax.plot_surface(X, Y, Z, rstride=1, cstride=1, cmap='RdYlGn', linewidth=3, antialiased=False)
    fig.colorbar(surf, shrink=0.5, aspect=5)
    pyplot.title("Assignment_2_1")
    pyplot.xlabel(r'$x$')
    pyplot.ylabel(r'$y$')

    # how to move

    pyplot.plot(coord_from_x, coord_from_y, coord_from_z, 'ko', markersize=6)
    pyplot.plot(coord_to_x, coord_to_y, coord_to_z, 'ro', markersize=6)
    for i in range(0, len(coord_from_x)):
        pyplot.plot([coord_from_x[i], coord_to_x[i]], [coord_from_y[i], coord_to_y[i]], [coord_from_z[i], coord_to_z[i]]
                    , '->', color='b', linewidth=1)

    pyplot.savefig("Assignment_2_1.png")

    fig1 = pyplot.figure()
    pyplot.scatter(time_list, accuracy_list)
    pyplot.title("Assignment_2_2")
    pyplot.xlabel('time')
    pyplot.ylabel('accuracy')
    pyplot.savefig("Assignment_2_2.png")
    pyplot.legend()
    pyplot.grid()
    pyplot.show()
except FileNotFoundError as e:
    print(e)
