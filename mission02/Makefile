NAME=ssh
SSH_PORT=2222

help:
	echo "Options:"
	echo "build			: build the docker"
	echo "run			: run docker in background"
	echo "connect			: connect via ssh in the docker"
	echo "clean			: clean the current directory"
	echo "help			: display this help"

build:
	cat ~/.ssh/id_rsa.pub >> ./authorized_keys
	docker build -t ${NAME} .

run:
	docker run -dit -p ${SSH_PORT}:42 ${NAME}

connect:
	ssh prenvois@`boot2docker ip` -p ${SSH_PORT}

clean:
	rm -rf authorized_keys

.SILENT:
