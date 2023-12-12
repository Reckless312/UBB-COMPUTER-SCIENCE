import numpy as np
import matplotlib.pyplot as plt


def f(x, y, b):
    return 0.5 * (x**2 + b * y**2)


def gradient(x, y, b):
    return np.array([x, b * y])


def gradient_descent(x0, y0, b, learning_rate, num_iterations):
    x_values = [x0]
    y_values = [y0]

    for _ in range(num_iterations):
        grad = gradient(x_values[-1], y_values[-1], b)
        x_values.append(x_values[-1] - learning_rate * grad[0])
        y_values.append(y_values[-1] - learning_rate * grad[1])

    return x_values, y_values


def plot_contour_lines(b, x_values, y_values):
    x = np.linspace(-5, 5, 100)
    y = np.linspace(-5, 5, 100)
    X, Y = np.meshgrid(x, y)
    Z = f(X, Y, b)

    plt.figure(figsize=(8, 6))
    plt.contour(X, Y, Z, levels=np.logspace(-1, 3, 10), cmap='viridis')
    plt.scatter(x_values, y_values, c='red', marker='x', label='Gradient Descent Path')
    plt.title(f'Gradient Descent with b = {b}')
    plt.xlabel('x')
    plt.ylabel('y')
    plt.legend()
    plt.show()


b_values = [1, 0.5, 0.2, 0.1]

for b in b_values:
    x_initial, y_initial = 3, 3
    learning_rate = 0.1
    num_iterations = 50

    x_values, y_values = gradient_descent(x_initial, y_initial, b, learning_rate, num_iterations)

    plot_contour_lines(b, x_values, y_values)

