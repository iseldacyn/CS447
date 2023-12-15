from sys import argv

def print_dict( d ):
    d = dict(sorted(d.items()))
    for i, j in d.items():
        if i == '\n':
            print( f'[\\n] -> {j}' )
        else:
            print( f'[{i}] -> {j}' )

# get codewords from codeword file
codes = {}
with open( argv[2], "r" ) as codewords:
    for encoding in codewords:
        encoding = encoding.split(' -> ')
        # for special characters \x
        key = str(encoding[1][:-1])
        if encoding[0][1] == '\\' and encoding[0][2] != ']':
            val = encoding[0][1] + encoding[0][2]
            codes.update( {key: val} )
        else:
            codes.update( {key: encoding[0][1]} )

print_dict( codes )

code = ""
with open( argv[1], "r" ) as encoding:
    with open( "decoding.txt", "w" ) as decoding:
        for line in encoding:
            for c in line:
                if c == '\n':
                    continue
                code += c

                if code in codes:
                    if codes[code] == '\\n':
                        decoding.write( f'\n' )
                    else:
                        decoding.write( codes[code] )
                    code = ""
