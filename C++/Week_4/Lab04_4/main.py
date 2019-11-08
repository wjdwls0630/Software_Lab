import numpy
from matplotlib import pyplot

try:
    dts = numpy.array([])
    sampling_freqs = numpy.array([])
    ts = numpy.array([])
    originals = numpy.array([])
    approxs = numpy.array([])
    with open("cmake-build-debug/data.txt", 'r') as dataFile:
        while True:
            line = dataFile.readline()
            data = line.split(" ")

            if not line:
                break

            if len(data) == 2:
                dts = numpy.append(dts, float(data[0]))
                sampling_freqs = numpy.append(sampling_freqs, float(data[1]))
            else:

                ts = numpy.append(ts, float(data[0]))
                originals = numpy.append(originals, float(data[1]))
                approxs = numpy.append(approxs, float(data[2]))

    ts = ts.reshape(len(dts), 50)
    originals = originals.reshape(len(dts), 50)
    approxs = approxs.reshape(len(dts), 50)

    # plot results
    for i in range(0, len(dts)):
        pyplot.figure(dpi=100, figsize=(8, 6))
        pyplot.title("Lab04_4_dt = {}".format(dts[i]))
        pyplot.plot(ts[i], originals[i],
                    label=rf'original,' + " dts={}, smp_freq = {}".format(dts[i], sampling_freqs[i]))
        pyplot.plot(ts[i], approxs[i],
                    label=rf'apporximation,' + " dts={}, smp_freq = {}".format(dts[i], sampling_freqs[i]))
        pyplot.xlabel(r'$t$ (sec)')
        pyplot.ylabel(r'$y$')
        pyplot.legend()
        pyplot.grid()
        pyplot.savefig("Lab04_4_dt={}.png".format(dts[i]))

    pyplot.show()

except FileNotFoundError as e:
    print(e)
