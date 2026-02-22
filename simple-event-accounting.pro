TEMPLATE = subdirs

SUBDIRS += \
    Application \
    Domain \
    Infrastructure \
    Presentation

Domain.subdir = src/Domain
Application.subdir = src/Application
Infrastructure.subdir = src/Infrastructure
Presentation.subdir = src/Presentation

Application.depends = Domain
Infrastructure.depends = Domain Application
Presentation.depends = Domain Application Infrastructure
