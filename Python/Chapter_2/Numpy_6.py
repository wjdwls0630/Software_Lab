import numpy

x = numpy.arange(-4, 6, 0.5)
print(x)

# two of these are same
print(numpy.linalg.norm(x))
print(numpy.linalg.norm(x, 2))

# two of these are same
print(numpy.linalg.norm(x, 1))
print(sum(abs(x)))

print(numpy.linalg.norm(x, numpy.inf))
print(numpy.max(abs(x)))
