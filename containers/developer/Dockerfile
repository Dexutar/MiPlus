FROM fedora:latest

# Define user build arguments
ARG UNAME=user

# Add user
RUN useradd -m -s /bin/bash ${UNAME}

# Install Docker CE CLI
RUN dnf install -y dnf-plugins-core && \
  dnf config-manager --add-repo https://download.docker.com/linux/fedora/docker-ce.repo && \
  dnf install -y docker-ce-cli

RUN echo -e "#!/bin/sh\n\
    sudoIf() { if [ \"\$(id -u)\" -ne 0 ]; then sudo \"\$@\"; else \"\$@\"; fi }\n\
    SOCKET_GID=\$(stat -c '%g' /var/run/docker.sock) \n\
    if [ \"${SOCKET_GID}\" != '0' ]; then\n\
        if [ \"\$(cat /etc/group | grep :\${SOCKET_GID}:)\" = '' ]; then sudoIf groupadd --gid \${SOCKET_GID} docker-host; fi \n\
        if [ \"\$(id ${UNAME} | grep -E \"groups=.*(=|,)\${SOCKET_GID}\(\")\" = '' ]; then sudoIf usermod -aG \${SOCKET_GID} ${UNAME}; fi\n\
    fi\n\
    exec \"\$@\"" > /usr/local/share/docker-init.sh \
    && chmod +x /usr/local/share/docker-init.sh

ENTRYPOINT [ "/usr/local/share/docker-init.sh" ]
CMD [ "sleep", "infinity" ]

RUN dnf install -y g++ gdb cmake boost-devel gtest-devel git passwd findutils
