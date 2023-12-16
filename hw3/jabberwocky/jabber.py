from sys import argv
from math import log2

table = {}
prefix = ''
curr_s = ''
length, index = 0, 0
# initialize table
table.update( {"": (index, length)} )
index += 1
with open( argv[1], "r" ) as input:
    with open( argv[2], "w" ) as output:
        for line in input:
            for char in line:
                curr_s += char
                # found new character not in table
                if curr_s not in table:
                    curr_l = log2(index) + 1
                    table.update( {curr_s: (index, curr_l)} )
                    
                    # print string from prefix and current string
                    i, _ = table[prefix]
                    i = format( i, '08b' )
                    output.write( f'{i[8-length:]}{char}' )
                    # update maximum length
                    if curr_l > length:
                        length = int(curr_l)
                    index += 1
                    curr_s = ''
                else:
                    prefix = curr_s

        # print out any remaining prefixes
        if prefix != "":
            i, _ = table[prefix]
            i = format( i, '08b' )
            output.write( f'{i[8-length:]}' )
