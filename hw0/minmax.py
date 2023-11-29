import csv
import matplotlib.pyplot as plt

mm_rec = []
mm_iter = []
with open( "minmax_output.csv", newline='' ) as minmax:
    reader = csv.reader( minmax )
    for row in reader:
        mm_rec.append( int(row[0]) )
        mm_iter.append( int(row[1]) )

x = []
y1 = []
y2 = []
for i in range(1000):
    x.append(i+1)
    y1.append( 1.5*(i+1) - 2 )
    y2.append( 2*(i+1) - 3 )

plt.plot( x, y1 )
plt.plot( x, y2 )
plt.plot( x, mm_rec, label="recursive")
plt.plot( x, mm_iter, label="iterative")

plt.xlabel('Number of elements')
plt.ylabel('Cost Complexity')
plt.title('MinMax Algorithm Cost Complexity')

plt.xlim(0,1000)
plt.ylim(0,2000)

plt.legend()
plt.show()
