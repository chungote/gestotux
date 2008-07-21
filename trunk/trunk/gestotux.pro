SUBDIRS += utiles \
 src \
 plugins
TEMPLATE = subdirs
CONFIG += warn_on \
          qt \
          thread  \
 ordered
DESTDIR = .

