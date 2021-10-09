FROM fedora:latest

# Define user build arguments
ARG UNAME=user

# Add user
RUN useradd -m -s /bin/bash ${UNAME}

RUN dnf install -y g++ gdb cmake boost-devel gtest-devel git passwd findutils
