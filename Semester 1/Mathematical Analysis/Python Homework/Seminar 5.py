import numpy as np
import matplotlib.pyplot as plt
from typing import Callable


"""
Homework for seminar 5
Name : Cora Ioan Alexandru
Group : 912
"""

"""
Problem statement:
    Let f : R → R be differentiable.
    To minimize f, consider the gradient descent method x(the n+1 th) = x(the n th) − η f′(x(n th), where x(first) ∈ R and learning rate > 0.
    (a) Take a convex f and show that for small learning rate the method converges to the minimum of f.
    (b) Show that by increasing learning rate, the method can converge faster (in fewer steps).
    (c) Show that taking learning rate too large might lead to the divergence of the method.
    (d) Take a non-convex f and show that the method can get stuck in a local minimum.
"""

"""
Implementing the Gradiant Descent Algorithm
"""


def gradient_descent(start: float, gradient: Callable[[float], float], list_of_x: list, list_of_y: list,
                     learn_rate: float, max_iter: int, tol: float = 0.01):
    x = start
    steps = [start]
    list_of_x.append(start)
    list_of_y.append(func1(start))
    for _ in range(max_iter):
        diff = learn_rate * gradient(x)
        if np.abs(diff) < tol:
            break
        x = x - diff
        list_of_x.append(x)
        list_of_y.append(func1(x))
        steps.append(x)
    return list_of_x, list_of_y


"""
Point a)
"""


def func1(x: float):
    return -(x ** 2) - 4 * x + 1


def gradient_funct1(x: float):
    return 2 * x - 4


x, y = gradient_descent(9, gradient_funct1, [], [], 0.9, 100)
plt.plot(x, y)
plt.xlabel('x - axis')
plt.ylabel('y - axis')
plt.title('Exercise d')
plt.show()
import numpy as np


def f(x):
    return np.e ** (-(x ** 2))


a = 5

x = np.linspace(-a, a, 1000)
y = f(x)

result = np.trapz(y, x)
print(result)
