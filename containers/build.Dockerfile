FROM fedora:36

# Install build dependencies
RUN dnf install -y gcc-c++-12.1.1 cmake-3.22.2 boost-devel-1.76.0 gtest-devel-1.11.0 gmock-devel-1.11.0 lcov