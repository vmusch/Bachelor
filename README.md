# Bachelor
The code constructed from a regex to korotkov automata.
A korotkov automat is an nfa with Q-gram/K-mer transitions.
It is based on this lecture https://wiki.postgresql.org/images/6/6c/Index_support_for_regular_expression_search.pdf

A matrix is generated from the automata, which can be used for pattern matching.
The regex need to be written in reverse polish notation and supports the following operations:
| - or
* - kleene star
+ - min. 1
? - 0 or 1
. - concatination
example:
a(b^+|c^+)d => ab+c+|.d.

text in brackets is the explanatory
$ make main
$./main "ab+c+|.d."(regex) "3"(length of q-gram) "Matrix"(optianl .txt file) "Automat"(optional .dot file)

output:
abb bbb bbd 
abb bbd 
abd 
acc ccc ccd 
acc ccd 
acd 

the .dot file can be transformed int an png file with the following command.
$ dot -Tpng out.dot > out.png
