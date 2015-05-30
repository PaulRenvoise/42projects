FROM debian:stable
MAINTAINER prenvois <prenvois@student.42.fr>

### PRE-INSTALL ###
RUN apt-get update

### INSTALL ###
RUN mkdir /app
RUN apt-get install -yq openssh-server
RUN mkdir -p /var/run/sshd
RUN mkdir -p /root/.ssh
COPY ./authorized_keys /root/.ssh/

VOLUME "/app"

EXPOSE 22

### POST-INSTALL ###
CMD ["/usr/sbin/sshd", "-D"]
