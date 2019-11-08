import numpy
from matplotlib import pyplot

x = numpy.random.randn(100000, 5)

pyplot.figure(figsize=(8, 6))
pyplot.hist(x[:, 0], 50, density=1)
pyplot.title('Standard normal distribution')
pyplot.grid()
pyplot.xlabel(r'$x$')
pyplot.ylabel('Probability density function')
pyplot.xlim(-4, 4)
pyplot.savefig("Matplotlib_6_1.png")

xsq = x * x
x2 = numpy.sum(xsq[:, 0:2], axis=1)
x3 = numpy.sum(xsq[:, 0:3], axis=1)
x4 = numpy.sum(xsq[:, 0:4], axis=1)
x5 = numpy.sum(xsq[:, 0:5], axis=1)

pyplot.figure(figsize=(8, 6))
pyplot.hist(x2, 200, density=1, alpha=1.0)
pyplot.hist(x3, 200, density=1, alpha=0.8)
pyplot.hist(x4, 200, density=1, alpha=0.6)
pyplot.hist(x5, 200, density=1, alpha=0.4)
pyplot.title('Chi squared distribution')
pyplot.grid()
pyplot.xlabel(r'$x$')
pyplot.ylabel('Probability density function')
pyplot.xlim(0, 10)
pyplot.legend([r'$\chi^2_2$', r'$\chi^2_3$', r'$\chi^2_4$', r'$\chi^2_5$'])
pyplot.savefig("Matplotlib_6_2.png")
pyplot.show()
