import numpy
from matplotlib import pyplot
from scipy import integrate

Cd = 1.0  # drag coefficient


# function that returns dy/dt=[hdot, vdot]


def model(z, t):
    h = z[0]  # h, altitude
    v = z[1]  # v, altitude rate
    hdot = v  # dh/dt
    vdot = -10  # dv/dt
    return [hdot, vdot]


# initial condition
ic = [2000, 0]
# time points
t = numpy.linspace(0, 20, 100)

# solve ODE
states = integrate.odeint(model, ic, t)

# plot results
pyplot.figure(figsize=(8, 6))
pyplot.subplot(211)
pyplot.plot(t, states[:, 0], label='Numerical solution')
pyplot.plot(t, 2000 - 0.5 * 10 * t * t, '--', label='Analytic solution')
pyplot.ylabel('h (m)')
pyplot.legend()
pyplot.subplot(212)
pyplot.plot(t, states[:, 1], label='Numerical solution')
pyplot.plot(t, -10 * t, '--', label='Analytic solution')
pyplot.xlabel('time (s)')
pyplot.ylabel('v (m/s)')
pyplot.legend()
pyplot.savefig("DynamicSys_2.png")
pyplot.show()
