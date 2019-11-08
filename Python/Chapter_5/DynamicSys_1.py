import numpy
from matplotlib import pyplot
from scipy import integrate

L = 1e-3  # inductance: 1mH
C = 10e-9  # capacitance: 10nF
R = 250  # resistance: 250ohm


# function that returns dz/dt=[Vcdot, Idot]
def model(z, t):
    Vc = z[0]
    I = z[1]
    Vcdot = I / C
    if (t <= 100e-6 and 25e-6 < t):
        Vin = 5
    else:
        Vin = 0
    Idot = (Vin - Vc - I * R) / L
    return [Vcdot, Idot]


# initial condition
ic = [0, 0]
# time points
t = numpy.linspace(0, 200e-6, 1000)
u = numpy.zeros(1000)
u[125:500] = 5;
# solve ODE
states = integrate.odeint(model, ic, t)

# plot results
pyplot.figure(figsize=(8, 6))
pyplot.subplot(211)
pyplot.plot(t * 10 ** 6, u, '--', label=r'$V_{in}$')
pyplot.plot(t * 10 ** 6, states[:, 0], label=r'$V_C$')
pyplot.legend()
pyplot.ylabel(r'$V_c (V)$')
pyplot.subplot(212)
pyplot.plot(t * 10 ** 6, states[:, 1])
pyplot.xlabel(r'time ($\mu$s)')
pyplot.ylabel(r'$I (A)$')
pyplot.savefig("DynamicSys_1.png")
pyplot.show()
