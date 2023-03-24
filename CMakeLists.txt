__cc_find(trimesh2)

set(INC_PREFIX include/cxkernel)
set(INC_SRCS ${INC_PREFIX}/cxkernelinterface.h
			 ${INC_PREFIX}/kernel/cxkernel.h
			 )
			 
set(IMPL_SRCS kernel/cxkernel.cpp)
set(QRCS res/cxkernel.qrc)

set(SRCS ${INC_SRCS} ${IMPL_SRCS})
set(ILIBS ${qtuser})
set(INCS ${CMAKE_CURRENT_SOURCE_DIR}/include/)
set(DEFS CXKERNEL_DLL NOMINMAX)

__add_real_target(cxkernel dll SOURCE ${SRCS}
								ILIB ${ILIBS}
								INC ${INCS}
								DEF ${DEFS}
								INTERFACE ${INCS}
								QTQRC ${QRCS}
								SOURCE_FOLDER
								)