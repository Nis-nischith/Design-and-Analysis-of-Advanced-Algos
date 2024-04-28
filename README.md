# Design-and-Analysis-of-Advanced-Algos
The task is to implement a dynamic - programming solution to predict the secondary structure of RNA molecule with maximum number of base pairs given a nucleotide sequence. and vizualise it.
## RNA
RNA is a basic biological molecule. It is single stranded.
RNA molecules fold into complex secondary structures.
Secondary structure often governs the behaviour of an RNA molecule.
Various rules govern secondary structure formation :
  Pairs of bases match up; each base matches with  1 other base.
  Adenine always matches with Uracil.
  Cytosine always matches with Guanine.  
  There are no kinks in the folded molecule.
### What is a secondary structure??
An secondary structure on B is a set of pairs S =  {(i , j)}, where 1 ≤ i , j ≤  n and satisfies the following rules.
  (No sharp turns) The ends of each pair are separated by at least 4 intervening bases i.e. if (i , j) ε S, then i < j - 4.
  The elements in each pair in S consist of either {A,U} or {C,G} (in either order).
  S is a matching: no base appears in more than one pair.
  (No knots) If (i,j) and (k,l) are two pairs in S, then we cannot have i < k < j < l .


