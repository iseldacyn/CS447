from sys import argv

def maxI(a):
    return max(range(len(a)), key=a.__getitem__)

# probability matrix
prob = []
with open( argv[1], "r" ) as input:
    for line in input:
        line = line.split()
        curr_row = []
        for num in line:
            curr_row.append( float(num) )
        prob.append( curr_row )

# bias for heads
bias_h = []
with open( argv[2], "r" ) as input:
    for num in input:
        bias_h.append( float(num) )
# bias for tails
bias_t = []
for num in bias_h:
    bias_t.append( 1-num )

# sequence of tosses
seq = []
with open( argv[3], "r" ) as input:
    for line in input:
        line = line.split()
        for num in line:
            seq.append( int(num) )

probability = 0
probCgO = []
coinSeq = []

# initial probability calculations
if seq[0] == 0:
    # Bayes theorem, for a coin C and outcome O
    # P(C|O) = P(O)*P(O|C)/P(C)
    # P(C|O) = (0.5)*(bias_t(C))/total probability
    for i in bias_t:
        probCgO.append( .5*i )

    # total probability = sum of individual probabilities
    probability = sum(probCgO)
    for i in range(len(probCgO)):
        probCgO[i] /= probability

    # max probability is most likely coin
    coinSeq.append( maxI(probCgO) )

# repeat for heads
else:
    for i in bias_h:
        probability += i
    probability /= len(bias_h)

    for i in bias_h:
        probCgO.append( .5*i/probability )

    coinSeq.append( maxI(probCgO) )


# continue for the rest of the inputs
for i in seq[1:]:
    if i == 0:
        # P(C|O_new) = P(C|O_prev)*P(O|C)*P(C|C) + P(Cn|O)*P(O|Cn)*P(Cn|C) + ...
        # for all other coins n flipped
        newCgO = []
        for i in range(len(bias_t)):
            newCgO.append(0)
            for j in range(len(bias_t)):
                newCgO[i] += probCgO[j]*bias_t[j]*prob[j][i]

        probability = sum(newCgO)
        for i in range(len(newCgO)):
            newCgO[i] /= probability

        coinSeq.append( maxI(probCgO) )
        probCgO = newCgO

    # repeat for heads
    else:
        newCgO = []
        for i in range(len(bias_h)):
            newCgO.append(0)
            for j in range(len(bias_h)):
                newCgO[i] += probCgO[j]*bias_h[j]*prob[j][i]

        probability = sum(newCgO)
        for i in range(len(newCgO)):
            newCgO[i] /= probability

        coinSeq.append( maxI(probCgO) )
        probCgO = newCgO

# print final sequence to sequence.output and terminal
with open( "sequence.output", "w" ) as output:
    print( f'Final Sequence: ', end="")
    for i in coinSeq:
        print( f'{i} ', end="")
        output.write( f'{i} ' )
    print()


