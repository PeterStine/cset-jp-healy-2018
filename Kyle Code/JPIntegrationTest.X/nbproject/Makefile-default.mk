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
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/JPIntegrationTest.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/JPIntegrationTest.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=RTC2.cpp main.cpp data.S GFX/glcdfont.c GFX/tft_gfx.c GFX/tft_master.c LCD_Interface.c Touch/Touch_Driver.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/RTC2.o ${OBJECTDIR}/main.o ${OBJECTDIR}/data.o ${OBJECTDIR}/GFX/glcdfont.o ${OBJECTDIR}/GFX/tft_gfx.o ${OBJECTDIR}/GFX/tft_master.o ${OBJECTDIR}/LCD_Interface.o ${OBJECTDIR}/Touch/Touch_Driver.o
POSSIBLE_DEPFILES=${OBJECTDIR}/RTC2.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/data.o.d ${OBJECTDIR}/GFX/glcdfont.o.d ${OBJECTDIR}/GFX/tft_gfx.o.d ${OBJECTDIR}/GFX/tft_master.o.d ${OBJECTDIR}/LCD_Interface.o.d ${OBJECTDIR}/Touch/Touch_Driver.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/RTC2.o ${OBJECTDIR}/main.o ${OBJECTDIR}/data.o ${OBJECTDIR}/GFX/glcdfont.o ${OBJECTDIR}/GFX/tft_gfx.o ${OBJECTDIR}/GFX/tft_master.o ${OBJECTDIR}/LCD_Interface.o ${OBJECTDIR}/Touch/Touch_Driver.o

# Source Files
SOURCEFILES=RTC2.cpp main.cpp data.S GFX/glcdfont.c GFX/tft_gfx.c GFX/tft_master.c LCD_Interface.c Touch/Touch_Driver.c


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/JPIntegrationTest.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MZ2048EFG144
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/data.o: data.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/data.o.d 
	@${RM} ${OBJECTDIR}/data.o 
	@${RM} ${OBJECTDIR}/data.o.ok ${OBJECTDIR}/data.o.err 
	@${FIXDEPS} "${OBJECTDIR}/data.o.d" "${OBJECTDIR}/data.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_AS_PRE)  -D__DEBUG  -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/data.o.d"  -o ${OBJECTDIR}/data.o data.S  -DXPRJ_default=$(CND_CONF)  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/data.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1
	
else
${OBJECTDIR}/data.o: data.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/data.o.d 
	@${RM} ${OBJECTDIR}/data.o 
	@${RM} ${OBJECTDIR}/data.o.ok ${OBJECTDIR}/data.o.err 
	@${FIXDEPS} "${OBJECTDIR}/data.o.d" "${OBJECTDIR}/data.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/data.o.d"  -o ${OBJECTDIR}/data.o data.S  -DXPRJ_default=$(CND_CONF)  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/data.o.asm.d",--gdwarf-2
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/GFX/glcdfont.o: GFX/glcdfont.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/GFX" 
	@${RM} ${OBJECTDIR}/GFX/glcdfont.o.d 
	@${RM} ${OBJECTDIR}/GFX/glcdfont.o 
	@${FIXDEPS} "${OBJECTDIR}/GFX/glcdfont.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/GFX/glcdfont.o.d" -o ${OBJECTDIR}/GFX/glcdfont.o GFX/glcdfont.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/GFX/tft_gfx.o: GFX/tft_gfx.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/GFX" 
	@${RM} ${OBJECTDIR}/GFX/tft_gfx.o.d 
	@${RM} ${OBJECTDIR}/GFX/tft_gfx.o 
	@${FIXDEPS} "${OBJECTDIR}/GFX/tft_gfx.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/GFX/tft_gfx.o.d" -o ${OBJECTDIR}/GFX/tft_gfx.o GFX/tft_gfx.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/GFX/tft_master.o: GFX/tft_master.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/GFX" 
	@${RM} ${OBJECTDIR}/GFX/tft_master.o.d 
	@${RM} ${OBJECTDIR}/GFX/tft_master.o 
	@${FIXDEPS} "${OBJECTDIR}/GFX/tft_master.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/GFX/tft_master.o.d" -o ${OBJECTDIR}/GFX/tft_master.o GFX/tft_master.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/LCD_Interface.o: LCD_Interface.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/LCD_Interface.o.d 
	@${RM} ${OBJECTDIR}/LCD_Interface.o 
	@${FIXDEPS} "${OBJECTDIR}/LCD_Interface.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/LCD_Interface.o.d" -o ${OBJECTDIR}/LCD_Interface.o LCD_Interface.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/Touch/Touch_Driver.o: Touch/Touch_Driver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Touch" 
	@${RM} ${OBJECTDIR}/Touch/Touch_Driver.o.d 
	@${RM} ${OBJECTDIR}/Touch/Touch_Driver.o 
	@${FIXDEPS} "${OBJECTDIR}/Touch/Touch_Driver.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Touch/Touch_Driver.o.d" -o ${OBJECTDIR}/Touch/Touch_Driver.o Touch/Touch_Driver.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/GFX/glcdfont.o: GFX/glcdfont.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/GFX" 
	@${RM} ${OBJECTDIR}/GFX/glcdfont.o.d 
	@${RM} ${OBJECTDIR}/GFX/glcdfont.o 
	@${FIXDEPS} "${OBJECTDIR}/GFX/glcdfont.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/GFX/glcdfont.o.d" -o ${OBJECTDIR}/GFX/glcdfont.o GFX/glcdfont.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/GFX/tft_gfx.o: GFX/tft_gfx.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/GFX" 
	@${RM} ${OBJECTDIR}/GFX/tft_gfx.o.d 
	@${RM} ${OBJECTDIR}/GFX/tft_gfx.o 
	@${FIXDEPS} "${OBJECTDIR}/GFX/tft_gfx.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/GFX/tft_gfx.o.d" -o ${OBJECTDIR}/GFX/tft_gfx.o GFX/tft_gfx.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/GFX/tft_master.o: GFX/tft_master.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/GFX" 
	@${RM} ${OBJECTDIR}/GFX/tft_master.o.d 
	@${RM} ${OBJECTDIR}/GFX/tft_master.o 
	@${FIXDEPS} "${OBJECTDIR}/GFX/tft_master.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/GFX/tft_master.o.d" -o ${OBJECTDIR}/GFX/tft_master.o GFX/tft_master.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/LCD_Interface.o: LCD_Interface.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/LCD_Interface.o.d 
	@${RM} ${OBJECTDIR}/LCD_Interface.o 
	@${FIXDEPS} "${OBJECTDIR}/LCD_Interface.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/LCD_Interface.o.d" -o ${OBJECTDIR}/LCD_Interface.o LCD_Interface.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/Touch/Touch_Driver.o: Touch/Touch_Driver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Touch" 
	@${RM} ${OBJECTDIR}/Touch/Touch_Driver.o.d 
	@${RM} ${OBJECTDIR}/Touch/Touch_Driver.o 
	@${FIXDEPS} "${OBJECTDIR}/Touch/Touch_Driver.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Touch/Touch_Driver.o.d" -o ${OBJECTDIR}/Touch/Touch_Driver.o Touch/Touch_Driver.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/RTC2.o: RTC2.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/RTC2.o.d 
	@${RM} ${OBJECTDIR}/RTC2.o 
	@${FIXDEPS} "${OBJECTDIR}/RTC2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fenforce-eh-specs -MMD -MF "${OBJECTDIR}/RTC2.o.d" -o ${OBJECTDIR}/RTC2.o RTC2.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/main.o: main.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fenforce-eh-specs -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/RTC2.o: RTC2.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/RTC2.o.d 
	@${RM} ${OBJECTDIR}/RTC2.o 
	@${FIXDEPS} "${OBJECTDIR}/RTC2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fenforce-eh-specs -MMD -MF "${OBJECTDIR}/RTC2.o.d" -o ${OBJECTDIR}/RTC2.o RTC2.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/main.o: main.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fenforce-eh-specs -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/JPIntegrationTest.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CPPC} $(MP_EXTRA_LD_PRE) -g   -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/JPIntegrationTest.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)   -mreserve=data@0x0:0x37F   -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/JPIntegrationTest.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CPPC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/JPIntegrationTest.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/JPIntegrationTest.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
