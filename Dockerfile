FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive

# Install necessary packages
RUN apt-get update && \
        apt-get clean && \ 
        apt-get install -y \
        gcc-arm-none-eabi \
        cmake \
        git \
        ninja-build \
        libncurses-dev \
        && rm -rf /var/lib/apt/lists/*

# install STM32 ARM Package
# tar xjf gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2 -C /usr/share/

# Create links so that binaries are accesible system wide
#RUN sudo ln -s /usr/share/gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar/bin/arm-none-eabi-gcc /usr/bin/arm-none-eabi-gcc \ 
#        sudo ln -s /usr/share/gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar/bin/arm-none-eabi-g++ /usr/bin/arm-none-eabi-g++ \
#        sudo ln -s /usr/share/gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar/bin/arm-none-eabi-gdb /usr/bin/arm-none-eabi-gdb \
#        sudo ln -s /usr/share/gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar/bin/arm-none-eabi-size /usr/bin/arm-none-eabi-size \ 
#        sudo ln -s /usr/share/gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar/bin/arm-none-eabi-objcopy /usr/bin/arm-none-eabi-objcopy

# Install dependencies
#RUN sudo apt install libncurses-dev \
#        sudo ln -s /usr/lib/x86_64-linux-gnu/libncurses.so.6 /usr/lib/x86_64-linux-gnu/libncurses.so.5 \
#        sudo ln -s /usr/lib/x86_64-linux-gnu/libtinfo.so.6 /usr/lib/x86_64-linux-gnu/libtinfo.so.5

# Check Versions of arm-none-eabi
RUN arm-none-eabi-gcc --version \
        arm-none-eabi-g++ --version \
        arm-none-eabi-gdb --version \
        arm-none-eabi-size --version

# Check Cmake and Ninja Versions
RUN cmake --version \
        ninja --version

# Install Other libraries (if Needed)


# Create a directory for your workspace
WORKDIR /workspace

# Copy your C++ application source code and CMakeLists.txt
# into the container (adjust the paths accordingly)
COPY . /workspace

# Set the entry point to run your application (adjust as needed)
CMD ["/workspace/build"]

# Bulding Image: docker build -t stm32-dev-environment .
# Run Container: docker run -it --privileged --rm stm32-dev-environment

# Run Code inside Container: cd /workspace
# mkdir build
# cd build
# cmake .. -DCMAKE_TOOLCHAIN_FILE=/path/to/stm32_toolchain.cmake
# make

# RUN FOR VSCODE Extensions:
# code --install-extension ms-vscode.cpptools
# code --install-extension ms-vscode.cmake-tools
# code --install-extension twxs.cmake
# code --install-extension marus25.cortex-debug
# code --install-extension dan-c-underwood.arm
# code --install-extension zixuanwang.linkerscript