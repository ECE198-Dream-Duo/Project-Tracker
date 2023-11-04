# Use a base image that includes the arm-none-eabi-gcc toolchain and CMake
FROM debian:buster-slim

# Install build essentials and other dependencies
RUN apt-get update && apt-get install -y && apt-get clean \
    build-essential \
    cmake \
    make \
    gcc-arm-none-eabi \
    git \
    && rm -rf /var/lib/apt/lists/*

# Install Other Libraries
RUN apt-get update && apt-get install -y ccache && rm -rf /var/lib/apt/lists/*

# Create a non-root user (optional but recommended)
RUN useradd -ms /bin/bash developer
USER developer
WORKDIR /home/developer

# Copy your project files into the Docker image
COPY --chown=developer:developer . /home/developer/LineTrackingRobot

# Create and move to the build directory
WORKDIR /home/developer/LineTrackingRobot/build

# Run CMake to configure the project. Adjust the command if you have a custom toolchain file.
RUN chmod +x build.sh

# The default command could be to run the tests or simply output the build files
CMD ["ls", "/home/developer/LineTrackingRobot/build"]

# To Build:
# cmake -G "MinGW Makefiles" -DCMAKE_TOOLCHAIN_FILE=../arm-none-eabi-gcc.cmake -DCMAKE_BUILD_TYPE=Debug ..
# cmake -G "MinGW Makefiles" -DCMAKE_TOOLCHAIN_FILE=../arm-none-eabi-gcc.cmake -DCMAKE_BUILD_TYPE=Release ..
# cmake --build . -- -j 4

# To Clean:
# cmake --build . --target clean
