FROM fedora:45

# Install build dependencies
RUN dnf install -y gcc-c++-16.1.1 cmake-4.3.0 boost-devel-1.90.0 gtest-devel-1.17.0 lcov