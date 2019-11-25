import numpy
from matplotlib import animation
from matplotlib import pyplot

fig = pyplot.figure()

ax = pyplot.axes(xlim=(0, 20050), ylim=(-40, 40))
ax.grid()
ax.set_xlabel(rf'r(m)')
ax.set_ylabel(rf'A')
line, = ax.plot([], [])


def init():
    line.set_data([], [])
    return line,


def animate(i):
    r_numerical = numpy.array([])
    a_numerical = numpy.array([])

    with open("data/R_tn=" + str(int(i)) + ".txt", 'r') as dataFile:
        while True:
            file_line = dataFile.readline()  # read one line

            if not file_line:
                break

            data = file_line.split(" ")  # save data
            r_numerical = numpy.append(r_numerical, float(data[0]))
            a_numerical = numpy.append(a_numerical, float(data[1]))

    line.set_data(r_numerical, a_numerical)
    return line,


anim = animation.FuncAnimation(fig=fig, func=animate, init_func=init, frames=numpy.linspace(0, 499, 499),
                               blit=True)
anim.save("video/EM_wave.mp4", fps=50, extra_args=['-vcodec', 'libx264'])

pyplot.show()
