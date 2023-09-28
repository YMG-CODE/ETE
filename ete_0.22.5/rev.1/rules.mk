# MCU name
MCU = atmega32u4

# Bootloader selection
#BOOTLOADER = caterina
BOOTLOADER = qmk-dfu



OLED_DRIVER_ENABLE  = no 
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no       # Breathing sleep LED during USB suspend
# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = yes        # Enable keyboard RGB underglow
RGBLIGHT_LIMIT_VAL = 255
AUDIO_ENABLE = no           # Audio output
SPLIT_KEYBOARD = yes

# if firmware size over limit, try this option
LTO_ENABLE = yes

VIA_ENABLE = yes