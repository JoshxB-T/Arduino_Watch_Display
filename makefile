FILE=.

make: compile upload

compile:
	arduino-cli compile --fqbn arduino:renesas_uno:unor4wifi $(FILE)

upload:
	arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:renesas_uno:unor4wifi $(FILE)
