FROM debian:stable
MAINTAINER prenvois <prenvois@student.42.fr>

### PRE-INSTALL ###
RUN apt-get update

### INSTALL ###
RUN apt-get install -yq openssh-server
RUN mkdir -p /var/run/sshd
RUN useradd -m -s /bin/bash prenvois
RUN mkdir -p /home/prenvois/.ssh
COPY ./authorized_keys /home/prenvois/.ssh/
RUN echo "PORT 42" >> /etc/ssh/sshd_config
RUN /etc/init.d/ssh restart

EXPOSE 42

### POST-INSTALL ###
CMD ["/usr/sbin/sshd", "-D"]
