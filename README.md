# Influence Maximization
This is the implementation of Greedy++ [Zhang and Zhang, 2017].     
Full version: [sigir17full.pdf](sigir17full.pdf)

# Code
To run our code, please type the following commands:
```
g++ Greedy++.cpp -o Greedy++
./Greedy++ [Input file] [Output File] [Top-K, optional, default=20] [Directed or Undirected Graph, optional, default = Undir]
```
For example,
```
g++ Greedy++.cpp -o Greedy++
./Greedy++ data/GrQc.txt out.txt 20
```
