#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-free.mk)" "nbproject/Makefile-local-free.mk"
include nbproject/Makefile-local-free.mk
endif
endif

# Environment
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=free
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/UBMP4-Intro-1-Input-Output.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/UBMP4-Intro-1-Input-Output.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=UBMP4.c morseCode.c senderMode.c buzzer.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/UBMP4.p1 ${OBJECTDIR}/morseCode.p1 ${OBJECTDIR}/senderMode.p1 ${OBJECTDIR}/buzzer.p1
POSSIBLE_DEPFILES=${OBJECTDIR}/UBMP4.p1.d ${OBJECTDIR}/morseCode.p1.d ${OBJECTDIR}/senderMode.p1.d ${OBJECTDIR}/buzzer.p1.d

# Object Files
OBJECTFILES=${OBJECTDIR}/UBMP4.p1 ${OBJECTDIR}/morseCode.p1 ${OBJECTDIR}/senderMode.p1 ${OBJECTDIR}/buzzer.p1

# Source Files
SOURCEFILES=UBMP4.c morseCode.c senderMode.c buzzer.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-free.mk dist/${CND_CONF}/${IMAGE_TYPE}/UBMP4-Intro-1-Input-Output.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=16F1459
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/UBMP4.p1: UBMP4.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/UBMP4.p1.d 
	@${RM} ${OBJECTDIR}/UBMP4.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -mrom=default,-0-07FF -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -mext=cci -Wa,-a -DXPRJ_free=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=800  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/UBMP4.p1 UBMP4.c 
	@-${MV} ${OBJECTDIR}/UBMP4.d ${OBJECTDIR}/UBMP4.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/UBMP4.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/morseCode.p1: morseCode.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/morseCode.p1.d 
	@${RM} ${OBJECTDIR}/morseCode.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -mrom=default,-0-07FF -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -mext=cci -Wa,-a -DXPRJ_free=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=800  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/morseCode.p1 morseCode.c 
	@-${MV} ${OBJECTDIR}/morseCode.d ${OBJECTDIR}/morseCode.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/morseCode.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/senderMode.p1: senderMode.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/senderMode.p1.d 
	@${RM} ${OBJECTDIR}/senderMode.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -mrom=default,-0-07FF -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -mext=cci -Wa,-a -DXPRJ_free=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=800  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/senderMode.p1 senderMode.c 
	@-${MV} ${OBJECTDIR}/senderMode.d ${OBJECTDIR}/senderMode.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/senderMode.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/buzzer.p1: buzzer.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/buzzer.p1.d 
	@${RM} ${OBJECTDIR}/buzzer.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -mrom=default,-0-07FF -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -mext=cci -Wa,-a -DXPRJ_free=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=800  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/buzzer.p1 buzzer.c 
	@-${MV} ${OBJECTDIR}/buzzer.d ${OBJECTDIR}/buzzer.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/buzzer.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/UBMP4.p1: UBMP4.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/UBMP4.p1.d 
	@${RM} ${OBJECTDIR}/UBMP4.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -mrom=default,-0-07FF -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -mext=cci -Wa,-a -DXPRJ_free=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=800  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/UBMP4.p1 UBMP4.c 
	@-${MV} ${OBJECTDIR}/UBMP4.d ${OBJECTDIR}/UBMP4.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/UBMP4.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/morseCode.p1: morseCode.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/morseCode.p1.d 
	@${RM} ${OBJECTDIR}/morseCode.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -mrom=default,-0-07FF -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -mext=cci -Wa,-a -DXPRJ_free=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=800  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/morseCode.p1 morseCode.c 
	@-${MV} ${OBJECTDIR}/morseCode.d ${OBJECTDIR}/morseCode.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/morseCode.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/senderMode.p1: senderMode.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/senderMode.p1.d 
	@${RM} ${OBJECTDIR}/senderMode.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -mrom=default,-0-07FF -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -mext=cci -Wa,-a -DXPRJ_free=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=800  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/senderMode.p1 senderMode.c 
	@-${MV} ${OBJECTDIR}/senderMode.d ${OBJECTDIR}/senderMode.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/senderMode.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/buzzer.p1: buzzer.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/buzzer.p1.d 
	@${RM} ${OBJECTDIR}/buzzer.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -mrom=default,-0-07FF -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -mext=cci -Wa,-a -DXPRJ_free=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=800  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/buzzer.p1 buzzer.c 
	@-${MV} ${OBJECTDIR}/buzzer.d ${OBJECTDIR}/buzzer.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/buzzer.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/UBMP4-Intro-1-Input-Output.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=dist/${CND_CONF}/${IMAGE_TYPE}/UBMP4-Intro-1-Input-Output.X.${IMAGE_TYPE}.map  -D__DEBUG=1  -DXPRJ_free=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -mrom=default,-0-07FF -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -mext=cci -Wa,-a -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=800  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -std=c99 -gdwarf-3 -mstack=compiled:auto:auto        $(COMPARISON_BUILD) -Wl,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -o dist/${CND_CONF}/${IMAGE_TYPE}/UBMP4-Intro-1-Input-Output.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	@${RM} dist/${CND_CONF}/${IMAGE_TYPE}/UBMP4-Intro-1-Input-Output.X.${IMAGE_TYPE}.hex 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/UBMP4-Intro-1-Input-Output.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=dist/${CND_CONF}/${IMAGE_TYPE}/UBMP4-Intro-1-Input-Output.X.${IMAGE_TYPE}.map  -DXPRJ_free=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -mrom=default,-0-07FF -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -mext=cci -Wa,-a -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=800  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     $(COMPARISON_BUILD) -Wl,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -o dist/${CND_CONF}/${IMAGE_TYPE}/UBMP4-Intro-1-Input-Output.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/free
	${RM} -r dist/free

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
