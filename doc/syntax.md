# Formalizing the *fox* syntax

The following railroad diagrams define the *fox* language syntax. You read these diagrams from left to right, following the paths like a train on rails. You will encounter forks and loops, and that's just about it. Couldn't be easier.

The diagrams in this document will allow you to precisely tell valid from invalid *fox* code. Studying this information will not be necessary for most people who are just looking to program in *fox* - but it's absolutely essential for developing the language itself and even more so for writing *fox* compilers.

All railroad diagrams have been created with [this](http://tabatkins.github.io/railroad-diagrams) tool. You will find the source for all these diagrams in this repository as well.


# Source File

![](img/railroad-src-file.svg)

This first diagram describes the flow of an entire *fox* source file. It's extremely simple: A *fox* source file is just a number of instructions stringed together with optional spacers before and after each instruction.

Note that all files **have** to end in a `'\0'`, which marks the end of the file. An otherwise empty file is absolutely valid however, and you can see that there is a path that leads from the beginning straight to the ending character.

Here are some examples for possible paths through the above diagram, each of these describe a valid *fox* source file:

- `'\0'`
- `spacer '\0'`
- `instruction '\0'`
- `spacer spacer '\0'`
- `instruction instruction '\0'`
- `spacer instruction '\0'`
- `instruction spacer '\0'`
- `spacer instruction spacer '\0'`
- `instruction spacer instruction '\0'`

And these are examples for **invalid** *fox* source files:

- `spacer spacer` (a `spacer` can never be followed by another `spacer`)
- `instruction instruction` (missing `'\0'` at end) 

But what exactly is a `spacer`? And what's an `instruction`? Let's define these elements with, you guessed it, more railroad diagrams!


# Spacer

![](img/railroad-spacer.svg)

A `spacer` is just a sequence of whitespaces or tabs. So far, they have just been used to optionally separate the different instructions that make up a *fox* program. This is just so that programmers are free to format *fox* code the way they like, with any amount of extra whitespaces or tabs.

But it's important to note that a `spacer` as seen in the diagram above does require at least one whitespace or tab. This is because they are also used within some instructions, to seperate some keywords from a following `identifier` for example. Note that the first diagram, the one that describes entire source files, has an extra path circumventing just the `spacer`. If it weren't for that optional skip, every *fox* instruction would have to be surrounded by at least one whitespace or tab. Before and after. That would get very tedious very fast, if you ask me.

Let's look at some `spacer` examples:

- `' '`
- `'\t'`
- `' ' ' '`
- `'\t' '\t'`
- `' ' '\t'`
- `'\t' ' '`
- `' ' '\t' ' '`
- `'\t' ' ' '\t'`

And here are some **invalid** examples for spacers:

- ` ` (at least one whitespace or tab is required for a `spacer`)
- `' ' '\t' 'f' ' '` (only whitespaces and tabs are allowed, no other characters)

Before we can dive into instructions, we need to go over two more diagrams that we will within some instructions.


# Numeric value

![](img/railroad-num-value.svg)


# Identifier

![](img/railroad-identifier.svg)


# Instructions

## Comment

![](img/railroad-comment.svg)


## Variable declaration

![](img/railroad-var-declaration.svg)


