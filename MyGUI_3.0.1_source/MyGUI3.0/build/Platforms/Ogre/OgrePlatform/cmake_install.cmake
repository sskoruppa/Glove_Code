# Install script for directory: C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/Platforms/Ogre/OgrePlatform

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
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/MYGUI" TYPE FILE FILES
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/Platforms/Ogre/OgrePlatform/include/MyGUI_LastHeader.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/Platforms/Ogre/OgrePlatform/include/MyGUI_OgreDataManager.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/Platforms/Ogre/OgrePlatform/include/MyGUI_OgreDataStream.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/Platforms/Ogre/OgrePlatform/include/MyGUI_OgreDiagnostic.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/Platforms/Ogre/OgrePlatform/include/MyGUI_OgrePlatform.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/Platforms/Ogre/OgrePlatform/include/MyGUI_OgreRenderManager.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/Platforms/Ogre/OgrePlatform/include/MyGUI_OgreTexture.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/Platforms/Ogre/OgrePlatform/include/MyGUI_OgreRTTexture.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/Platforms/Ogre/OgrePlatform/include/MyGUI_OgreVertexBuffer.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/Release" TYPE STATIC_LIBRARY FILES "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/build/lib/Release/MyGUI.OgrePlatform.lib")
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/RelWithDebInfo" TYPE STATIC_LIBRARY FILES "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/build/lib/RelWithDebInfo/MyGUI.OgrePlatform.lib")
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/MinSizeRel" TYPE STATIC_LIBRARY FILES "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/build/lib/MinSizeRel/MyGUI.OgrePlatform.lib")
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/Debug" TYPE STATIC_LIBRARY FILES "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/build/lib/Debug/MyGUI.OgrePlatform_d.lib")
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/MYGUI" TYPE FILE FILES
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/Platforms/Ogre/OgrePlatform/include/MyGUI_LastHeader.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/Platforms/Ogre/OgrePlatform/include/MyGUI_OgreDataManager.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/Platforms/Ogre/OgrePlatform/include/MyGUI_OgreDataStream.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/Platforms/Ogre/OgrePlatform/include/MyGUI_OgreDiagnostic.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/Platforms/Ogre/OgrePlatform/include/MyGUI_OgrePlatform.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/Platforms/Ogre/OgrePlatform/include/MyGUI_OgreRenderManager.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/Platforms/Ogre/OgrePlatform/include/MyGUI_OgreTexture.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/Platforms/Ogre/OgrePlatform/include/MyGUI_OgreRTTexture.h"
    "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/Platforms/Ogre/OgrePlatform/include/MyGUI_OgreVertexBuffer.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/Release" TYPE STATIC_LIBRARY FILES "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/build/lib/Release/MyGUI.OgrePlatform.lib")
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/RelWithDebInfo" TYPE STATIC_LIBRARY FILES "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/build/lib/RelWithDebInfo/MyGUI.OgrePlatform.lib")
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/MinSizeRel" TYPE STATIC_LIBRARY FILES "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/build/lib/MinSizeRel/MyGUI.OgrePlatform.lib")
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/Debug" TYPE STATIC_LIBRARY FILES "C:/Dokumente und Einstellungen/superuser/Eigene Dateien/Samplecode/Glove Demo/MyGUI_3.0.1_source/MyGUI3.0/build/lib/Debug/MyGUI.OgrePlatform_d.lib")
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

