## Supported languages:
- [Rust](https://github.com/rust-lang/rust)
- [C](https://en.wikipedia.org/wiki/C_(programming_language))
- [C++](https://en.wikipedia.org/wiki/C%2B%2B)
- [JS](https://en.wikipedia.org/wiki/JavaScript)
- [Go](https://en.wikipedia.org/wiki/Go_(programming_language))
- [Php](https://en.wikipedia.org/wiki/PHP)
- [Pascal](https://en.wikipedia.org/wiki/Pascal_(programming_language))
- [Kotlin](https://en.wikipedia.org/wiki/Kotlin_(programming_language))
- [Python](https://en.wikipedia.org/wiki/Python_(programming_language))
- [Lua](https://en.wikipedia.org/wiki/Lua_(programming_language))

### In future i plan to add more and more languages.

![PREVIEW](PREVIEW.gif)

# To run:
```shell
$ git clone --depth 1 https://github.com/rakivo/create && cd create
$ make
$ ./create hello rs test .
```

## To add the binary to your PATH variables:
```shell
$ ./addtopath.sh
```

## Usage:
```./create create <name> <language> <dir_name> <dir_path>```
for instance: ```./create hello rs test .```

### After that you can test that:
```shell
$ cd test
$ cargo run
```

#### The goal of this project is to create a lightweight tool for generating projects that is fast and convenient to use, avoiding the slowness found in many modern tools.
