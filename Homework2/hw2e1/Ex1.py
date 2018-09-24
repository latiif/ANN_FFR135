from tesst import drawPattern

def shift(string):
    return string[1:] + string[:1]

def reverse(string):
    return string[::-1]

def numberOfOnes(number):
    return binarize(number).count('1')


def calculateHash(string):
    primeNumbers = [2 ,3 ,5 ,7 ,11 ,13 ,17 ,19]
    res = 1

    while (string[0 ]!= '1') and (string[1 ]!='0'):
        string = shift(string)

    exp = 0
    index = 0
    sequence = 0
    i = 0
    while i< 4:
        if string[index] == '1':
            shouldIncreaseSequence = False
            i += 1
            j = index
            while True:
                j += 1
                if j >= len(string):
                    j = 0
                if string[j] == '0':
                    exp += 1
                    shouldIncreaseSequence = True
                if string[j] == '1':
                    break

            res *= primeNumbers[sequence] ** exp
            if shouldIncreaseSequence:
                sequence += 1
            exp = 0

        index = (index + 1) % len(string)

    return res


def binarize(number):
    res = str(bin(number))[2:]

    while len(res)!=8:
        res= '0'+res

    return res


def addHash(hash, dictionary):
    if hash in dictionary:
        dictionary[hash]    +=1
    else:
        dictionary[hash]    = 1

if __name__=="__main__":
    ec = dict()
    commons = dict()
    count = 0
    all_hashes = dict()

    for i in range(256):
        if numberOfOnes(i) == 4:
            hash = calculateHash(binarize(i))
            reverse_hash = calculateHash(reverse(binarize(i)))

            if not (hash in all_hashes):
                all_hashes[hash] = binarize(i)

            if not (reverse_hash in all_hashes):
                all_hashes[reverse_hash] = reverse(binarize(i))

            if hash==reverse_hash:
                addHash(hash,ec)
            else:
                addHash((hash,reverse_hash),commons)



    result = dict()
    to_ignore = list()
    for hash in ec:

        if hash in to_ignore:
            continue

        is_unique  = True
        mutual_count = 0
        mutual = set()
        for f,s in commons:
            if hash==f or hash==s:
                is_unique = False
                mutual.add(f)
                mutual.add(s)
                mutual_count+=commons[(f,s)]
        if is_unique:
            result[hash] = ec[hash]
        else:
            for mut in mutual:
                if (mut in ec):
                    mutual_count+=ec[mut]
                    to_ignore.append(mut)

            result[hash] = mutual_count

    print("In total we found " + str(len(result.keys())) + " symmetries")

    num_linearly_separable = 0
    for hash in result:
        print(str(result[hash])+" functions belong to the symmetry "+all_hashes[hash])
        if drawPattern(all_hashes[hash]):
            num_linearly_separable+=result[hash]

    print(num_linearly_separable)

