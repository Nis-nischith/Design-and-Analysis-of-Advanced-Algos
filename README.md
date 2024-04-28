<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
</head>
<body>

<h1>Design and Analysis of Advanced Algorithms</h1>

<h2>Task Description</h2>
<p>The goal is to implement a dynamic programming solution to predict the secondary structure of an RNA molecule, maximizing the number of base pairs, given a nucleotide sequence, and visualize the structure.</p>

<h2>RNA</h2>
<ul>
    <li>RNA is a fundamental biological molecule and is single-stranded.</li>
    <li>RNA molecules fold into complex secondary structures that often govern their behavior.</li>
</ul>

<h2>Rules for Secondary Structure Formation:</h2>
<ul>
    <li>Bases pair up; each base matches with one other base.</li>
    <li>Adenine (A) always pairs with Uracil (U).</li>
    <li>Cytosine (C) always pairs with Guanine (G).</li>
    <li>The folded molecule has no kinks.</li>
</ul>

<h2>What is a Secondary Structure?</h2>
<p>A secondary structure on sequence B is a set of pairs S = {(i, j)} where 1 ≤ i, j ≤ n, satisfying:</p>
<ul>
    <li><strong>No sharp turns:</strong> The ends of each pair are separated by at least 4 intervening bases, i.e., if (i, j) ∈ S, then i &lt; j - 4.</li>
    <li>The pairs consist of either {A,U} or {C,G} (in either order).</li>
    <li><strong>Matching rule:</strong> No base appears in more than one pair.</li>
    <li><strong>No knots:</strong> If (i, j) and (k, l) are two pairs in S, then we cannot have i &lt; k &lt; j &lt; l.</li>
</ul>

</body>
</html>



