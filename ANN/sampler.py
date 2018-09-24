from random import sample, choice

p = 0

for i in range(1000000):
    a = choice([-1,1],)
    if (a==-1):
        p+=1


print(p/100000)