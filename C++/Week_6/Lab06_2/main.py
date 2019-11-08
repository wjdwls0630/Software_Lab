import numpy
from matplotlib import pyplot


def rm_space(data_set: list) -> list:
    data_real = numpy.array([])
    index = 0
    for data in data_set:
        if data != '':
            data_real = numpy.append(data_real, float(data))

    return data_real


try:
    dx = dy = 0.1
    a0 = 1
    a1 = 5
    b0 = -4
    b1 = 0
    x = numpy.array([])
    y = numpy.array([])
    z = numpy.array([])
    with open("cmake-build-debug/data.txt", 'r') as dataFile:
        line_x = dataFile.readline()
        data_set = line_x.split(" ")

        x = rm_space(data_set)

        for i in range(0, int(b1 - b0 / dy)):
            line_yz = dataFile.readline()
            data_set = line_yz.split(" ")
            data_set = rm_space(data_set)
            y = numpy.append(y, float(data_set[0]))
            data_set = numpy.delete(data_set, 0)
            z = numpy.append(z, data_set)

    Z = z.reshape(int(b1 - b0 / dy), int(a1 - a0 / dx))
    print(len(Z))
    X, Y = numpy.meshgrid(x, y)

    # plot results
    fig = pyplot.figure()
    ax = fig.gca(projection='3d')
    surf = ax.plot_surface(X, Y, Z, rstride=1, cstride=1, cmap='RdYlGn', linewidth=3, antialiased=False)

    fig.colorbar(surf, shrink=0.5, aspect=5)
    pyplot.title("Lab06_2")
    pyplot.xlabel(r'$x$')
    pyplot.ylabel(r'$y$')
    pyplot.legend()
    pyplot.grid()
    pyplot.savefig("Lab06_2.png")
    pyplot.show()

    pyplot.show()

except FileNotFoundError as e:
    print(e)
