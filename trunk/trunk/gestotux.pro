SUBDIRS += src \
 plugins \
 utiles
TEMPLATE = subdirs 
CONFIG += warn_on \
          qt \
          thread  \
 ordered
DESTDIR = .

