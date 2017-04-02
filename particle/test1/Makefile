default: src/test1.ino
	rm -f photon_*
	particle compile photon .
	particle flash --usb photon_*
	particl serial monitor
