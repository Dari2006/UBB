#urna cu 5 bile R, 3 A, 32 V, se extrag 3 bile fara returnare
#A: "cel putin o bila e R:
#B: "toate au aceeasi culoare"
#P(B|A) -> estimarea

from math import comb
from random import sample, random

from matplotlib import pyplot as plt


def prob_cond(nr_sim):
    countA, countB = 0, 0
    for _ in range(nr_sim):
        bile_extrase = sample(['red','blue','green'],counts=[5,3,2],k=3)
        if 'red' in bile_extrase:
            countA+=1
            if len(set(bile_extrase))==1:
                countB+=1
    return countB/countA


#print(comb(3,2))


A = 1 - comb(5, 3)/comb(10,3)



print(A)



#EX2
from random import randrange
from matplotlib.pyplot import bar, hist, grid, show, legend
import matplotlib.pyplot

data = [randrange(1,7) for _ in range(500)]  #cele 500 de val

bin_edges = [k+0.5 for k in range(7)]  #intervale centrate in valorile k = 1...6 : 0.5 ---> 6.5

plt.hist(data, bin_edges, density = True, rwidth = 0.9, color = 'green', edgecolor = 'black',
    alpha = 0.5, label = 'frecvente relative')

distribution = dict([(i, 1//6) for i in range(1,7)])  #fiecarei val ii atasam prob teoretica corespunzatoare

plt.bar(distribution.keys(), distribution.values(), width = 0.85, color = 'red', edgecolor = 'black',
    alpha = 0.6, label = 'probabilitati')

legend(loc = 'lower left')
grid()

plt.show()



#EX 3
from scipy.stats import binom
#model binomial -> parametri teoretici: n = 5, p  = 0.6

#a)
n = 5
p = 0.6
x = binom.rvs(n, p, size = 1000)     #1000 de valori ale experimentului; extrag 5 bile cy ret si adun cifele inscriptionate

#b)  histograma cu data  - x,   bin.edges => 0.5 -> 5.5
#prob teoretice: fiecarei valori k 0..5 ii asociem prob teoretica P(x = k) si folosim binom.pmf(k, n, p)

edges = [k+0.5 for k in range(-1,6)]
distribution = dict([(i, binom.pmf(i, n, p)) for i in range(0,6)])
plt.bar(distribution.keys(), distribution.values(), width = 0.85, color = 'red', edgecolor = 'black',
    alpha = 0.6, label = 'probabilitati')
plt.hist(x, edges)
plt.grid()
plt.show()


import random
#c) estimare P(1 < X <= 4): verificat cate valori din X respectaw condirtia si impartim la nr total de valori(1000)
#teoretic: binom.cdf(k, n, p) = P(x <= k)   ;   P(1<x<=4) = P(x<=4) - P(x <= 1)

#nr valori intre 2 si 4
estimare = sum((x > 1) & (x <= 4)) / 1000
print(estimare)

p_teoretica = binom.cdf(4, 5, 0.6) - binom.cdf(1, 5, 0.6)

print(f"teoretic 3c: {p_teoretica}")




#4
#a)
#lista input
v = [random.randint(1, 1000) for _ in range(100)]

#k vom avea k elem random din v
k = random.randint(1, 100)

#lista cu cele k elem
w = random.sample(v, k)

#maximul
maxim = max(w)
print(f"maxim 4a : {maxim}")

#b)
cnt = 0
v2 = [i for i in range(1, 101)]
for _ in range(10000):
    k = random.randint(1, 100)
    w = random.sample(v2, k)
    if max(w) == 100:
        cnt += 1

print(cnt/10000)


#c)


#print(prob_cond(5000))


