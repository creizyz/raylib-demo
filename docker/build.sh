#!/bin/bash

set -e # Exit immediately if a command exits with a non-zero status

# Define variables
DOCKER_IMAGE="cxx-raylib-dev"     # The Docker image name
PROJECT_DIR=$(pwd)                # The current directory is assumed to be the project dir
CONTAINER_WORKDIR="/usr/src/app"  # Working directory inside the container
BUILD_PATH="build/docker"         # Name of the build directory

# Ensure all CPUs but one are used for the build
NUM_CPUS=$(($(nproc) - 1))
NUM_CPUS=$(( NUM_CPUS < 1 ? 1 : NUM_CPUS ))

# Step 1: Build the Docker image if it doesn't exist
if ! docker images | grep -q "${DOCKER_IMAGE}"; then
    echo "Docker image '${DOCKER_IMAGE}' not found. Building..."
    docker build -t $DOCKER_IMAGE "${PROJECT_DIR}/docker"
fi

# Step 2: Create the build directory if it doesn't exist
if [ ! -d "${PROJECT_DIR}/${BUILD_PATH}" ]; then
    echo "Creating build directory at: ${PROJECT_DIR}/${BUILD_PATH}"
    mkdir -p "${PROJECT_DIR}/${BUILD_PATH}"
fi

# Step 3: Run the build process in the container
echo "Running cmake and build process inside the Docker container..."

docker run --rm -it \
    -v "${PROJECT_DIR}":${CONTAINER_WORKDIR} \
    ${DOCKER_IMAGE} \
    bash -c "cd ${CONTAINER_WORKDIR}/${BUILD_PATH} && cmake ${CONTAINER_WORKDIR} && make -j ${NUM_CPUS}"

# Step 4: Confirm the build is successful
if [ $? -eq 0 ]; then
    echo "Build completed successfully!"
    echo "Executable can be found in: ${PROJECT_DIR}/${BUILD_PATH}"
else
    echo "Build failed."
    exit 1
fi
