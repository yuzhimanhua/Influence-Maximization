# Top-K Influential Nodes in Social Networks: A Game Perspective
This is the implementation of [Top-K Influential Nodes in Social Networks: A Game Perspective](https://dl.acm.org/citation.cfm?id=3080709).

## Full Version
The full version of our paper can be found [**here**](https://yuzhimanhua.github.io/papers/sigir17.pdf).

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
```
@inproceedings{zhang2017top,
  title={Top-K Influential Nodes in Social Networks: A Game Perspective},
  author={Zhang, Yu and Zhang, Yan},
  booktitle={Proceedings of the 40th International ACM SIGIR Conference on Research and Development in Information Retrieval},
  pages={1029--1032},
  year={2017},
  organization={ACM}
}
```
