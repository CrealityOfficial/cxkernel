set(CMAKE_CXX_STANDARD 14)

__cc_find(cxbin)
__cc_find(QhullWrapper)
__assert_target(cxbin)
__assert_target(qhullWrapper)

__files_group(${CMAKE_CURRENT_SOURCE_DIR}/cxkernel/ SRCS)
set(QRCS res/cxkernel.qrc res/images.qrc)

set(LIBS)
if(CC_BC_WIN)
	list(APPEND LIBS Dbghelp.lib)
	elseif(CC_BC_MAC)
	# add_compile_options(-x objective-c++)
	list(APPEND SRCS ${CMAKE_CURRENT_SOURCE_DIR}/macwindow/macwindow.h ${CMAKE_CURRENT_SOURCE_DIR}/macwindow/macwindow.mm)
	find_library(APP_KIT Appkit Foundation)
endif()
if(CC_BC_MAC)
set(ILIBS ${qtuser} trimesh2 cxbin stringutil qhullWrapper mmesh qcxutil cxcloud ${APP_KIT} )
else()
set(ILIBS ${qtuser} trimesh2 cxbin stringutil qhullWrapper mmesh qcxutil cxcloud)
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
