from sys import argv
from math import log2

table = {}
curr_i = ''
curr_s = ''
length, index = 0, 0
table.update( { index: ('', length) } )
index += 1
i = 0
with open( argv[1], "r" ) as input:
    with open( argv[2], "w" ) as output:
        for line in input:
            for char in line:
                # iterate through file by length
                if i < length:
                    curr_i += char
                    i += 1
                    continue

                # add new index to table and write
                num = 0
                for c in range(len(curr_i)):
                    num += pow(2, c) * int(curr_i[-c-1])
                curr_s, _ = table[num]
                curr_s += char
                output.write( f'{curr_s}' )
                length = int(log2(index) + 1)
                table.update( {index: (curr_s, length)} )
                index += 1
                curr_i = ''
                i = 0
        
        # repeat for last char
        num = 0
        for c in range(len(curr_i)):
            num += pow(2, c) * int(curr_i[-c-1])
        curr_s, _ = table[num]
        output.write( f'{curr_s}' )
