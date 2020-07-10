# What is the idea behind *fox*?

*fox* is a very thin coat over assembly. In other words: Programming in *fox* feels like writing assembly, but with added convenience features. This is what's planned:

* [ ] Variables with identifiers
* [ ] Human-readable loops
* [ ] Easy function calling with arguments

# What should I use *fox* for?

Nothing serious, unless you are very brave and/or reckless. Use *fox* to learn about programming languages and syntax, compilers and assembly with me - or look at it as a template to base your own ideas off of.


# What does *fox* code look like?

```
# this is a comment
var x    # define variable
x 7      # assign value 7
return x # return variable
```


# How do I get started with *fox*?

### Linux

1. Verify that you have `gcc` installed. `gcc` is both needed to build the *fox* compiler `foxy` and to assemble and link *fox* programs. I use `gcc 7.5` but other versions may also work just fine.
```
$ gcc --version
gcc (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0
Copyright (C) 2017 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```

2. Verify that you have `make` installed. Almost any version will do, it does not have to be specifically `make 4.1`.
```
$ make --version
GNU Make 4.1
Built for x86_64-pc-linux-gnu
Copyright (C) 1988-2014 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
```

3. Alright, let's roll! Clone this repository and build the `foxy` compiler.
```
$ git clone https://github.com/janhsimon/fox
Cloning into 'fox'...
remote: Enumerating objects: 3, done.
remote: Counting objects: 100% (3/3), done.
remote: Total 3 (delta 0), reused 3 (delta 0), pack-reused 0
Unpacking objects: 100% (3/3), done.
$ cd foxy
$ make
```

4. Write and compile a minimal *fox* program called `life`. As the name implies, it's very powerful and returns the number `42`. We supply the name of our source file `life.fox` and our platform with `-platform linux-gcc`. The latter is important for the next step.
```
$ echo "# hello fox" > life.fox
$ echo "var x" >> life.fox
$ echo "x 42" >> life.fox
$ echo "return x" >> life.fox
$ ./foxy life.fox -platform linux-gcc
life.fox
life.fox -> life.s
```

5. Assemble and link the *fox* program. We simply re-use `gcc` for this.
```
$ gcc life.s -o life
```

6. Run `life` and print the previous program's return code with `$?`. Verify that the answer to the ultimate question of life, the universe, and everything, is indeed `42`.
```
$ ./life
$ echo $?
42
```
