import numpy
from matplotlib import pyplot

t = numpy.arange(0, 10, 0.01)  # points from 0 to 10 spaced by 0.01
x1 = numpy.exp(-t) * numpy.sin(3 * t)
pyplot.plot(t, x1)
pyplot.show()
