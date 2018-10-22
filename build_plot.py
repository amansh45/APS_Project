# -*- coding: utf-8 -*-

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
    
    import matplotlib.pyplot as plt        
    plt.scatter(avl_X,avl_Y, c='b', marker='o', label='avl_build')
    plt.scatter(bin_X, bin_Y, c='r', marker='s', label='binomial_build')
    plt.scatter(rb_X, rb_Y, c='y', marker='o', label='red-black_build')
    plt.xlabel('size of input') 
    plt.ylabel('time taken (milli sec)')        
    plt.legend(loc='upper left')
    plt.show()