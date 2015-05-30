NAME=hello/world:v42
HTTP_PORT=80

help:
	echo "Options:"
	echo "build			: build the docker"
	echo "run			: run docker in foreground"
	echo "help			: display this help"

build:
	docker build -t ${NAME} .

run:
	docker run -p ${HTTP_PORT}:80 -it ${NAME} /bin/zsh

.SILENT:
