from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt

def column(matrix, i):
    return [row[i] for row in matrix]

action = ["insert", "search", "rmin", "xmin"]
for x in action:
    filepath=[]
    if x=="insert":
        filepath.append("avl_insert.txt")
        filepath.append("rb_insert.txt")
        filepath.append("binomial_insert.txt")
    elif x=="search":
        filepath.append("avl_search.txt")
        filepath.append("rb_search.txt")
        filepath.append("binomial_search.txt")
    elif x=="rmin":
        filepath.append("avl_rmin.txt")
        filepath.append("rb_rmin.txt")
        filepath.append("binomial_rmin.txt")
    elif x=="xmin":
        filepath.append("avl_xmin.txt")
        filepath.append("rb_xmin.txt")
        filepath.append("binomial_xmin.txt")
    
    avl_list = []
    
    with open(filepath[0]) as f:
        for line in f:
            inner_list = [int(elt.strip()) for elt in line.split(' ')]
            avl_list.append(inner_list)
    
    rb_list = []
    with open(filepath[1]) as f:
        for line in f:
            inner_list = [int(elt.strip()) for elt in line.split(' ')]
            rb_list.append(inner_list)
            
    binomial_list = []
    with open(filepath[2]) as f:
        for line in f:
            inner_list = [int(elt.strip()) for elt in line.split(' ')]
            binomial_list.append(inner_list)

    avl_list.pop()
    binomial_list.pop()
    avl_X = column(avl_list, 0)
    avl_Y = column(avl_list, 1)
    bin_X = column(binomial_list, 0)
    bin_Y = column(binomial_list, 1)
    rb_X = column(rb_list, 0)
    rb_Y = column(rb_list, 1)
    
    avl_Y[:] = [x / 1000 for x in avl_Y]
    bin_Y[:] = [x / 1000 for x in bin_Y]
    rb_Y[:] = [x / 1000 for x in rb_Y]
            
    plt.scatter(avl_X,avl_Y, c='b', marker='o', label='avl tree')
    plt.scatter(bin_X, bin_Y, c='r', marker='s', label='binomial heap')
    plt.scatter(rb_X, rb_Y, c='y', marker='^', label='red-black tree')
    plt.xlabel('size of input') 
    plt.ylabel('time taken (milli sec)')        
    plt.legend(loc='upper left')
    if x=="insert":
        plt.title('Insertion')
    elif x=="search":
        plt.title("Search")
    elif x=="rmin":
        plt.title("Retrieve Minimum")
    elif x=="xmin":
        plt.title("Extract Minimum")
    plt.show()
    
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
binomial_mst = []
with open('binomial_mst.txt') as f:
    for line in f:
        binomial_list = [int(elt.strip()) for elt in line.split(' ')]
        binomial_mst.append(binomial_list)

bmstX = column(binomial_mst, 0)
bmstY = column(binomial_mst, 1)
bmstZ = column(binomial_mst, 2)

bmstZ[:] = [x / 1000 for x in bmstZ]


avl_mst = []
with open('avl_mst.txt') as f:
    for line in f:
        avl_list = [int(elt.strip()) for elt in line.split(' ')]
        avl_mst.append(avl_list)
        
amstX = column(avl_mst, 0)
amstY = column(avl_mst, 1)
amstZ = column(avl_mst, 2)

amstZ[:] = [x / 1000 for x in amstZ]

for c, m, t in [('r', 'o', 'avl'), ('b', '^', 'binomial')]:
    if t=='avl':
        ax.scatter(amstX, amstY, amstZ, c=c, marker=m, label='avl tree')
    elif t=='binomial':
        ax.scatter(bmstX, bmstY, bmstZ, c=c, marker=m, label='binomial heap')

ax.set_xlabel('vertex count')
ax.set_ylabel('edge count')
ax.set_zlabel('time taken (milli seconds)')
plt.title("Minimum Spanning Tree Comparision")
plt.legend(loc='upper left')
plt.show()