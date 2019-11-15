import numpy
from matplotlib import pyplot

try:
    x = numpy.array([])
    y = numpy.array([])
    with open("cmake-build-debug/datae.txt", 'r') as dataFile:
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
    x_exp = numpy.linspace(-7.5, 10, 100)
    pyplot.plot(x_exp, 5.26529 * numpy.exp(0.315812 * x_exp), 'r', linewidth=2, label="no calculate")
    # pyplot.plot(x_exp, 5.93554*numpy.exp(0.30054*x_exp), 'k',linewidth=2, label="make 0")

    pyplot.title("Assignment_2")
    pyplot.xlabel(r'$x$')
    pyplot.ylabel(r'$y$')
    pyplot.legend()
    pyplot.grid()
    pyplot.savefig("Assignment_2.png")
    pyplot.show()

except FileNotFoundError as e:
    print(e)
