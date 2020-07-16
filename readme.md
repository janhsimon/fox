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

## Linux

1. Verify that you have `gcc` installed. We need `gcc` for its assembler and linker. I use `gcc 7.5` but other versions may also work just fine. No guarantees though.
```
$ gcc --version
gcc (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0
Copyright (C) 2017 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```

2. Download the latest Linux release of the *fox* compiler `foxy` from the [releases page](https://github.com/janhsimon/fox/releases) and place it in a folder of your choice. Let's say you picked `~/fox-dev` for example. You can also choose to just build `foxy` yourself by cloning this repository and running `make` in the `/foxy` subdirectory.

3. Now we are ready to create the minimal *fox* program `life`. As the name implies, it's very powerful and returns the number `42`. And it does all that in just one single source file called `life.fox`. Fist we navigate to `~/fox-dev` and then we write the source file.
```
$ cd ~/fox-dev
$ echo "# hello fox" > life.fox
$ echo "var x" >> life.fox
$ echo "x 42" >> life.fox
$ echo "return x" >> life.fox
```

4. Let's compile `life`. We simply supply our platform with `-platform linux-gcc` and a list of source files to the compiler.
```
$ ./foxy -platform linux-gcc life.fox
life.fox
life.fox -> life.s
```

5. Now assemble and link the *fox* program with a little help from our friend `gcc`.
```
$ gcc life.s -o life
```

6. Run `life` and print the previous program's return code with `echo $?`. Verify that the answer to the ultimate question of life, the universe, and everything, is indeed `42`.
```
$ ./life
$ echo $?
42
```


## Windows

1. Install `Visual Studio` if you don't have it yet. We need it for its assembler and linker. I use `Visual Studio Community 2019` but 2017 should be compatible as well.

2. Grab the latest Windows release of the *fox* compiler `foxy` from the [releases page](https://github.com/janhsimon/fox/releases) and extract it to a folder of your choice. Let's use the folder `C:\fox-dev` for example.

3. Time to create our first *fox* program. It will be called `life` and consists of just a single source file: `life.fox`. It's very complex and returns the number `42`. First, you need to open the `x64 Native Tools Command Prompt for Visual Studio 2019`. It's easy to find if you open your start menu and begin typing in the first letters. Then enter the following commands in the prompt that pops up to navigate to our folder `C:\fox-dev` and write the source file `life.fox`:
```
> cd c:\fox-dev
> echo # hello fox > life.fox
> echo var x >> life.fox
> echo x 42 >> life.fox
> echo return x >> life.fox
```

4. Now it's to to compile `life`. We simply supply our platform with `-platform win-vs` and a list of source files to `foxy`:
```
> foxy -platform win-vs life.fox
life.fox
life.fox -> life.s
```

5. Next we need to assemble and link the *fox* program. We will use the `Microsoft Macro Assembler`  and `Microsoft Incremental Linker` tools that come with `Visual Studio` for this.
```
> ml64 life.s /link /ENTRY:main
```

6. Let's run `life` and then check that it returned `42` by printing `%errorlevel%`. Make sure that our program did indeed return the answer to the ultimate question of life, the universe, and everything.
```
> life
> echo %errorlevel%
42
```

