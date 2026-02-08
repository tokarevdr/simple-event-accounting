TEMPLATE = subdirs

SUBDIRS += \
    src/Application \
    src/Domain \
    src/Infrastructure \
    src/Presentation

Application.depends = src/Domain
Infrastructure.depends = src/Application src/Domain
Presentation.depends = src/Application src/Infrastructure src/Domain
