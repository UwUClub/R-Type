# R-Type



## Contents

- [Requirements](#requirements)
- [Communication](#communication)
- [Installation](#installation)
- [Installation from source](#installation-from-source)
- [Compilation](#compilation)
- [More Details](#more-details)
- [Testing](#testing)
- [Credits](#credits)
- [License](#license)

## Requirements

- C++ 20+ is required

## Communication

- If you have a bug or an issue, please contact us.

## Installation
- Head to the [releases page](github.com/UwUClub/R-Type/releases) and download the latest release for your platform.

## Installation from source

### SSH

```bash
git clone git@github.com:UwUClub/R-Type.git
```

## Compilation

### Using CMake

```bash
cmake -S . -B build && cmake --build build
```

## Binaries
### Server
First start the server
```bash
./server <ip> <port>
```
### Client
Then start the client
```bash
./client <ip of server> <port of server>
```

### Flappybird
Standalone flappybird game to demonstrate ECS.
```bash
./flappybird
```


## More Details

 * [Dependency Setup](README_dependencies.md)
 * [Building Details](README_building.md)
 * [![ci](https://github.com/UwUClub/Zappy/actions/workflows/Testing.yml/badge.svg)](https://github.com/cpp-best-practices/cmake_template/actions/workflows/ci.yml)
 ``` txt
    can add that to see coverage % in github
    * [![codecov](https://codecov.io/gh/UwUClub/R-Type/branch/main/graph/badge.svg)](https://codecov.io/gh/cpp-best-practices/cmake_template)
 ```
## Testing

See [Catch2 tutorial](https://github.com/catchorg/Catch2/blob/master/docs/tutorial.md)

## Credits

- Valentin Gegoux
- Baptiste Laran
- Mathéo Martin
- Maxence Labourel

## License

R-Type is developped by the UwUClub for Epitech.
