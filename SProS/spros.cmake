DECLARE_EXTENSION(spros)
DECLARE_IDL(SProS) # Interface set version: 3
DECLARE_IDL_DEPENDENCY(MathML_content_APISPEC)
DECLARE_EXTENSION_END(spros)

INCLUDE_DIRECTORIES(SProS/sources)

ADD_LIBRARY(spros
  SProS/sources/SProSImpl.cpp)
TARGET_LINK_LIBRARIES(spros cellml ${CMAKE_DL_LIBS})
SET_TARGET_PROPERTIES(spros PROPERTIES VERSION ${GLOBAL_VERSION} SOVERSION ${SPROS_SOVERSION})
target_link_libraries(libcellml INTERFACE spros)
INSTALL(TARGETS spros DESTINATION lib)

DECLARE_BOOTSTRAP("SProSBootstrap" "SProS" "Bootstrap" "SProS" "createSProSBootstrap" "CreateSProSBootstrap" "SProSBootstrap.hpp" "SProS/sources" "spros")

DECLARE_CPPUNIT_FILE(SProS)
DECLARE_TEST_LIB(spros)
