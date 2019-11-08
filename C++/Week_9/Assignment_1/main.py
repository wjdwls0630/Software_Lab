import numpy
from matplotlib import pyplot

try:
    # value
    x_list = []
    p_list = []

    x_lin_list = numpy.linspace(1, 700, 10000)
    prop_list = []

    n_list = numpy.array([])

    temp1 = numpy.array([])
    temp2 = numpy.array([])
    temp3 = numpy.array([])

    with open("cmake-build-debug/data.txt", 'r') as dataFile:
        while True:
            line = dataFile.readline()
            if not line:
                break

            data = line.split(" ")

            if len(data) == 1:
                x_list.append(temp1)
                p_list.append(temp2)
                prop_list.append(temp3)

                temp1 = numpy.array([])
                temp2 = numpy.array([])
                temp3 = numpy.array([])

            elif len(data) == 2:
                if data[0] == 'n':
                    n_list = numpy.append(n_list, int(data[1]))

                else:
                    temp1 = numpy.append(temp1, float(data[0]))
                    temp2 = numpy.append(temp2, float(data[1]))

            elif len(data) == 3:
                temp3 = numpy.append(temp3, float(data[0]))
                temp3 = numpy.append(temp3, float(data[1]))
                temp3 = numpy.append(temp3, float(data[2]))

    func = 1 / numpy.sqrt(2 * numpy.pi * 289) * numpy.exp(-(numpy.power((x_lin_list - 350), 2) / (2 * 289)))

    fig = pyplot.figure(figsize=(12, 7), dpi=100)
    fig.subplots_adjust(hspace=0.7, wspace=0.2)
    fig.suptitle('Assignment_1')
    ax = fig.add_subplot(3, 2, 1)
    ax.set(title="Gaussian Pdf".format(350))
    ax.plot(x_lin_list, func, label="mean = {}\n var = {}\n dev = {}".format(350, 289, 17))
    ax.set_xlabel('X')
    ax.set_ylabel("P(X)")
    ax.legend()
    ax.grid()

    for i in range(1, len(n_list) + 1):
        ax = fig.add_subplot(3, 2, i + 1)
        ax.set_title("n = {} pdf".format(n_list[i - 1]))
        ax.plot(x_list[i - 1], p_list[i - 1], linewidth=1,
                label="mean = {}\n var = {}\n dev = {}".format(prop_list[i - 1][0], prop_list[i - 1][1],
                                                               prop_list[i - 1][2]))
        ax.set_xlabel('X')
        ax.set_ylabel("P(X)")
        ax.legend()
        ax.grid()

    pyplot.savefig("Assignment_1.png")
    pyplot.show()

except FileNotFoundError as e:
    print(e)
