ENCODER_ENABLE = yes
MOUSEKEY_ENABLE = yes

# Optical sensor driver for trackball.
POINTING_DEVICE_ENABLE = yes
POINTING_DEVICE_SPLITS += yes


//POINTING_DEVICE_DRIVER = pmw3360
POINTING_DEVICE_DRIVER = custom
# Include common library
SRC += lib_combine/ETE/ETE.c
SRC += drivers/pmw3360/pmw3360.c

QUANTUM_LIB_SRC += spi_master.c # Optical sensor use SPI to communicate