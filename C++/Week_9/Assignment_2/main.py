import numpy
from matplotlib import pyplot

try:
    # value
    x_bi_list = []
    x_po_list = []
    p_bi_list = []
    p_po_list = []

    n_list = numpy.array([])

    temp1 = numpy.array([])
    temp2 = numpy.array([])
    temp3 = numpy.array([])
    temp4 = numpy.array([])

    bi_or_po = True  # True -> bi False -> po

    with open("cmake-build-debug/data.txt", 'r') as dataFile:
        while True:
            line = dataFile.readline()
            if not line:
                break

            data = line.split(" ")

            if len(data) == 1:
                if data[0] == "binomial\n":
                    bi_or_po = True
                elif data[0] == "poisson\n":
                    bi_or_po = False
                else:
                    if bi_or_po == True:
                        x_bi_list.append(temp1)
                        p_bi_list.append(temp2)
                    else:
                        x_po_list.append(temp1)
                        p_po_list.append(temp2)

                    temp1 = numpy.array([])
                    temp2 = numpy.array([])

            elif len(data) == 2:
                if data[0] == 'n':
                    n_list = numpy.append(n_list, int(data[1]))

                else:
                    temp1 = numpy.append(temp1, float(data[0]))
                    temp2 = numpy.append(temp2, float(data[1]))

    fig = pyplot.figure(figsize=(12, 7), dpi=100)
    fig.subplots_adjust(hspace=0.7, wspace=0.2)
    fig.suptitle('Assignment_2_binomial vs poisson')

    for i in range(1, len(n_list) + 1):
        ax = fig.add_subplot(2, 2, i)
        ax.set_title("n = {} pdf".format(n_list[i - 1]))
        ax.plot(x_bi_list[i - 1], p_bi_list[i - 1], color='k', linewidth=1, label="binomial")
        ax.plot(x_po_list[i - 1], p_po_list[i - 1], color='r', linewidth=1, label="poisson")
        ax.set_xlabel(r'$x$')
        ax.set_ylabel(r'$p_X(x)')
        ax.legend()
        ax.grid()

    pyplot.savefig("Assignment_2.png")
    pyplot.show()

except FileNotFoundError as e:
    print(e)
