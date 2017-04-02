default: src/test1.ino
	rm -f photon_*
	particle compile photon .
	particle flash --usb photon_*
	sleep 1
	particle serial monitor
