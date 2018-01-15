# HierachicalCluster
A HierachicalCluster Algorithm with c++
Hierarchical clustering (also called hierarchical cluster analysis or HCA) is a method of cluster analysis which seeks to build a hierarchy of clusters.
In general, the merges and splits are determined in a greedy manner. The results of hierarchical clustering are usually presented in a dendrogram.

In the standard algorithm for hierarchical agglomerative clustering (HAC) has a time complexity of On^3 and requires On^2 memory, which makes it too slow for even medium data sets. However, for some special cases, optimal efficient agglomerative methods of complexity On^2 are known: SLINK[2] for single-linkage and CLINK[3] for complete-linkage clustering. With a heap the runtime of the general case can be reduced to O(n^2) at the cost of further increasing the memory requirements. In many programming languages, the memory overheads of this approach are too large to make it practically usable.

Except for the special case of single-linkage, none of the algorithms (except exhaustive search in O(n^2) can guaranteed to find the optimum solution.
Divisive clustering with an exhaustive search is O(n^2), but it is common to use faster heuristics to choose splits, such as k-means.

The following graphs are the steps of clustering in hierachically.
We try the data with 3-dimension such as:
double data[8][3] = {{1.00,1.00,1.00},{5.00,5.00,0.00},{2.00,4.00,3.00},{1.00,1.00,0.00},{6.00,4.00,-1.00},{-1.00,1.00,1.00},{6.00,0.00,0.00},{7.00,0.00,0.00}};
The value of the red block is the minimum of the distance in this generation.
Also the red block in the table is the intersections of the yellow blocks and the green blocks.the red block will be set will value of 0 in each generation.
The yellow blocks divided into two parts.On one part,the column of the yellow blocks was equal to the red block's row.On another part,the row was equal to the red blocks'row.
And for the green parts,they also divide into two parts.On one part,the column of the green blocks was equal to the red block's column.On another part,the row was equal to the
block's row.
You can also realize that the number of the yellow blocks is the same as the green blocks which equals to the number of the nodes minus one.
The yellow and green block correspond with each other in order.Such as the first yellow block corresponds with the first block in green.Let use Y[i] and G[i] to stand for the i block in the yellow or the green queue.
If the Y[i] < G[i] and Y[i] > 0,the G[i] will be set as 0.If the Y[i] > G[i],the Y[i] will be covered with G[i] and G[i] will be zero.In the end,if Y[i] equals to G[i] and both of them are greater than zero,the green
block will be set at zero.
![GitHub](https://github.com/leungs/HierachicalCluster/blob/master/HierarchicalCluster/0.png?raw=true "GitHub,Social Coding")
![GitHub](https://github.com/leungs/HierachicalCluster/blob/master/HierarchicalCluster/1.png?raw=true "GitHub,Social Coding")
![GitHub](https://github.com/leungs/HierachicalCluster/blob/master/HierarchicalCluster/2.png?raw=true "GitHub,Social Coding")
![GitHub](https://github.com/leungs/HierachicalCluster/blob/master/HierarchicalCluster/3.png?raw=true "GitHub,Social Coding")
![GitHub](https://github.com/leungs/HierachicalCluster/blob/master/HierarchicalCluster/4.png?raw=true "GitHub,Social Coding")
![GitHub](https://github.com/leungs/HierachicalCluster/blob/master/HierarchicalCluster/5.png?raw=true "GitHub,Social Coding")
![GitHub](https://github.com/leungs/HierachicalCluster/blob/master/HierarchicalCluster/6.png?raw=true "GitHub,Social Coding")
![GitHub](https://github.com/leungs/HierachicalCluster/blob/master/HierarchicalCluster/7.png?raw=true "GitHub,Social Coding")
