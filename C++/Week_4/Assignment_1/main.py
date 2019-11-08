import numpy
from matplotlib import pyplot

try:
    # differtiation
    dts_diff = numpy.array([])
    computation_times_diff = numpy.array([])
    snr_diff = numpy.array([])
    ts_diff = numpy.array([])
    originals_diff = numpy.array([])
    approxs_diff = numpy.array([])
    with open("cmake-build-debug/data_diff.txt", 'r') as dataFile:
        while True:
            line = dataFile.readline()
            data = line.split(" ")

            if not line:
                break

            # dt
            if len(data) == 1:
                dts_diff = numpy.append(dts_diff, float(data[0]))

            # elapsed time, snr
            elif len(data) == 2:
                computation_times_diff = numpy.append(computation_times_diff, float(data[0]) * pow(10, -6))
                snr_diff = numpy.append(snr_diff, float(data[1]))

            # t original approx
            else:
                ts_diff = numpy.append(ts_diff, float(data[0]))
                originals_diff = numpy.append(originals_diff, float(data[1]))
                approxs_diff = numpy.append(approxs_diff, float(data[2]))

    fig = pyplot.figure(figsize=(12, 7), dpi=100)
    fig.subplots_adjust(hspace=0.7, wspace=0.2)
    fig.suptitle('Assignment_4_diff')
    ax = fig.add_subplot(3, 2, 1)
    ax.set(title="dt = {}".format(dts_diff[0]))
    ax.plot(ts_diff[0:2], originals_diff[0:2], color='k', label=rf'original')
    ax.plot(ts_diff[0:2], approxs_diff[0:2], color='r', label=rf'approximation')
    ax.set_xlabel(r'$t$ (sec)')
    ax.set_ylabel(r'$y$')
    ax.legend()
    ax.grid()

    last = int(0.1 / dts_diff[1]) + 2
    first = int(0.1 / dts_diff[0]) + 1
    for i in range(1, len(dts_diff) - 1):
        ax = fig.add_subplot(3, 2, i + 1)
        ax.set_title("dt = {}".format(dts_diff[i]))
        ax.plot(ts_diff[first:last], originals_diff[first:last], '--', color='k', linewidth=2, label=rf'original')
        ax.plot(ts_diff[first:last], approxs_diff[first:last], 'r', linewidth=2, label=rf'approximation')
        ax.set_xlabel(r'$t$ (sec)')
        ax.set_ylabel(r'$y$')
        ax.legend()
        ax.grid()

        first = last
        if i <= 3:
            last = first + int(0.1 / dts_diff[i + 1])

    pyplot.savefig("Assignment_1_diff.png")

    # integration
    dts_integrate = numpy.array([])
    computation_times_integrate = numpy.array([])
    snr_integrate = numpy.array([])
    ts_integrate = numpy.array([])
    originals_integrate = numpy.array([])
    approxs_integrate = numpy.array([])
    with open("cmake-build-debug/data_integrate.txt", 'r') as dataFile:
        while True:
            line = dataFile.readline()
            data = line.split(" ")

            if not line:
                break

            # dt
            if len(data) == 1:
                dts_integrate = numpy.append(dts_integrate, float(data[0]))

            # elapsed time, snr
            elif len(data) == 2:
                computation_times_integrate = numpy.append(computation_times_integrate, float(data[0]) * pow(10, -9))
                snr_integrate = numpy.append(snr_integrate, float(data[1]))

            # t original approx
            else:
                ts_integrate = numpy.append(ts_integrate, float(data[0]))
                originals_integrate = numpy.append(originals_integrate, float(data[1]))
                approxs_integrate = numpy.append(approxs_integrate, float(data[2]))

    fig = pyplot.figure(figsize=(12, 7), dpi=100)
    fig.subplots_adjust(hspace=0.7, wspace=0.2)
    fig.suptitle('Assignment_4_integrate')
    ax = fig.add_subplot(3, 2, 1)
    ax.set(title="dt = {}".format(dts_integrate[0]))
    ax.plot(ts_integrate[0:2], originals_integrate[0:2], color='k', marker='o', label=rf'original')
    ax.plot(ts_integrate[0:2], approxs_integrate[0:2], color='r', marker='o', label=rf'approximation')
    ax.set_xlabel(r'$t$ (sec)')
    ax.set_ylabel(r'$y$')
    ax.legend()
    ax.grid()

    last = int(0.1 / dts_integrate[1]) + 2
    first = int(0.1 / dts_integrate[0]) + 1
    for i in range(1, len(dts_integrate) - 1):
        ax = fig.add_subplot(3, 2, i + 1)
        ax.set(title="dt = {}".format(dts_integrate[i]))
        if (i == 1):
            ax.set_ylim([-0.05, 0.05])
        ax.plot(ts_integrate[first:last], originals_integrate[first:last], '--', color='k', linewidth=2,
                label=rf'original')
        ax.plot(ts_integrate[first:last], approxs_integrate[first:last], 'r', linewidth=2, label=rf'approximation')
        ax.set_xlabel(r'$t$ (sec)')
        ax.set_ylabel(r'$y$')
        ax.legend()
        ax.grid()

        first = last
        if i <= 3:
            last = first + int(0.1 / dts_integrate[i + 1])

    pyplot.savefig("Assignment_1_integrate.png")

    fig = pyplot.figure(figsize=(12, 6), dpi=100)
    fig.subplots_adjust(hspace=0.5, wspace=0.2)
    fig.suptitle('Assignment_4_snr_versus_time')
    ax = fig.add_subplot(1, 2, 1)
    ax.set(title="snr_vs_time_diff")
    ax.plot(computation_times_diff, snr_diff, marker='o', color='g', linewidth=2, label=rf'differentiation')
    for i, txt in enumerate(dts_diff):
        ax.annotate(txt, (computation_times_diff[i], snr_diff[i]))
    ax.set_xlabel(r'$t$(ms)')
    ax.set_ylabel(r'$snr[dB]$')
    ax.legend()
    ax.grid()

    ax = fig.add_subplot(1, 2, 2)
    ax.set(title="snr_vs_time_integrate")
    ax.plot(computation_times_integrate, snr_integrate, marker='o', color='r', linewidth=2, label=rf'integration')
    for i, txt in enumerate(dts_integrate):
        ax.annotate(txt, (computation_times_integrate[i], snr_integrate[i]))
    ax.set_xlabel(r'$t$(s)')
    ax.set_ylabel(r'$snr[dB]$')
    ax.legend()
    ax.grid()

    pyplot.savefig("Assignment_1_snr_versus_time.png")

    pyplot.show()


except FileNotFoundError as e:
    print(e)
