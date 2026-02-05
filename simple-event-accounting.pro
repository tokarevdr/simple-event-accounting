TEMPLATE = subdirs

SUBDIRS += \
    src/Application \
    src/Domain \
    src/Infrastructure \
    src/Presentation

Application.depends = src/Domain
Infrastructure.depends = src/Application
