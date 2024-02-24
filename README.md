# Software is NOT finished! Do NOT have any expectations!

## Supported languages:
- [Rust](https://github.com/rust-lang/rust) (rs)
- [C](https://en.wikipedia.org/wiki/C_(programming_language)) (c)
- [C++](https://en.wikipedia.org/wiki/C%2B%2B) (cpp)

### In future i plan to add more and more languages.

# To run: 
```shell
$ git clone --depth 1 https://github.com/rakivo/create
$ cd create
$ gcc -O3 main.c -g -o create
$ ./create test rs .
```
## Usage:
```./create <dir_name> <language> <dir_path>```
for instance: ```create test rs .```

### After this manipulations you'll have a little test.c file in your <dir_name> directory, containing code to print "hello, world" to your shell
#### The goal of this project is to create a lightweight tool for generating projects that is fast and convenient to use, avoiding the slowness found in many modern tools.
