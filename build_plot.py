# -*- coding: utf-8 -*-

avl_insert_list = []

def column(matrix, i):
    return [row[i] for row in matrix]

with open('avl_insert.txt') as f:
    for line in f:
        inner_list = [int(elt.strip()) for elt in line.split(' ')]
        avl_insert_list.append(inner_list)

rb_insert_list = []
with open('rb_insert.txt') as f:
    for line in f:
        inner_list = [int(elt.strip()) for elt in line.split(' ')]
        rb_insert_list.append(inner_list)
        
binomial_insert_list = []
with open('binomial_insert.txt') as f:
    for line in f:
        inner_list = [int(elt.strip()) for elt in line.split(' ')]
        binomial_insert_list.append(inner_list)

avl_insert_list.pop()
avl_X = column(avl_insert_list, 0)
avl_Y = column(avl_insert_list, 1)
bin_X = column(binomial_insert_list, 0)
bin_Y = column(binomial_insert_list, 1)
rb_X = column(rb_insert_list, 0)
rb_Y = column(rb_insert_list, 1)


import matplotlib.pyplot as plt        

plt.scatter(avl_X,avl_Y, c='b', marker='o', label='avl_build')
plt.scatter(bin_X, bin_Y, c='r', marker='s', label='binomial_build')
plt.scatter(rb_X, rb_Y, c='y', marker='o', label='red-black_build')
plt.xlabel('size of input') 
plt.ylabel('time taken')
plt.title('Scatter plot showing the build time taken by RB tree, AVL tree and Binomial Heap')
plt.legend(loc='upper left')
plt.show()