TEMPLATE = subdirs

SUBDIRS += \
    Application \
    Domain \
    Infrastructure \
    Presentation \
    Utils

Domain.subdir = src/Domain
Application.subdir = src/Application
Infrastructure.subdir = src/Infrastructure
Presentation.subdir = src/Presentation
Utils.subdir = src/Utils

Application.depends = Domain
Infrastructure.depends = Domain Application
Presentation.depends = Utils Domain Application Infrastructure
