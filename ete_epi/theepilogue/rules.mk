VIA_ENABLE = yes
LTO_ENABLE = yes
RGBLIGHT_ENABLE = yes        # Enable keyboard RGB underglow
RGBLIGHT_LIMIT_VAL = 255
EXTRAKEY_ENABLE = yes

CUSTOM_MATRIX = lite
SRC += matrix.c
SPLIT_KEYBOARD = yes
SPLIT_KEYBOARD_ENABLE = yes

ENCODER_ENABLE = yes

# Build Options

# Disable other features to squeeze firmware size
SPACE_CADET_ENABLE = no
MAGIC_ENABLE = no
CONSOLE_ENABLE = no
COMMAND_ENABLE = no
MUSIC_ENABLE = no
SPACE_CADET_ENABLE = no
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
AUDIO_ENABLE = no           # Audio output
GRAVE_ESC_ENABLE = no
