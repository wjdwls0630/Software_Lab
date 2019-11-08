from matplotlib import pyplot

try:
    t = []
    result = []
    with open("cmake-build-debug/data.txt", 'r') as dataFile:
        while True:
            line = dataFile.readline()  # read one line

            if not line:
                break

            data = line.split(" ")  # save data
            t.append(float(data[0]))  # save in time array
            result.append(float(data[1]))  # save in result array

    t_alias = []
    result_alias = []
    with open("cmake-build-debug/data_alias.txt", 'r') as dataFile_alias:
        while True:
            line = dataFile_alias.readline()  # read one line

            if not line:
                break

            data = line.split(" ")  # save data
            t_alias.append(float(data[0]))  # save in time array
            result_alias.append(float(data[1]))  # save in result array

    # plot results
    pyplot.figure(dpi=100, figsize=(8, 6))
    pyplot.plot(t, result, label=rf'Sampling')
    pyplot.plot(t_alias, result_alias, label=rf'Sampling_alias')
    pyplot.title("Lab04_1")
    pyplot.xlabel(r'$t$ (sec)')
    pyplot.ylabel(r'$y$')
    pyplot.legend()
    pyplot.grid()
    pyplot.savefig("Lab04_1.png")
    pyplot.show()

except FileNotFoundError as e:
    print(e)
