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

But what exactly is a `spacer`? And what's an `instruction`? Let's define these elements with, you guessed it, more railroad diagrams!


# Spacer

![](img/railroad-spacer.svg)

A `spacer` is just a sequence of whitespaces or tabs. So far, they have just been used to optionally separate the different instructions that make up a *fox* program. This is just so that programmers are free to format *fox* code the way they like, with any amount of extra whitespaces or tabs.

But it's important to note that a 'spacer' as seen in the diagram above does require at least one whitespace or tab. This is because they are also used within some instructions, to seperate a keyword from an identifier for example. Note that the source file diagram has an extra path circumventing the 'spacer' specifically to allow not using any seperation between instructions.

Let's look at some 'spacer' examples:

- `' '`
- `'\t'`
- `' ' ' '`
- `'\t' '\t'`
- `' ' '\t'`
- `'\t' ' '`
- `' ' '\t' ' '`
- `'\t' ' ' '\t'`

Next we will look at the different *fox* instructions.


# Instructions

## Comment

![](img/railroad-comment.svg)

## Variable declaration

![](img/railroad-var-declaration.svg)

