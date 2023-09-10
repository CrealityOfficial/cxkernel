set(CMAKE_CXX_STANDARD 14)

__cc_find(topomesh)
__cc_find(nestplacer)

__cc_find(trimesh2)
__assert_target(trimesh2)

__cc_find(cxbin)
__cc_find(QhullWrapper)
__assert_target(cxbin)
__assert_target(qhullWrapper)
__cc_find(Boost)
__assert_target(boost_nowide)

__cc_find(openssl)
__assert_target(ssl)
__assert_target(crypto)

__files_group(${CMAKE_CURRENT_SOURCE_DIR}/cxkernel/ SRCS)
set(QRCS res/cxkernel.qrc res/images.qrc)

set(LIBS cxbin cxutil ssl crypto qhullWrapper)
set(ILIBS qtuser_core trimesh2 mmesh cxnd)

if(TARGET cxcloud)
	list(APPEND ILIBS cxcloud)
endif()

if(TARGET topomesh)
	list(APPEND LIBS topomesh)
endif()

if(TARGET nestplacer)
	list(APPEND LIBS nestplacer)
endif()

if(CC_BC_WIN)
	list(APPEND LIBS Dbghelp.lib crypt32 ws2_32)
elseif(CC_BC_MAC)
	# add_compile_options(-x objective-c++)
	list(APPEND SRCS ${CMAKE_CURRENT_SOURCE_DIR}/macwindow/macwindow.h ${CMAKE_CURRENT_SOURCE_DIR}/macwindow/macwindow.mm 
	${CMAKE_CURRENT_SOURCE_DIR}/macwindow/mycppobject.h ${CMAKE_CURRENT_SOURCE_DIR}/macwindow/mycppobject.cpp)
	find_library(APP_KIT Appkit Foundation)
	list(APPEND ILIBS ${APP_KIT})
endif()

set(INCS ${CMAKE_CURRENT_SOURCE_DIR})
set(DEFS CXKERNEL_DLL NOMINMAX)

__add_real_target(cxkernel dll SOURCE ${SRCS}
								LIB ${LIBS}
								ILIB ${ILIBS}
								INC ${INCS}
								DEF ${DEFS}
								INTERFACE ${INCS}
								QTQRC ${QRCS}
								)
