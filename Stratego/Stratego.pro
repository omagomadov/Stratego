TEMPLATE = subdirs

SUBDIRS += \
    gui \
    model \
    tests \
    tui

OTHER_FILES += config.pri \
               setup-board/default.txt
