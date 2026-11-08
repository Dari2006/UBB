from matplotlib.pyplot import axis, plot, show
from random import random
from math import dist
from matplotlib import pyplot as plt

A = [0, 0]
B = [1, 0]
C = [1, 1]
D = [0, 1]
E = [0.5, 0.5]


axis('square')
axis((0, 1, 0, 1))
#F=[random(),random()]
#plt.plot(F[0],F[1],'ro')

inside_circle = 0
close_to_center = 0


for _ in range(0, 501):
    x = random()
    y = random()
    if dist([x, y], E) < 0.5:
        plt.plot(x, y, 'ro')
        inside_circle += 1
    else:
        plt.plot(x, y, 'bo')
plt.savefig('test.png')

for _ in range(0, 501):
    x = random()
    y = random()
    if dist([x, y], E) < min(dist([x, y], D), dist([x, y], C), dist([x, y], A), dist([x, y], B)):
        plt.plot(x, y, 'ro')
        close_to_center += 1
    else:
        plt.plot(x, y, 'bo')
plt.savefig('test1.png')

side = 0
for _ in range(0, 501):
    x = random()
    y = random()
    if dist([x, y], E) < y:
        plt.plot(x, y, 'ro')
        side += 1
    else:
        plt.plot(x, y, 'bo')
plt.savefig('test2.png')


print(f"{inside_circle/500:.2f}")
print(f"{close_to_center/500:.2f}")
print(f"{side/500:.2f}")

