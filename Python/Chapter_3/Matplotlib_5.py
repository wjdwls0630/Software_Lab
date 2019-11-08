import numpy
from matplotlib import pyplot

numpy.random.seed(0)
x1 = numpy.random.randn(2, 100)
x2 = 5 * numpy.random.rand(2, 50)
x3 = numpy.random.randn(2, 150)

A1 = numpy.array([[1, -0.5], [-0.5, 4]])
A2 = numpy.array([[1, 0.5], [0.5, 4]])
A3 = numpy.array([[2, 0], [0, 2]])

b1 = numpy.array([-1, 3]).reshape(2, 1)
b2 = numpy.array([0, 0]).reshape(2, 1)
b3 = numpy.array([5, -5]).reshape(2, 1)

y1 = numpy.dot(A1, x1) + b1
y2 = numpy.dot(A2, x2) + b2
y3 = numpy.dot(A3, x3) + b3

pyplot.figure(figsize=(8, 6))
pyplot.plot(y1[0, :], y1[1, :], 'ro', alpha=0.5)
pyplot.plot(y2[0, :], y2[1, :], 'bv', alpha=0.5)
pyplot.plot(y3[0, :], y3[1, :], 'kx', alpha=1.0)
pyplot.legend(['A', 'B', 'C'])
pyplot.savefig("Matplotlib_5.png")
pyplot.show()
