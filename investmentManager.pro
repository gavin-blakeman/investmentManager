TEMPLATE = subdirs

CONFIG += ordered
SUBDIRS += "ACL"
SUBDIRS += "GCL"
SUBDIRS += "MCL"
#SUBDIRS += "WtExtensions"
SUBDIRS += "QCL"
SUBDIRS += "SCL"
SUBDIRS += "investmentManager"

DEFINES += QWT_STATIC
