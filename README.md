# Brainfuck Interpreter
## About
`bf` is a simple command-line interpreter for the Brainfuck esoteric
language.

## Dependencies
* A suitable C compiler supporting at least C99
* `make`

## Build
```
make
```


## Usage
Read from a file:
```
bf <path/to/file>
```

Also supports reading in from `stdin`
```
echo "+++++++++++++++++++++++++++++++++++++++." | bf
```
