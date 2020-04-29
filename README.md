# Truncate a list of strings using higher order functions.

Assignment made for CPSC 213 at the University of British Columbia for the second winter term of 2019 (January-April 2020). Development was in March 2020.

Relevant concepts: memory management, function pointers

'List' structure was implemented as a dynamic array and contains several higher order functions, all of which add the mutated elements to a new list (no in-place mutation):

* map1 (map over one list)

* map2 (map, using one list to provide base elements and another list to provide arguments to the function)

* foldl (over one list)

* filter (over one list)

* for-each (over one list)

The program trunc truncates a list of strings according to a list of numbers and additionally outputs all the strings concatenated, as well as the length of the longest string in the list.

Input to trunc is a list of numbers and a list of strings in any order. For example, the input

`./trunc 4 3 5 2 3 apple peach banana grape plum`

or the input

`./trunc 4 apple 3 peach 5 banana 2 3 grape plum`

produces the output

`appl`
`pea`
`banan`
`gr`
`plu`
`appl pea banan gr plu`
`5`