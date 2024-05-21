# Docker file for the backend
FROM ubuntu:22.04

# Install the necessary dependencies
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y \
    gcc \
    g++ \
    cmake \
    curl \
    git \
    sqlite3 \
    libsqlite3-dev \
    libssl-dev \
    libboost-all-dev

# Install jsoncpp
RUN git clone https://github.com/open-source-parsers/jsoncpp.git /tmp/jsoncpp && \
    cd /tmp/jsoncpp && \
    mkdir -p build/release && \
    cd build/release && \
    cmake -DCMAKE_BUILD_TYPE=release -DBUILD_SHARED_LIBS=ON -DARCHIVE_INSTALL_DIR=. -G "Unix Makefiles" ../.. && \
    make && \
    make install && \
    rm -rf /tmp/jsoncpp

# Install jsoncons
RUN git clone https://github.com/danielaparker/jsoncons.git /tmp/jsoncons && \
    cd /tmp/jsoncons && \
    mkdir build && \
    cd build && \
    cmake .. && \
    make install && \
    rm -rf /tmp/jsoncons

# Install jwt-cpp
RUN git clone https://github.com/Thalhammer/jwt-cpp.git /tmp/jwt-cpp && \
    cd /tmp/jwt-cpp && \
    mkdir build && \
    cd build && \
    cmake -DJWT_BUILD_EXAMPLES=OFF .. && \
    make install && \
    rm -rf /tmp/jwt-cpp

# Install cpp-httplib
RUN git clone --depth=1 https://github.com/yhirose/cpp-httplib.git /tmp/cpp-httplib && \
    cd /tmp/cpp-httplib && cmake . && make install && \
    rm -rf /tmp/cpp-httplib


# Set the working directory
WORKDIR /app

# Copy the current directory contents into the container at /app
COPY . /app

# Compile the backend
RUN mkdir build && cd build && cmake .. && make

# Initialize the database
RUN ./build/Initialize_Database

# Expose the port
EXPOSE 4000

# Expose the port
EXPOSE 8080

# Run the backend
CMD ["./build/Backend"]