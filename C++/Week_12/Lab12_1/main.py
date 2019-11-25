import numpy
from matplotlib import pyplot
from scipy import integrate

try:
    # setting numerical solution data to plot
    t_numerical = numpy.array([])
    vt_numerical = numpy.array([])
    with open("cmake-build-debug/data.txt", 'r') as dataFile:
        while True:
            line = dataFile.readline()  # read one line

            if not line:
                break

            data = line.split(" ")  # save data
            t_numerical = numpy.append(t_numerical, float(data[0]))
            vt_numerical = numpy.append(vt_numerical, float(data[1]))

    # analytical solution

    t = numpy.linspace(0, 6 * pow(10, -3), 1000)  # equally spaced 1000 points from 0 to 6ms
    vt_analysis = (48 - numpy.exp(-1400 * t) * (48 * numpy.cos(4800 * t) + 14 * numpy.sin(4800 * t)))

    """
    Actually python has their own library called integrate, and In this library
    it have function named odeint which solve Dynamic equation
    we can compare our solution in cpp with using this function 
    """

    # first define model which include Dynamic equation

    # Different equation - Circuit - Coefficient

    V = 48.0  # voltage source : 48 V
    L = 100 * pow(10, -3)  # inductance: 100mH
    C = 0.4 * pow(10, -6)  # capacitance: 0.4uF
    R = 280.0  # resistance: 280ohm


    # function that returns dz/dt=[Vcdot, Idot]
    def model(z, t):
        v_c = z[0]
        i = z[1]
        v_c_dot = i / C
        if t >= 0:
            Vin = V
        else:
            Vin = 0

        """
        Using KVL 
        V-Ri-Li_dot-v_c = 0
        i = C*v_c_dot
        """
        i_dot = (Vin - v_c - i * R) / L
        # [first order diff, second order diff]
        return [v_c_dot, i_dot]


    # set initial condition
    ic = [0, 0]

    # solve ODE
    states = integrate.odeint(model, ic, t)

    # plot results
    pyplot.figure(dpi=100, figsize=(10, 8))
    pyplot.plot(t_numerical * pow(10, 3), vt_numerical, 'r', linewidth=1, label=rf'numerical')
    pyplot.plot(t * pow(10, 3), vt_analysis, 'g', '--', linewidth=1, label=rf'analytical')
    pyplot.plot(t * pow(10, 3), states[:, 0], 'b', '--', linewidth=1, label=rf'odeint')
    pyplot.title("Lab12_1")
    pyplot.xlabel(r'$t$ (ms)')
    pyplot.ylabel(r'$v(t)$')
    pyplot.legend()
    pyplot.grid()
    pyplot.savefig("Lab12_1.png")
    pyplot.show()


except FileNotFoundError as e:
    print(e)
