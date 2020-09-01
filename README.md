# K-Median in a directed tree

Refer : attached pdf

## Project Diary 
**Keywords** : Algorithms, Analysis of Algorithms, Combinatorial Problems, Dynamic Programming, k-median problem.
I did this project under the supervision of *Prof. Smruti Ranjan Sarangi* based on *Analysis of Algorithm* and *Dynamic Programming* during my 4 th semester. The project was aimed to compute *k-medians* in a directed tree better than the <img src="https://latex.codecogs.com/gif.latex?O(Pk^2)" /> complexity. It uses a space of <img src="https://latex.codecogs.com/gif.latex?O(nk)" /> complexity, and the implemented algorithm is **NP-hard**, whereas _dynamic programming_ is used here for efficiency. (*k* is the number of resources to be placed, *P* is the path length of tree & *n* is the number of vertices in the tree).  
The implementation was based on the research paper *An Algorithm for Finding a k-Median in a Directed Tree* $`\^1`$. We programmed the whole module in *2 phases*. The first phase contains the algorithm to compute $`||T_v||_t`$ for all possible pairs of *v* and *t* where *v* is post order number of a vertex, and *t* varies from *1* to *k*. This phase requires $`O(Pk^2)`$ time and $`O(nk)`$ space.  
The second phase was to find the location of proxies to be placed. It also required $`O(Pk^2)`$ time and $`O(nk)`$
space. It uses the data calculated in First Phase and computes $`||T_u,t||`$ for all possible values of *u* and *t*. $`||T_u,t||`$ is our minimum cost for the sub-tree rooted at u and t be the total proxies placed in sub-tree $`T_u`$ . To determine the correct position of proxies in the tree for minimum cost, we calculate $`||C_u,t||`$ and $`||N_u,t||`$ for various values of *t* from *1* to *k*.
 We run the code in parts,
debug it and find alternative approaches for the functions that were showing errors. Also we discussed the problem statements and errors and bugs with our Ph.D. seniors.
The things that I learned throughout the project are to work with a team, discuss the other more efficient algorithmic possibilities and seek guidance of seniors. This project changed my perspective towards research experiences. It developed my independent thinking and I got the courage to explore other fields as well.

For technical support in this project, VS Code and Github was used to share the code. Whole module was programmed in *CPP17*.

**Reference :**  
[1] Vigneron, Antoine; Gao, Lixin; Golin, Mordecia J.; Italiano Giuseppe F.; Li, Bo “An Algorithm for Finding a k-Median in a Direced Tree”. *Information Processing Letters*, 2000
