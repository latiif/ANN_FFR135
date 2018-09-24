from random import randint

N = 4
w, h = N, N
W = [[0 for x in range(w)] for y in range(h)]

p1 = [-1, 1, 1, 1]

patterns = [p1]

# learn the patterns

for p in patterns:
    for i in range(N):
        for j in range(i,N):
            if i != j:
                W[i][j] +=  p[i] * p[j]
            else:
                W[i][j] = 0
            W[j][i] = W[i][j]

question = [1, 1,1, 1]

output = list(question)


for t in range(1000):

    i = randint(0, N-1)

    res = output[i]
    for j in range(N):
        res += W[i][j] * output[j]

    if res < 0:
        output[i] = -1
    elif res > 0:
        output[i] = 1

    ## check for convergance
    converged = False
    for p in patterns:
        if p == output:
            print("Converged")
            converged = True
            print(t)
            break

    if converged:
        break

print(question)
print(output)