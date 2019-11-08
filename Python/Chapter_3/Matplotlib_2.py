import numpy
from matplotlib import pyplot

t = numpy.linspace(0, 10, 1000)  # equally spaced 1000 points from 0 to 10
x1 = numpy.exp(-t) * numpy.sin(3 * t)
x2 = numpy.exp(-t) * numpy.sin(3 * t + 1)
x3 = numpy.exp(-2 * t) * numpy.cos(3 * t + 1)
pyplot.figure(figsize=(8, 6))
pyplot.plot(t, x1, label=r'$x_1=e^{-t}\sin(3t)$')
pyplot.plot(t, x2, label=r'$x_2=e^{-t}\sin(3t+1)$')
pyplot.plot(t, x3, label=r'$x_3=e^{-2t}\sin(3t+1)$')
pyplot.xlabel(r'$t$')
pyplot.ylabel('Response')
pyplot.xlim(0, 6)
pyplot.ylim(-0.4, 1)
pyplot.grid(True)
pyplot.legend()
pyplot.savefig('Matplotlib_2.png')
pyplot.show()
