----------------------- REVIEW 1 ---------------------
PAPER: 219
TITLE: Top-K Influential Nodes in Social Networks: A Game Perspective
AUTHORS: Yu Zhang and Yan Zhang


----------- Overall evaluation -----------
The paper handles an important research topic. The proposed solution is technically sound but its description is not clear enough. Performed experiments are solid and obtained results are good.

----------- Comments to the Author(s) -----------
This paper introduces a novel approach for finding top-k influential nodes in social networks. The main novelty relies on the use of a Coordination Game model. A greedy algorithm is presented for the problem, as well as some optimizations.

The target application is of wide interest of the SIGIR community. The idea of using a coordination game model for the problem is quite original. Performed experiments considered a solid evaluation protocol and obtained results are very encouraging. The main limitation of the paper refers to presentation aspects. Several key concepts are not introduced clearly, what possibly affects the reproducibility of the results (specific comments are provided below).

1. The last sentence of the abstract is confusing.
2. The introduction needs to be reorganized. The overview of the proposed solution is confusing. It is not clear how the applied heuristics work.
3. What does "N(v)" stand for in Equations 8 and 10?
4. Which modifications of Algorithm 1 are necessary to implement the proposed optimizations?
5. Description of implemented optimization is not clear.


----------------------- REVIEW 2 ---------------------
PAPER: 219
TITLE: Top-K Influential Nodes in Social Networks: A Game Perspective
AUTHORS: Yu Zhang and Yan Zhang


----------- Overall evaluation -----------
The authors in this paper position the influence maximization algorithm from a game theoretical perspective, where the influence propagation is modeled as a coordination game between users. The authors showed that under specific payoff settings in this coordination game, the proposed model serves as generalization of some existing models. Necessary properties are preserved under specific model settings, and therefore greedy algorithm can be applied to solve the problem with the same approximation rate as existing models.

----------- Comments to the Author(s) -----------
The idea of modeling influence propagation as a coordination game among users is a very interesting idea, and it will enable a more general formalization of this type of problems, e.g., capturing richer set of users’ behaviors and decisions. And some nice theoretical analysis has been provided to analyze when this model can be effectively solved with some heuristic based greedy algorithms. 

The experimental comparisons with existing models on real-world data are also very promising. 

As a conclusion, I would like to recommend accepting this paper.
