__cc_find(cxbin)
__cc_find(QhullWrapper)
__assert_target(cxbin)
__assert_target(qhullWrapper)

__files_group(${CMAKE_CURRENT_SOURCE_DIR}/cxkernel/ SRCS)
set(QRCS res/cxkernel.qrc)

set(LIBS)
if(CC_BC_WIN)
	list(APPEND LIBS Dbghelp.lib)
endif()

set(ILIBS ${qtuser} trimesh2 cxbin stringutil qhullWrapper mmesh qcxutil cxcloud)
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
