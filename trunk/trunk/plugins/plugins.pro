CONFIG += plugin \
debug \
exceptions \
 ordered
QT += sql \
svg \
xml \
network

CONFIG -= release

TEMPLATE = subdirs

DESTDIR = .

SUBDIRS += HiComp

