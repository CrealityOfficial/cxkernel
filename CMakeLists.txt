set(SRCS)
set(ILIBS ${qtuser})
set(INCS)

__add_real_target(cxkernel dll SOURCE ${SRCS}
								ILIB ${ILIBS}
								INC ${INCS}
								INTERFACE ${INCS}
								SOURCE_FOLDER
								)