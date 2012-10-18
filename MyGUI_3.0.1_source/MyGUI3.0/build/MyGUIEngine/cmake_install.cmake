# Install script for directory: C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/build/sdk")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "Release")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/Release" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/build/lib/Release/MyGUIEngine.lib")
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/Release" TYPE SHARED_LIBRARY FILES "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/build/bin/Release/MyGUIEngine.dll")
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/RelWithDebInfo" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/build/lib/RelWithDebInfo/MyGUIEngine.lib")
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/RelWithDebInfo" TYPE SHARED_LIBRARY FILES "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/build/bin/RelWithDebInfo/MyGUIEngine.dll")
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/MinSizeRel" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/build/lib/MinSizeRel/MyGUIEngine.lib")
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/MinSizeRel" TYPE SHARED_LIBRARY FILES "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/build/bin/MinSizeRel/MyGUIEngine.dll")
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/Debug" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/build/lib/Debug/MyGUIEngine_d.lib")
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/Debug" TYPE SHARED_LIBRARY FILES "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/build/bin/Debug/MyGUIEngine_d.dll")
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/MYGUI" TYPE FILE FILES
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_Allocator.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_CustomAllocator.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_DDItemInfo.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_IBItemInfo.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_MenuItemType.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_MessageStyle.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_WidgetToolTip.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_Button.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_Canvas.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_ComboBox.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_DDContainer.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_Edit.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_HScroll.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_ItemBox.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_List.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_ListBox.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_ListCtrl.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_MenuBar.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_MenuCtrl.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_MenuItem.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_Message.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_MultiList.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_PopupMenu.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_Progress.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_ScrollView.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_StaticImage.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_StaticText.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_Tab.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_TabItem.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_VScroll.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_Widget.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_Window.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_IWidgetFactory.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_Bitwise.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_CoordConverter.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_DataFileStream.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_DataStream.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_Delegate.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_DelegateImplement.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_DynLib.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_Enumerator.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_EventPair.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_Guid.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_RenderOut.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_TextChangeHistory.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_TextIterator.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_TextureUtility.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_TextView.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_Timer.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_UString.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_Utility.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_WidgetTranslate.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_XmlDocument.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_LogManager.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_LogStream.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_CastWidget.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_Common.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_Diagnostic.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_Exception.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_GenericFactory.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_Macros.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_Platform.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_Precompiled.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_Prerequest.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_RenderFormat.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_ResourceHolder.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_WidgetDefines.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_ICroppedRectangle.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_IDataStream.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_Instance.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_IObject.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_ISerializable.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_ITexture.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_IUnlinkWidget.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_IVertexBuffer.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_IWidgetCreator.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_Plugin.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_RTTI.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_BiIndexBase.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_ScrollViewBase.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_WidgetEvent.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_WidgetUserData.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_EditText.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_MainSkin.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_RawRect.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_RotatingSkin.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_SimpleText.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_SubSkin.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_TileRect.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_IStateInfo.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_ISubWidget.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_ISubWidgetRect.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_ISubWidgetText.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_LayerItem.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_LayerNode.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_OverlappedLayer.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_RenderItem.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_SharedLayer.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_SharedLayerNode.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_ILayer.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_ILayerItem.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_ILayerNode.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_IRenderTarget.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_ActionController.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_ControllerEdgeHide.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_ControllerFadeAlpha.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_ControllerItem.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_ControllerPosition.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_ResourceImageSet.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_ResourceImageSetPointer.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_ResourceManualFont.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_ResourceManualPointer.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_ResourceSkin.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_ResourceTrueTypeFont.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_IFont.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_IPointer.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_IResource.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_ChildSkinInfo.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_FontData.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_MaskPickInfo.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_SubWidgetBinding.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_SubWidgetInfo.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_Align.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_Any.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_Colour.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_CommonStateInfo.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_ImageInfo.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_InputDefine.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_RenderTargetInfo.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_TCoord.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_TPoint.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_TRect.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_TSize.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_Types.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_Version.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_VertexData.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_WidgetStyle.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_ClipboardManager.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_ControllerManager.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_DataManager.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_DynLibManager.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_FactoryManager.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_FontManager.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_Gui.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_InputManager.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_LanguageManager.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_LayerManager.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_LayoutManager.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_PluginManager.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_PointerManager.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_RenderManager.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_ResourceManager.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_SkinManager.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_SubWidgetManager.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/MyGUIEngine/include/MyGUI_WidgetManager.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

