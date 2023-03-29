__cc_find(cxbin)
__assert_target(cxbin)

set(SRCS cxkernel/cxkernelinterface.h
		 cxkernel/kernel/data.h
		 cxkernel/kernel/cxkernel.h
		 cxkernel/kernel/cxkernel.cpp
		 cxkernel/kernel/visualscene.h
		 cxkernel/kernel/visualscene.cpp
		 cxkernel/render/boxentity.h
		 cxkernel/render/boxentity.cpp
		 cxkernel/interface/renderinterface.h
		 cxkernel/interface/renderinterface.cpp
		 cxkernel/interface/iointerface.h
		 cxkernel/interface/iointerface.cpp
		 cxkernel/interface/jobsinterface.h
		 cxkernel/interface/jobsinterface.cpp
		 cxkernel/utils/meshloader.h
		 cxkernel/utils/meshloader.cpp
		 cxkernel/utils/meshloadjob.h
		 cxkernel/utils/meshloadjob.cpp
		)
			  
set(QRCS res/cxkernel.qrc)

set(ILIBS ${qtuser} trimesh2 cxbin stringutil)
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