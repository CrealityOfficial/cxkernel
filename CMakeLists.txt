__cc_find(cxbin)
__cc_find(QhullWrapper)
__assert_target(cxbin)
__assert_target(qhullWrapper)

set(SRCS cxkernel/cxkernelinterface.h
		 cxkernel/kernel/data.h
		 cxkernel/kernel/cxkernel.h
		 cxkernel/kernel/cxkernel.cpp
		 cxkernel/kernel/visualscene.h
		 cxkernel/kernel/visualscene.cpp
		 cxkernel/render/xeffect.h
		 cxkernel/render/xeffect.cpp
		 cxkernel/render/xentity.h
		 cxkernel/render/xentity.cpp
		 cxkernel/render/xrendergraph.h
		 cxkernel/render/xrendergraph.cpp
		 cxkernel/render/xrenderpass.h
		 cxkernel/render/xrenderpass.cpp
		 cxkernel/interface/renderinterface.h
		 cxkernel/interface/renderinterface.cpp
		 cxkernel/interface/iointerface.h
		 cxkernel/interface/iointerface.cpp
		 cxkernel/interface/jobsinterface.h
		 cxkernel/interface/jobsinterface.cpp
		 cxkernel/interface/modelninterface.h
		 cxkernel/interface/modelninterface.cpp
		 cxkernel/utils/meshloader.h
		 cxkernel/utils/meshloader.cpp
		 cxkernel/utils/meshloadjob.h
		 cxkernel/utils/meshloadjob.cpp
		 cxkernel/utils/modelfrommeshjob.h
		 cxkernel/utils/modelfrommeshjob.cpp
		 cxkernel/data/header.h
		 cxkernel/data/header.cpp
		 cxkernel/data/modelndata.h
		 cxkernel/data/modelndata.cpp
		 cxkernel/utils/dumpproxy.h
		 cxkernel/utils/dumpproxy.cpp
		 cxkernel/data/capturetask.h
		 cxkernel/data/capturetask.cpp
		 cxkernel/data/captureSetupData.h
		 cxkernel/utils/capturehelper.h
		 cxkernel/utils/capturehelper.cpp
		 cxkernel/utils/capturecontainer.h
		 cxkernel/utils/capturecontainer.cpp
		)
			  
set(QRCS res/cxkernel.qrc)

set(LIBS)
if(CC_BC_WIN)
	list(APPEND LIBS Dbghelp.lib)
endif()

set(ILIBS ${qtuser} trimesh2 cxbin stringutil qhullWrapper mmesh qcxutil)
set(INCS ${CMAKE_CURRENT_SOURCE_DIR})
set(DEFS CXKERNEL_DLL NOMINMAX)

__add_real_target(cxkernel dll SOURCE ${SRCS}
								LIB ${LIBS}
								ILIB ${ILIBS}
								INC ${INCS}
								DEF ${DEFS}
								INTERFACE ${INCS}
								QTQRC ${QRCS}
								SOURCE_FOLDER
								)