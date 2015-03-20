include $(TOPDIR)/rules.mk

PKG_NAME:=liblpty
PKG_VERSION:=0.1
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://github.com/ntavish/liblpty.git
PKG_SOURCE_VERSION:=2b4b2aefd2f60ee0f5a2ba16de11dde2326e21be
PKG_SOURCE_PROTO:=git
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)
PKG_BUILD_DEPENDS := +lualpty +liblua

include $(INCLUDE_DIR)/package.mk

define Package/liblpty
	CATEGORY:=Libraries
	DEFAULT:=n
	TITLE:=Routiy
	URL:=http://www.tset.de/lpty/
	DEPENDS:= +liblua +libc +lualpty
endef

define Package/liblpty/description
C bindings for lpty library
endef

TARGET_CFLAGS += $(FPIC) $(TARGET_CPPFLAGS) -Os

TARGET_LDFLAGS += -llua -shared

define Build/Compile
	echo $(PKG_BUILD_DIR)
	echo $(PKG_SOURCE_SUBDIR)
	$(TARGET_CC) $(TARGET_CFLAGS) $(PKG_BUILD_DIR)/liblpty.c $(TARGET_LDFLAGS) -o $(PKG_BUILD_DIR)/liblpty.so
endef

define Build/InstallDev
	$(INSTALL_DIR) $(STAGING_DIR)/usr/include
	$(INSTALL_DIR) $(STAGING_DIR)/usr/lib/lua
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/liblpty.h $(STAGING_DIR)/usr/include
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/liblpty.so $(STAGING_DIR)/usr/lib/lua/liblpty.so
endef

define Package/liblpty/install
	$(INSTALL_DIR) $(1)/usr/lib/lua/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/liblpty.so $(1)/usr/lib/lua/liblpty.so
endef

$(eval $(call BuildPackage,liblpty))
