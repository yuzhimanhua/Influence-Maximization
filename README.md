# Influence Maximization
This is the implementation of Greedy++ [Zhang and Zhang, 2017] as well as the baseline methods compared in the paper.     
Full version: [sigir17full.pdf](sigir17full.pdf)

# Code
To run our code, please type the following commands:
```
g++ [Algorithms.cpp] -o [Algorithms]
./[Algorithms] [Input file] [Output File] [Top-K, optional, default=20] [Directed or Undirected, optional, default = Undir]
```
For example,
```
g++ Greedy++.cpp -o Greedy++
./Greedy++ data/GrQc.txt out.txt 20
```
