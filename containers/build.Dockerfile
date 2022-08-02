FROM fedora:35
RUN dnf install -y gcc-c++-11.2.1 gdb-12.1 cmake-3.22.2 boost-devel-1.76.0 gtest-devel-1.10.0 gmock-devel-1.10.0 git findutils lcov