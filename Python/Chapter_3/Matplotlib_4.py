import numpy
from matplotlib import pyplot

w = numpy.logspace(-2, 2, 1000)  # log-spaced 1000 points from 0.01 to 100
s = w * 1j  # s = jw
g = (s + 3) / (s * s + s + 3)  # G(s)=(s+3)/(s^2+s+3)
pyplot.figure(figsize=(8, 6))
pyplot.plot(numpy.real(g), numpy.imag(g), '--')
pyplot.plot(numpy.real(g), -numpy.imag(g), '-.')
pyplot.plot(-1, 0, 'r*')
pyplot.title('Nyquist diagram')
pyplot.xlabel('Re')
pyplot.ylabel('Im')
pyplot.axis('equal')
pyplot.xlim(-1.5, 1.5)
pyplot.savefig('Matplotlib_4.png')
pyplot.show()
