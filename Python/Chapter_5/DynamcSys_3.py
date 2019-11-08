import numpy
from matplotlib import pyplot
from scipy import integrate

Cd = 1.0  # drag coefficient


# function that returns dy/dt=[hdot, vdot]
def model(z, t, d):
    S = numpy.pi * d ** 2 / 4  # cross-section area of the droplet
    m = numpy.pi * d ** 3 / 6 * 1000  # mass of the droplet
    h = z[0]  # h, altitude
    v = z[1]  # v, altitude rate
    hdot = v  # dh/dt
    rho = 1.225 * (1 - 2.256e-5 * h) ** 5.226  # air density
    vdot = -10 + 0.5 * rho * v * v * S * Cd / m  # dv/dt
    return [hdot, vdot]


# initial condition
ic = [2000, 0]
# time points
t = numpy.linspace(0, 10, 100)

# solve ODEs
d = 0.01e-3
states1 = integrate.odeint(model, ic, t, args=(d,))
d = 0.1e-3
states2 = integrate.odeint(model, ic, t, args=(d,))
d = 1e-3
states3 = integrate.odeint(model, ic, t, args=(d,))

# plot results
pyplot.figure(figsize=(8, 6))
pyplot.subplot(211)
pyplot.plot(t, states1[:, 0], label='d=0.01mm')
pyplot.plot(t, states2[:, 0], label='d=0.1mm')
pyplot.plot(t, states3[:, 0], label='d=1mm')
pyplot.ylabel('h (m)')
pyplot.legend()
pyplot.subplot(212)
pyplot.plot(t, states1[:, 1], label='d=0.01mm')
pyplot.plot(t, states2[:, 1], label='d=0.1mm')
pyplot.plot(t, states3[:, 1], label='d=1mm')
pyplot.xlabel('time (s)')
pyplot.ylabel('v (m/s)')
pyplot.legend()

pyplot.savefig("DynamicSys_3.png")
pyplot.show()
