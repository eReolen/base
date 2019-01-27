PROJECT := ereolen
DNS := ereolen.docker.localhost

up:
	docker-compose -p ${PROJECT} up -d

stop:
	docker-compose -p ${PROJECT} stop

ps:
	docker-compose -p ${PROJECT} ps

clean:
	docker-compose -p ${PROJECT} rm

mysql:
	docker-compose -p ${PROJECT} port mariadb 3306 | cut -d: -f2

open:
	open http://${DNS}:$(shell docker-compose -p ${PROJECT} port reverse-proxy 80 | cut -d: -f2)
