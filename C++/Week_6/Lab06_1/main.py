# from calculation, we expect that the local minimum occurs at x = 9/4

x_old = 0
x_new = 6  # the algorithm is starts at x = 6
eps = 10 ** (-2)  # step size
precision = 10 ** (-6)


def f_prime(x):
    return 4 * x ** 3 - 9 * x ** 2


while abs(x_new - x_old) > precision:
    x_old = x_new
    x_new = x_old - eps * f_prime(x_old)

print("Local minimum occurs at x  = {}".format(x_new))
print("we expectt x = 9/4 = {}".format(9 / 4))
