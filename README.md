# bfz
program to interpret BrainF*** 
Brainfuse. Write a program, bfz.c, that interprets a small language called Brainfuse.3 Every program in this
language is a string of characters representing instructions.
Initial setup of the machine provides a single read/write memory logically divided into two segments. In the
middle is a zero value (the fuse). To the left of the fuse is the program, to the right, its data.
fuse
-------------------------v----------------
|0|... program text ... |0| ... data ...
-------^------------------------^---------
       IP                       DP
The data area initially contains 30,000 bytes, at least, but it may be unlimited. By convention, the program is
bracketed by a 0 on the left and abuts the fuse on the right.
Execution begins with the instruction pointer pointing to the leftmost instruction in the program and generally
progresses rightward until the machine halts. The data memory is accessed by the data pointer which initially
sits just to the right of the fuse. We’ll call the target of the data pointer the accumulator . Over time, the data
pointer moves right and left. Typically, the fuse keeps the machine from interpreting instructions in the data
area. Some programs are not typical.
