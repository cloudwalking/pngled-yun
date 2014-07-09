INSTALL_DIR=/usr/bin/rgam
SCP_TARGET=root@arduino.local:$(INSTALL_DIR)

up:
	scp pngled-server.py $(SCP_TARGET)
	scp data.png $(SCP_TARGET)