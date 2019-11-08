import numpy

x = numpy.array([[1, 2, 3], [4, 5, 6], [7, 8, 9], [10, 11, 12]])
v = numpy.random.randn(3)  # random noise
y = numpy.zeros(x.shape)  # creates a zero matrix with the same shape as x

for i in range(x.shape[0]):
    y[i, :] = x[i, :] + v
print(y)

print(x)

vv = numpy.tile(v, (x.shape[0], 1))  # Stack 4 copies of v on top of each other
y = x + vv
print(y)

y = x + v
print(y)

# outer product
v = numpy.array([1, 2, 3])  # v has shape (3,)
w = numpy.array([4, 5])  # w has shape (2,)
x = v.reshape(3, 1) * w
print(x)

# adding a vector to each row of a matrix
x = numpy.array([[1, 2, 3], [4, 5, 6]])
print(x + v)

# adding a vector to each column of a matrix
print(x + w.reshape(2, 1))
