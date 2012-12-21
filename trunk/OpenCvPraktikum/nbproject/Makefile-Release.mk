#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/View/TrackbarData.o \
	${OBJECTDIR}/Test/ATest.o \
	${OBJECTDIR}/CvHelper.o \
	${OBJECTDIR}/MyMath.o \
	${OBJECTDIR}/Modifier/ImageModificator.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/Control/RecorderCtl.o \
	${OBJECTDIR}/Input/AInputHandler.o \
	${OBJECTDIR}/Modifier/HsvModifier.o \
	${OBJECTDIR}/Modifier/ScaleModificator.o \
	${OBJECTDIR}/Output/VideoOutput.o \
	${OBJECTDIR}/FileManager.o \
	${OBJECTDIR}/CvVideoCapture.o \
	${OBJECTDIR}/Input/ImageSequenceInput.o \
	${OBJECTDIR}/Output/ImageListOutput.o \
	${OBJECTDIR}/Input/ImageInput.o \
	${OBJECTDIR}/Output/Output.o \
	${OBJECTDIR}/View/Window.o \
	${OBJECTDIR}/Input/InputHandler.o \
	${OBJECTDIR}/Modifier/CompositeModificator.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L/usr/local/lib `pkg-config --libs opencv`  

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/opencvpraktikum

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/opencvpraktikum: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/opencvpraktikum ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/View/TrackbarData.o: View/TrackbarData.cpp 
	${MKDIR} -p ${OBJECTDIR}/View
	${RM} $@.d
	$(COMPILE.cc) -Wall -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv` -std=c++11   -MMD -MP -MF $@.d -o ${OBJECTDIR}/View/TrackbarData.o View/TrackbarData.cpp

${OBJECTDIR}/Test/ATest.o: Test/ATest.cpp 
	${MKDIR} -p ${OBJECTDIR}/Test
	${RM} $@.d
	$(COMPILE.cc) -Wall -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv` -std=c++11   -MMD -MP -MF $@.d -o ${OBJECTDIR}/Test/ATest.o Test/ATest.cpp

${OBJECTDIR}/CvHelper.o: CvHelper.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -Wall -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv` -std=c++11   -MMD -MP -MF $@.d -o ${OBJECTDIR}/CvHelper.o CvHelper.cpp

${OBJECTDIR}/MyMath.o: MyMath.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -Wall -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv` -std=c++11   -MMD -MP -MF $@.d -o ${OBJECTDIR}/MyMath.o MyMath.cpp

${OBJECTDIR}/Modifier/ImageModificator.o: Modifier/ImageModificator.cpp 
	${MKDIR} -p ${OBJECTDIR}/Modifier
	${RM} $@.d
	$(COMPILE.cc) -Wall -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv` -std=c++11   -MMD -MP -MF $@.d -o ${OBJECTDIR}/Modifier/ImageModificator.o Modifier/ImageModificator.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -Wall -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv` -std=c++11   -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/Control/RecorderCtl.o: Control/RecorderCtl.cpp 
	${MKDIR} -p ${OBJECTDIR}/Control
	${RM} $@.d
	$(COMPILE.cc) -Wall -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv` -std=c++11   -MMD -MP -MF $@.d -o ${OBJECTDIR}/Control/RecorderCtl.o Control/RecorderCtl.cpp

${OBJECTDIR}/Input/AInputHandler.o: Input/AInputHandler.cpp 
	${MKDIR} -p ${OBJECTDIR}/Input
	${RM} $@.d
	$(COMPILE.cc) -Wall -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv` -std=c++11   -MMD -MP -MF $@.d -o ${OBJECTDIR}/Input/AInputHandler.o Input/AInputHandler.cpp

${OBJECTDIR}/Modifier/HsvModifier.o: Modifier/HsvModifier.cpp 
	${MKDIR} -p ${OBJECTDIR}/Modifier
	${RM} $@.d
	$(COMPILE.cc) -Wall -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv` -std=c++11   -MMD -MP -MF $@.d -o ${OBJECTDIR}/Modifier/HsvModifier.o Modifier/HsvModifier.cpp

${OBJECTDIR}/Modifier/ScaleModificator.o: Modifier/ScaleModificator.cpp 
	${MKDIR} -p ${OBJECTDIR}/Modifier
	${RM} $@.d
	$(COMPILE.cc) -Wall -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv` -std=c++11   -MMD -MP -MF $@.d -o ${OBJECTDIR}/Modifier/ScaleModificator.o Modifier/ScaleModificator.cpp

${OBJECTDIR}/Output/VideoOutput.o: Output/VideoOutput.cpp 
	${MKDIR} -p ${OBJECTDIR}/Output
	${RM} $@.d
	$(COMPILE.cc) -Wall -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv` -std=c++11   -MMD -MP -MF $@.d -o ${OBJECTDIR}/Output/VideoOutput.o Output/VideoOutput.cpp

${OBJECTDIR}/FileManager.o: FileManager.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -Wall -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv` -std=c++11   -MMD -MP -MF $@.d -o ${OBJECTDIR}/FileManager.o FileManager.cpp

${OBJECTDIR}/CvVideoCapture.o: CvVideoCapture.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -Wall -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv` -std=c++11   -MMD -MP -MF $@.d -o ${OBJECTDIR}/CvVideoCapture.o CvVideoCapture.cpp

${OBJECTDIR}/Input/ImageSequenceInput.o: Input/ImageSequenceInput.cpp 
	${MKDIR} -p ${OBJECTDIR}/Input
	${RM} $@.d
	$(COMPILE.cc) -Wall -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv` -std=c++11   -MMD -MP -MF $@.d -o ${OBJECTDIR}/Input/ImageSequenceInput.o Input/ImageSequenceInput.cpp

${OBJECTDIR}/Output/ImageListOutput.o: Output/ImageListOutput.cpp 
	${MKDIR} -p ${OBJECTDIR}/Output
	${RM} $@.d
	$(COMPILE.cc) -Wall -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv` -std=c++11   -MMD -MP -MF $@.d -o ${OBJECTDIR}/Output/ImageListOutput.o Output/ImageListOutput.cpp

${OBJECTDIR}/Input/ImageInput.o: Input/ImageInput.cpp 
	${MKDIR} -p ${OBJECTDIR}/Input
	${RM} $@.d
	$(COMPILE.cc) -Wall -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv` -std=c++11   -MMD -MP -MF $@.d -o ${OBJECTDIR}/Input/ImageInput.o Input/ImageInput.cpp

${OBJECTDIR}/Output/Output.o: Output/Output.cpp 
	${MKDIR} -p ${OBJECTDIR}/Output
	${RM} $@.d
	$(COMPILE.cc) -Wall -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv` -std=c++11   -MMD -MP -MF $@.d -o ${OBJECTDIR}/Output/Output.o Output/Output.cpp

${OBJECTDIR}/View/Window.o: View/Window.cpp 
	${MKDIR} -p ${OBJECTDIR}/View
	${RM} $@.d
	$(COMPILE.cc) -Wall -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv` -std=c++11   -MMD -MP -MF $@.d -o ${OBJECTDIR}/View/Window.o View/Window.cpp

${OBJECTDIR}/Input/InputHandler.o: Input/InputHandler.cpp 
	${MKDIR} -p ${OBJECTDIR}/Input
	${RM} $@.d
	$(COMPILE.cc) -Wall -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv` -std=c++11   -MMD -MP -MF $@.d -o ${OBJECTDIR}/Input/InputHandler.o Input/InputHandler.cpp

${OBJECTDIR}/Modifier/CompositeModificator.o: Modifier/CompositeModificator.cpp 
	${MKDIR} -p ${OBJECTDIR}/Modifier
	${RM} $@.d
	$(COMPILE.cc) -Wall -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv` -std=c++11   -MMD -MP -MF $@.d -o ${OBJECTDIR}/Modifier/CompositeModificator.o Modifier/CompositeModificator.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/opencvpraktikum

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
