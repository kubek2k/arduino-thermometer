SKTECH = Thermometer.ino
UPLOAD_PORT = /dev/tty.wchusbserial1410
BOARD = d1_mini

ESPROOT= ../esp8266
ifeq ($(CONFIG_FILE),)
  $(error CONFIG_FILE is not set)
endif
BUILD_EXTRA_FLAGS = -include $(CONFIG_FILE)

include ../makeEspArduino/makeEspArduino.mk

