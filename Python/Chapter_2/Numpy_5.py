import numpy

a = numpy.random.randn(100)
b = numpy.random.randn(100)
c = numpy.dot(a, b)
print(c)

A = numpy.random.randn(100, 50)
B = numpy.random.randn(50, 20)
C = numpy.dot(A, B)
print(C.shape)

C2 = A @ B  # It is equal to numpy.dot(A, B)
print(numpy.max(abs(C - C2)))  # check if C and C2 are equal

A = numpy.random.randn(100, 50)
b = numpy.random.randn(50)
C = numpy.dot(A, b)
print(C.shape)

C2 = A @ b  # It is equal to numpy.dot(A, b)
print(numpy.max(abs(C - C2)))  # check if C and C2 are equal
