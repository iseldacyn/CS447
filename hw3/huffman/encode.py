from sys import argv

class Tree:
    def __init__( self, label, freq, left, right ):
        self.label = label
        self.freq = freq
        self.left = left
        self.right = right

    def __eq__( self, t ):
        if self is None and t is None:
            return True
        elif self is None or t is None:
            return False
        if self.left is None and self.right is None and t.left is None and t.right is None:
            return True if ( (self.label == t.label) & (self.freq == t.freq) ) else False
        elif self.left is None and self.right is None and t.left is not None and t.right is not None:
            return False
        elif self.left is not None and self.right is not None and t.left is None and t.right is None:
            return False

        return True if ( (self.label == t.label) & (self.freq == t.freq) & (self.left == t.left) & (self.right == t.right) ) else False

    def __hash__( self ):
        return hash( (self.label, self.freq) )

def merge( t1, t2 ):
    if t1 is None:
        return t2
    elif t2 is None:
        return t1

    if t1.freq < t2.freq:
        T = Tree( t2.label+t1.label, t2.freq+t1.freq, t2, t1 )
    elif t1.freq > t2.freq:
        T = Tree( t1.label+t2.label, t1.freq+t2.freq, t1, t2 )
    else:
        T = Tree( t1.label+t2.label, t1.freq+t2.freq, t1, t2 )
    return T


# make a dictionary with encoded values from Huffman tree
def make_dict_from_tree( t ):
    if t.left is None and t.right is None:
        return {t.label: '0'}

    d = {}
    d.update( dict_from_tree( t.left, '0' ) )
    d.update( dict_from_tree( t.right, '1' ) )
    return d

# helper function
def dict_from_tree( t, s ):
    if t.left is None and t.right is None:
        return {t.label: s}

    d = {}
    d.update( dict_from_tree( t.left, s+'0' ) )
    d.update( dict_from_tree( t.right, s+'1' ) )
    return d

# encode values from freq dictionary
def encode( d ):
    # build out tree until there are no more left to merge
    T = None
    while len(d) > 1:
        # get two least frequent items in d 
        i1 = min( d, key=d.get ) 
        v1 = d[i1]
        del d[i1]
        i2 = min( d, key=d.get ) 
        v2 = d[i2]
        del d[i2]

        # merge!
        if isinstance( i1, Tree ):
            t1 = i1
        else:
            t1 = Tree( i1, v1, None, None )
        if isinstance( i2, Tree ):
            t2 = i2
        else:
            t2 = Tree( i2, v2, None, None )
        t0 = merge( t1, t2 )

        # update value in dictionary to be tree and add to main tree
        d.update( {t0: t0.freq} )

    # T is the only tree left in dictionary
    for key, _ in d.items():
        T = key
    # return dictionary of encoded characters
    return make_dict_from_tree( T )

def print_dict( d, file ):
    d = dict(sorted(d.items()))
    for i, j in d.items():
        if i == '\n':
            file.write( f'[\\n] -> {j}\n' )
        else:
            file.write( f'[{i}] -> {j}\n' )

freq = {}
with open( argv[1], "r" ) as input:
    for line in input:
        for char in line:
            if char not in freq:
                freq.update( {char: 0} )
            freq[char] += 1

encoding = encode(freq)
print_dict( encoding, open( "codewords.txt", "w" ) )

with open( argv[1], "r" ) as input:
    with open( "encoding.txt", "w" ) as output:
        for line in input:
            for char in line:
                output.write( encoding[char] )
