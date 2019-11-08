import pandas
from matplotlib import pyplot

df = pandas.read_csv('Pandas_1.csv', delimiter=',')

print(df.shape)  # show the size of the dataframe
print(df.head(10))  # show the first 10 rows

print(list(df))

pyplot.figure()
pyplot.plot(df['Time'], df['Yaw'])
pyplot.plot(df['Time'], df['Pitch'])
pyplot.plot(df['Time'], df['Roll'])
pyplot.grid(True)
pyplot.legend()
pyplot.xlabel("Time (s)")
pyplot.ylabel("Euler angles (deg)")
pyplot.title("Euler angles")
pyplot.savefig("Pandas_1.png")
pyplot.show()
