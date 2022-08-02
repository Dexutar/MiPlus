FROM dexutar/miplus-build:latest

# Define user build arguments
ARG UNAME=user

RUN dnf install -y passwd

# Add user
RUN useradd -G wheel -m -s /bin/bash ${UNAME} && passwd -d ${UNAME}

# Install Docker CE CLI
RUN dnf install -y dnf-plugins-core && \
  dnf config-manager --add-repo https://download.docker.com/linux/fedora/docker-ce.repo && \
  dnf install -y docker-ce-cli

# Default to root only access to the Docker socket, set up non-root init script
RUN touch /var/run/docker-host.sock \
  && ln -s /var/run/docker-host.sock /var/run/docker.sock \
  && dnf install -y socat

# Create docker-init.sh to spin up socat
RUN echo -e "#!/bin/sh\n\
  sudoIf() { if [ \"\$(id -u)\" -ne 0 ]; then sudo \"\$@\"; else \"\$@\"; fi }\n\
  sudoIf rm -rf /var/run/docker.sock\n\
  ((sudoIf socat UNIX-LISTEN:/var/run/docker.sock,fork,mode=660,user=${UNAME} UNIX-CONNECT:/var/run/docker-host.sock) 2>&1 >> /tmp/vscr-docker-from-docker.log) & > /dev/null\n\
  \"\$@\"" >> /usr/local/share/docker-init.sh \
  && chmod +x /usr/local/share/docker-init.sh

ENTRYPOINT [ "/usr/local/share/docker-init.sh" ]
CMD [ "sleep", "infinity" ]
