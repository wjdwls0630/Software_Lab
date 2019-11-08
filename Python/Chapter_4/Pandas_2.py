import numpy
import pandas
from matplotlib import pyplot

df = pandas.read_csv('https://web.stanford.edu/~hastie/Papers/LARS/diabetes.data', delimiter='\t')
print(df)

print(df.loc[df['AGE'].idxmin()])

print(df['BMI'].mean())

# same as df['BMI'].mean()
print(numpy.mean(df['BMI']))

pyplot.figure()
pyplot.plot(df['BP'], df['BMI'], 'o', alpha=0.5)
pyplot.xlabel('BP')
pyplot.ylabel('BMI')
pyplot.grid(True)
pyplot.savefig("Pandas_2.png")
pyplot.show()
