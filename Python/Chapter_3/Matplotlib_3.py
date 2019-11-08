import numpy
from matplotlib import pyplot

w = numpy.logspace(-2, 2, 1000)  # log-spaced 1000 points from 0.01 to 100
s = w * 1j  # s = jw
g = (s + 3) / (s * s + s + 3)  # G(s)=(s+3)/(s^2+s+3)
pyplot.figure(figsize=(8, 6))
pyplot.subplot(211)
pyplot.semilogx(w, 20 * numpy.log(abs(g)))
pyplot.ylabel('Magnitude (dB)')
pyplot.grid(True)
pyplot.title('Bode diagram')
pyplot.subplot(212)
pyplot.semilogx(w, 180 / numpy.pi * numpy.angle(g))
pyplot.ylabel('Phase (deg)')
pyplot.xlabel('Frequency (rad/s)')
pyplot.grid(True)
pyplot.savefig('Matplotlib_3.png')
pyplot.show()
