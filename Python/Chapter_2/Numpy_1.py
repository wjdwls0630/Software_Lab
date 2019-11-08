import numpy

a = numpy.array([1, 2, 3])  # this creates a 1d array
b = numpy.array([[4, 5, 6], [7, 8, 9]])  # this creates a 2d array

type(a), type(b)

print(a[0])  # accessing an element in a 1d array
print(a[1:])  # accessing elements in a 1d array
print(b[1, 1])  # accessing an element in a 2d array
print(b[:, ::2])  # accessing elements in a 2d array

# change element
b[1, 1] = -8
print(b)
