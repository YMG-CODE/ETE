# MCU name
MCU = atmega32u4

# Bootloader selection
#BOOTLOADER = caterina
BOOTLOADER = qmk-dfu


BOOTMAGIC_ENABLE = lite     # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
OLED_DRIVER_ENABLE  = no 
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no       # Breathing sleep LED during USB suspend
# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE = yes           # USB Nkey Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = yes        # Enable keyboard RGB underglow
RGBLIGHT_LIMIT_VAL = 255
AUDIO_ENABLE = no           # Audio output
SPLIT_KEYBOARD = yes

# if firmware size over limit, try this option
LTO_ENABLE = yes

JOYSTICK_ENABLE = yes
POINTING_DEVICE_ENABLE = yes
SRC += analog.c

ENCODER_ENABLE = yes