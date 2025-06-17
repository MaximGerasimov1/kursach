QT += core gui widgets
CONFIG += c++17

SOURCES += \
    main.cpp \
    supplier_management_system.cpp \
    about_program_dialog.cpp \
    supplier_registry.cpp \
    supplier_manager.cpp

HEADERS += \
    supplier_management_system.h \
    about_program_dialog.h \
    supplier_registry.h \
    supplier_manager.h

FORMS += \
    supplier_management_system.ui \
    about_program_dialog.ui

TRANSLATIONS += \
    translations/ru.ts \
    translations/en.ts \
    translations/ro.ts

RESOURCES += \
    assets.qrc

# Для корректной работы QSettings
DEFINES += QT_NO_CAST_FROM_ASCII 