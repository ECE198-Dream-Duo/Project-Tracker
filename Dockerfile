FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive

# Install necessary packages
RUN apt-get update && \
         apt-get clean && \ 
         apt-get install -y \
          gcc-arm-none-eabi \
          libcurl4-openssl-dev \ 
          cmake \
          make \
          git \
          && rm -rf /var/lib/apt/lists/*

# Create a directory for your workspace
WORKDIR /workspace

# Download the STM32 toolchain file and copy it to the /workspace directory
RUN wget -O stm32_toolchain.cmake https://example.com/path/to/stm32_toolchain.cmake

# Install Other libraries (if Needed)


# Copy your C++ application source code and CMakeLists.txt
# into the container (adjust the paths accordingly)
COPY CMakeLists.txt .
COPY src/ /workspace/src/
COPY include/ /workspace/include/

# Build your C++ application using CMake and the cross-compiler
RUN mkdir build && cd build && \
    cmake .. -DCMAKE_TOOLCHAIN_FILE=/workspace/stm32_toolchain.cmake && \
    make

# Set the entry point to run your application (adjust as needed)
CMD ["/workspace/build/LineTrackingRobot"]

# Bulding Image: docker build -t stm32-dev-environment .
# Run Container: docker run -it --privileged --rm stm32-dev-environment

# Run Code inside Container: cd /workspace
# mkdir build
# cd build
# cmake .. -DCMAKE_TOOLCHAIN_FILE=/path/to/stm32_toolchain.cmake
# make