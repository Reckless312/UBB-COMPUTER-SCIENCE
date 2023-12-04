# Import necessary libraries


import matplotlib.pyplot as plt
import numpy as np


def unit_ball(p, n_samples=1000):
    if p < 1:
        raise ValueError("Incorrect")
    points = np.random.rand(n_samples, 2) * 2 - 1
    distances = np.linalg.norm(points, ord=p, axis=1)
    points = points[distances <= 1]
    return points


p_values = [np.inf]

for p in p_values:
    points = unit_ball(p)
    plt.scatter(points[:, 0], points[:, 1], label=f"p={p}")

plt.legend()
plt.xlabel("X")
plt.ylabel("Y")
plt.title("Unit ball in 2D under different p-norms")
plt.show()
