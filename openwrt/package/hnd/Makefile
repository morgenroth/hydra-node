#
# Copyright (C) 2006 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=hnd
PKG_VERSION_MAJOR:=0
PKG_VERSION_MINOR:=2
PKG_VERSION_MICRO:=0

#PKG_VERSION:=$(PKG_VERSION_MAJOR).$(PKG_VERSION_MINOR).$(PKG_VERSION_MICRO)
PKG_VERSION:=$(PKG_VERSION_MAJOR).$(PKG_VERSION_MINOR)
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=http://www.ibr.cs.tu-bs.de/projects/ibr-dtn/releases

PKG_INSTALL:=1
PKG_BUILD_DEPENDS:=ibrcommon

include $(INCLUDE_DIR)/package.mk

define Package/hnd
  SECTION:=net
  CATEGORY:=Network
  DEPENDS:=ibrcommon
  TITLE:=Hydra Node Daemon
endef

define Package/hnd/description
 This daemon is necessary to get control over a hydra node.
endef

define Package/hnd/install
	$(INSTALL_DIR) $(1)/usr/bin/
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/hnd $(1)/usr/bin/hnd
endef

$(eval $(call BuildPackage,hnd))
