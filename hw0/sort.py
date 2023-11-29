import csv
import matplotlib.pyplot as plt

ssort = []
isort = []
msort = []
qsort_f = []
qsort_m = []
with open( "sort_output.csv", newline='' ) as minmax:
    reader = csv.reader( minmax )
    for row in reader:
        ssort.append( int(row[0]) )
        isort.append( int(row[1]) )
        msort.append( int(row[2]) )
        qsort_f.append( int(row[3]) )
        qsort_m.append( int(row[4]) )

x = []
for i in range(128):
    x.append(i+1)

plt.plot( x, ssort, label="Selection Sort")
plt.plot( x, isort, label="Insertion Sort")
plt.plot( x, msort, label="Merge Sort")
plt.plot( x, qsort_f, label="Quick Sort (fixed)")
plt.plot( x, qsort_m, label="Quick Sort (median)")

plt.xlabel('Number of elements')
plt.ylabel('Cost Complexity')
plt.title('Sorting Algorithm Cost Complexity')

plt.xlim(0,128)
plt.ylim(0,8500)

plt.legend()
plt.show()
