__cc_find(trimesh2)

set(SRCS cxkernel/cxkernelinterface.h
		 cxkernel/kernel/cxkernel.h
		 cxkernel/kernel/cxkernel.cpp
		 cxkernel/kernel/visualscene.h
		 cxkernel/kernel/visualscene.cpp
		 cxkernel/render/boxentity.h
		 cxkernel/render/boxentity.cpp
		 cxkernel/interface/renderinterface.h
		 cxkernel/interface/renderinterface.cpp
		)
			  
set(QRCS res/cxkernel.qrc)

set(ILIBS ${qtuser})
set(INCS ${CMAKE_CURRENT_SOURCE_DIR})
set(DEFS CXKERNEL_DLL NOMINMAX)

__add_real_target(cxkernel dll SOURCE ${SRCS}
								ILIB ${ILIBS}
								INC ${INCS}
								DEF ${DEFS}
								INTERFACE ${INCS}
								QTQRC ${QRCS}
								SOURCE_FOLDER
								)