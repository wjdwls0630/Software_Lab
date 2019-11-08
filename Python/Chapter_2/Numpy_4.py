import numpy

numpy.random.seed(0)

print(numpy.random.rand(5))

print(numpy.random.randn(5, 4))

# generates a million random samples from standard normal distribution
a = numpy.random.randn(1000000)

# mean
print(numpy.mean(a))

# standard deviation
print(numpy.std(a))

# generate 10 random nonnegative integers less than 12
print(numpy.random.randint(12, size=10))

print(numpy.random.randint(12, size=(4, 6)))
