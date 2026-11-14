# Mini IoT

A small IoT simulation project written in C++17.

## Features

- Sensor simulation (temperature and humidity).
- Measurement validation.
- Logging measurements to a file.
- UDP client-server communication.
- JSON serialization and parsing.
- Server acknowledgment (ACK).
- Socket error handling and timeouts.
- Basic multithreading.

## Technologies

- C++17
- CMake
- Linux UDP Sockets
- nlohmann/json
- GoogleTest

## Build and Run

```bash
mkdir build
cd build
cmake ..
make
./sensor
```

## Project Status

Basic sensor simulation and UDP communication are implemented. Further improvements are planned.
