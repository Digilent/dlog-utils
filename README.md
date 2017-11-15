# DLOG Utilities

Utilities for dlog files

## Getting Started

These instructions will get you a copy of the project up and running on your local machine.

### Prerequisites

1. Doxygen
2. g++
3. make
4. ar

### Subdirectories
* **build**
  * Contains the built files.
* **docs**
  * Contains built documentation from source.
* **examples**
  * Contains simple examples demonstrating how to use dlog-utils.
* **test**
  * Contains test files.
* **src**
  * Contains the source files.

### Installing

Clone this repository

```
git clone https://git.digilentinc.com/dsukumar/dlog-utils.git
```

Move to project directory

```
cd dlog-utils
```

Setup Environment

```
make setupEnv
```

Build Project

```
make all
```

Run an example

* **Windows**

  ```
  ./examples/build/main.exe log.dlog log
  ```
* **Linux/Mac**

  ```
  ./examples/build/main.out log.dlog log
  ```

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details