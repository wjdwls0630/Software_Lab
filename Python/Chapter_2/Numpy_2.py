import numpy

a_1 = numpy.array([1, 2, 3])  # this creates a 1d array
a_2 = numpy.array([[1, 2, 3]])  # this creates a 2d array, which is different from the above
a_3 = numpy.array([[1], [2], [3]])  # this creates a 2d array, which is different from the above

print(a_1)
print(a_2)
print(a_3)

print(a_1.shape)
print(a_2.shape)
print(a_3.shape)

a = numpy.ones(5)  # this creates a 1d array with all ones
print(a)
print(a.shape)

b = numpy.ones((5, 3))  # this creates a 2d array with all ones
print(b)
print(b.shape)
