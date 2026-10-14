from itertools import combinations_with_replacement
from random import sample


sortimente = ["Ananas", "Ciocolata", "Fistic", "Kiwi", "Mango", "Vanilie", "Zmeura"]

#print(help(combinations_with_replacement))

res = combinations_with_replacement(sortimente, 3)

for sortiment in res:
    for sort in sortiment:
        print(sort[0], end="")
    print()