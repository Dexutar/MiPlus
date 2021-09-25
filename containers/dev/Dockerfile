FROM fedora:latest
RUN dnf install -y g++ gdb cmake boost-devel gtest-devel git passwd
RUN useradd -m vscode && passwd -f -u vscode
