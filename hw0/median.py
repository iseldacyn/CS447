import csv
import matplotlib.pyplot as plt

med = []
with open( "median_output.csv", newline='' ) as minmax:
    reader = csv.reader( minmax )
    for row in reader:
        med.append( int(row[0]) )

x = []
y = []
for i in range(128):
    x.append(i+1)
    y.append( 10*(i+1) )

plt.plot( x, med, label="Select Median")
plt.plot( x, y )

plt.xlabel('Number of elements')
plt.ylabel('Cost Complexity')
plt.title('Select Algorithm Cost Complexity')

plt.xlim(0,128)
plt.ylim(0,1500)

plt.legend()
plt.show()
