include(../../findOpenBabel.pri)

TEMPLATE = lib

HEADERS += \
    atom.h \
    atomnumberitem.h \
    bond.h \
    commands.h \
    electronsystem.h \
    element.h \
    fileio.h \
    graphsymitem.h \
    itemplugin.h \
    math2d.h \
    mechanismarrow.h \
    mechanismarrowdialog.h \
    mimemolecule.h \
    minimise.h \
    molecule.h \
    molinputitem.h \
    mollibitem.h \
    molscene.h \
    molview.h \
    osra.h \
    reactionarrow.h \
    reactionarrowdialog.h \
    residue.h \
    ring.h \
    smilesitem.h \
    stereocenteritem.h \
    TextInputItem.h \
    tool.h \
    toolgroup.h \
    tools/chargetool.h \
    tools/connecttool.h \
    tools/drawtool.h \
    tools/electrontool.h \
    tools/hydrogentool.h \
    tools/lassotool.h \
    tools/mechanismarrowtool.h \
    tools/minimizetool.h \
    tools/movetool.h \
    tools/reactionarrowtool.h \
    tools/rotatetool.h \
    coloraction.h \
    graphicsitem.h \
    linewidthaction.h \
    abstractitemaction.h \
    abstractxmlobject.h

SOURCES += \
    atom.cpp \
    atomnumberitem.cpp \
    bond.cpp \
    commands.cpp \
    electronsystem.cpp \
    element.cpp \
    fileio.cpp \
    graphsymitem.cpp \
    itemplugin.cpp \
    mechanismarrow.cpp \
    mechanismarrowdialog.cpp \
    mimemolecule.cpp \
    minimise.cpp \
    molecule.cpp \
    molinputitem.cpp \
    mollibitem.cpp \
    molscene.cpp \
    molview.cpp \
    osra.cpp \
    reactionarrow.cpp \
    reactionarrowdialog.cpp \
    residue.cpp \
    smilesitem.cpp \
    stereocenteritem.cpp \
    TextInputItem.cpp \
    tool.cpp \
    toolgroup.cpp \
    tools/chargetool.cpp \
    tools/connecttool.cpp \
    tools/drawtool.cpp \
    tools/electrontool.cpp \
    tools/hydrogentool.cpp \
    tools/lassotool.cpp \
    tools/mechanismarrowtool.cpp \
    tools/minimizetool.cpp \
    tools/movetool.cpp \
    tools/reactionarrowtool.cpp \
    tools/rotatetool.cpp \
    coloraction.cpp \
    graphicsitem.cpp \
    linewidthaction.cpp \
    abstractitemaction.cpp \
    abstractxmlobject.cpp

FORMS += \
    mechanismarrowdialog.ui \
    reactionarrowdialog.ui

RESOURCES += \
    tools/toolicons.qrc

QT += svg

TARGET = ../../lib/molsketch
equals(QT_MAJOR_VERSION, 5) : TARGET = ../../lib/molsketch-qt5
