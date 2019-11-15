import numpy
from matplotlib import pyplot

try:
    x = numpy.array([])
    y = numpy.array([])
    with open("cmake-build-debug/data2.txt", 'r') as dataFile:
        line = dataFile.readline()
        N = int(line)  # read one line
        # number of data

        while True:
            line = dataFile.readline()  # read one line
            if not line:
                break
            data = line.split("\t")  # save data
            x = numpy.append(x, float(data[0]))
            y = numpy.append(y, float(data[1]))

    # plot results
    pyplot.figure(dpi=100, figsize=(8, 6))
    pyplot.scatter(x, y, label="data")
    x_experi = numpy.linspace(-7.5, 10, 100)
    pyplot.plot(x_experi, -1.17745 * pow(x_experi, 2) + 6.13387 * x_experi + (-1.17745), 'r', linewidth=2)
    pyplot.xlabel(r'$x$')
    pyplot.ylabel(r'$y$')
    pyplot.legend()
    pyplot.grid()
    pyplot.savefig("Assignment_1.png")
    pyplot.show()

except FileNotFoundError as e:
    print(e)
