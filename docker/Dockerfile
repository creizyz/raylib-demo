FROM debian:bookworm-slim

ENV ARCH=amd64
ENV RAYLIB_VERSION=5.5
ENV RAYLIB_URL="https://github.com/raysan5/raylib/releases/download/${RAYLIB_VERSION}/raylib-${RAYLIB_VERSION}_linux_${ARCH}.tar.gz"

# Install dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    build-essential \
    cmake \
    meson \
    gdb \
    wget \
    tar \
    libx11-dev \
    libxrandr-dev \
    libxinerama-dev \
    libxcursor-dev \
    libxi-dev \
    libgl1-mesa-dev \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

# Download and extract raylib
RUN wget -O raylib.tar.gz "${RAYLIB_URL}" && \
    tar -xvzf raylib.tar.gz && \
    cp -r raylib-${RAYLIB_VERSION}_linux_${ARCH}/lib/* /usr/local/lib/ && \
    cp -r raylib-${RAYLIB_VERSION}_linux_${ARCH}/include/ /usr/local/include/raylib && \
    rm -rf raylib.tar.gz raylib-${RAYLIB_VERSION}_linux_${ARCH}

# Set library path
ENV LD_LIBRARY_PATH="/usr/local/lib:${LD_LIBRARY_PATH}"

# Default working directory
WORKDIR /usr/src/app

# Command for debugging (optional)
CMD ["bash"]
