FROM ubuntu:22.04

LABEL description="Basic ubuntu container for algoritmosavancados"

RUN echo 'Build starts...'

RUN DEBIAN_FRONTEND=noninteractive \
    apt-get update \
    && UCF_FORCE_CONFFOLD=1 apt-get install  -y openssh-server git cmake gdb build-essential \
    ninja-build 

RUN echo 'PermitRootLogin yes' >> /etc/ssh/sshd_config && \
    echo 'PermitEmptyPasswords yes' >> /etc/ssh/sshd_config && \
    echo 'PasswordAuthentication yes' >> /etc/ssh/sshd_config && \
    ssh-keygen -A

EXPOSE 45

RUN mkdir /run/sshd

CMD ["/usr/sbin/sshd", "-D"]

RUN echo 'Build complete.'