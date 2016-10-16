# shellSort

This program is an implementation of the shell short for linked lists. The choice of gap sequences used are those originally given by Shell: for a list of length N, floor(N/2), floor(N/4),...,floor(N/(2^i)),...,1 are the gaps used for the intermediate k sorts.

The programs reads an input file (here called listOfNum.dat). bigListOfNum.dat and smallListOfNum.dat are two test cases (both composed of random unique integers).

The program also compares the shell sort against a insertion sort on the same set of numbers and outputs the CPU time taken for each. For the bigListOfNum (60,000ish intgers) we see the shell implementation is 25% faster. The program has to create many sub linked lists and so the overhead of doing so means the algorithms efficiency is only seen for larger lists.
