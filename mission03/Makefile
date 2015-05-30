NAME=volume
SSH_PORT=2222

help:
	echo "Options:"
	echo "config		: prepare the docker build"
	echo "build			: build the docker"
	echo "run			: run docker in background"
	echo "connect			: connect via ssh in the docker"
	echo "clean			: clean the current directory"
	echo "help			: display this help"

config:
	mkdir -p src
	cat ~/.ssh/id_rsa.pub >> ./authorized_keys
	VBoxManage sharedfolder remove boot2docker-vm --name Users
	VBoxManage sharedfolder add boot2docker-vm --name Users --hostpath ~/Work/docker/mission03/src/ --automount

build:
	docker build -t ${NAME} .

run:
	docker run -dit -p ${SSH_PORT}:22 -v /Users:/app ${NAME}

connect:
	ssh root@`boot2docker ip` -p ${SSH_PORT}

clean:
	rm -rf ./src
	rm -rf ./authorized_keys

.SILENT:
