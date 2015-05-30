FROM debian:stable
MAINTAINER prenvois <prenvois@student.42.fr>

### PRE-INSTALL ##
ENV APACHE_RUN_USER="www-data"
ENV APACHE_RUN_GROUP="www-data"
ENV APACHE_LOG_DIR="/var/log/apache2/"

RUN apt-get update

### INSTALL ####
RUN apt-get install -yq zsh nginx
RUN echo "daemon off;" >> /etc/nginx/nginx.conf
RUN rm /usr/share/nginx/www/index.html && echo "Hello World" >> /usr/share/nginx/www/index.html
EXPOSE 80
RUN echo "PS1='prenvois@42born2code:/# '" >> ~/.zshrc
