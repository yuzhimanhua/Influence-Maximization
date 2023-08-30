# Top-K Influential Nodes in Social Networks: A Game Perspective

[![License](https://img.shields.io/badge/License-Apache_2.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)

This repository contains the source code for [**Top-K Influential Nodes in Social Networks: A Game Perspective**](https://arxiv.org/pdf/1810.05959.pdf).

## Full Version
The full version of our paper can be found [**here**](https://arxiv.org/pdf/1810.05959.pdf).

## Code
To run our code, please type the following commands:
```
g++ Greedy++.cpp -o Greedy++
./Greedy++ [Input file] [Output File] [Top-K, optional, default=20] [Directed or Undirected Graph, optional, default = 'U']
```
For example,
```
g++ Greedy++.cpp -o Greedy++
./Greedy++ data/GrQc.txt out.txt 20
```
The output will have _k_ lines. Each line includes two numbers: Node ID, Estimated Marginal Gain (based on the snapshots).
For example,
```
131 39.020000
124 35.669998
639 35.570000
100 32.230000
15 26.719999
```
To accurately calculate the influence of the selected seed set, please use
```
g++ Calc_Inf.cpp -o Calc_Inf
./Calc_Inf [Network File] [Seed Node File] [Top-K, optional, default=20] [Directed or Undirected Graph, optional, default = 'U']
```
For example,
```
g++ Calc_Inf.cpp -o Calc_Inf
./Calc_Inf data/Epinions.txt out.txt  5  D
```

## Citation
If you find this repository useful, please cite the following paper:
```
@inproceedings{zhang2017top,
  title={Top-K Influential Nodes in Social Networks: A Game Perspective},
  author={Zhang, Yu and Zhang, Yan},
  booktitle={SIGIR'17},
  pages={1029--1032},
  year={2017},
  organization={ACM}
}
```
