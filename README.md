# Bachelor
The code constructed from a regex to korotkov automata.
A korotkov automat is an nfa with Q-gram/K-mer transitions.
It is based on this lecture https://wiki.postgresql.org/images/6/6c/Index_support_for_regular_expression_search.pdf

A matrix is generated from the automata, which can be used for pattern matching.
The regex need to be written in reverse polish notation and supports the following operations:<br>
1. "|" - or <br>
2. "*" - kleene star<br>
3. "+" - min. 1<br>
4. "?" - 0 or 1<br>
5. "." - concatination<br>

example:<br>
a(b^+|c^+)d => ab+c+|.d.<br>

The Project has the following directory layout:<br>
Bachelor<br>
|-picture<br>
|-Software<br>
>|- source<br>
>|- build<br>
>|- seqan<br>

For the setup got to the build directory and run: <br>
$ cmake -DCMAKE_BUILD_TYPE=Release ../source
$ make <br>

text in brackets is the explanatory<br>
$./korotkov "ab+c+|.d."(regex) "3"(length of q-gram) "Matrix"(optianl .txt file) "Automat"(optional .dot file)<br>

the output is on now a little bit experimentel<br>
output:<br>
acd 11 [1,0,0,0,0] -- q-Gram / hashnr. / bitvec<br>
abd 7 [0,1,0,0,0]<br>
bbd 23 [0,0,1,0,0]<br>
bbb 21 [0,0,0,1,0]<br>
abb 5 [0,0,0,0,1]<br>
1 2 3  -- row of the matrix that is necessary (need to be fixed!)<br>
a b c d  -- alphabet <br>
abb bbb bbd 0 0 1 1 1 --set of q-Grams / set as bitvector<br>
abb bbd 0 0 1 0 1 <br>
abd 0 1 0 0 0 <br>
acd 1 0 0 0 0 <br>

the .dot file can be transformed int an png file with the following command.<br>
$ dot -Tpng out.dot > out.png
