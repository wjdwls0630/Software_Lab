import numpy
from matplotlib import pyplot, cm

try:
    dx = dy = 0.1
    a = 2
    b = 1
    x = numpy.array([])
    y = numpy.array([])
    z = numpy.array([])
    with open("cmake-build-debug/data.txt", 'r') as dataFile:
        for i in range(0, int(a / dx)):
            line_x = dataFile.readline()
            x = numpy.append(x, float(line_x))

        for i in range(0, int(b / dy)):
            line_y = dataFile.readline()
            y = numpy.append(y, float(line_y))
            for j in range(0, int(a / dx)):
                line_z = dataFile.readline()
                z = numpy.append(z, float(line_z))

    Z = z.reshape(int(b / dy), int(a / dx))
    print(len(Z))
    X, Y = numpy.meshgrid(x, y)

    # plot results
    fig = pyplot.figure()
    ax = fig.gca(projection='3d')
    surf = ax.plot_surface(X, Y, Z, rstride=1, cstride=1, cmap=cm.coolwarm, linewidth=3, antialiased=False)

    fig.colorbar(surf, shrink=0.5, aspect=5)
    pyplot.title("Lab04_2")
    pyplot.xlabel(r'$x$ (sec)')
    pyplot.ylabel(r'$y$')
    pyplot.legend()
    pyplot.grid()
    pyplot.savefig("Lab04_2.png")
    pyplot.show()

    pyplot.show()

except FileNotFoundError as e:
    print(e)
