import numpy

print(numpy.zeros((3, 2)))
print(numpy.eye(4))
print(numpy.eye(4, dtype=int))

x = numpy.random.randn(4, 2)
print(x)
print(x.T)
