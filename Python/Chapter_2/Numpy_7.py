import numpy

A = numpy.random.randn(10, 5)
numpy.linalg.norm(A, 2)

U, S, V = numpy.linalg.svd(A)  # singular value decomposition of A
print(S)

A = numpy.random.randn(10, 10)
w, v = numpy.linalg.eig(A)  # eigenvalues and eigenvectors of A
print(w)  # print eigenvalues of A

A = numpy.array([[1, 2], [3, 4]])
norm_A_fro = numpy.linalg.norm(A, 'fro')
print(norm_A_fro ** 2)

n = 1000;
x = numpy.random.randn(n);
A = numpy.random.randn(1000, 1000)
y = numpy.dot(A, x)
x_hat = numpy.linalg.solve(A, y)

print(numpy.linalg.norm(x))
print(numpy.linalg.norm(x_hat - x))

print(x[0:10])
print(x_hat[0:10])
