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
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/CvHelper.o \
	${OBJECTDIR}/MyMath.o \
	${OBJECTDIR}/VideoHandler.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/NewCamHandler.o \
	${OBJECTDIR}/ImageInput.o \
	${OBJECTDIR}/FileManager.o \
	${OBJECTDIR}/CvVideoCapture.o \
	${OBJECTDIR}/CamHandler.o \
	${OBJECTDIR}/NopImageModificator.o \
	${OBJECTDIR}/ImageSequenceInput.o \
	${OBJECTDIR}/ImageModificator.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-m64 -std=gnu++0x -pipe
CXXFLAGS=-m64 -std=gnu++0x -pipe

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

${OBJECTDIR}/CvHelper.o: CvHelper.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -Wall -D__GXX_EXPERIMENTAL_CXX0X__ -DDEBUG -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/CvHelper.o CvHelper.cpp

${OBJECTDIR}/MyMath.o: MyMath.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -Wall -D__GXX_EXPERIMENTAL_CXX0X__ -DDEBUG -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/MyMath.o MyMath.cpp

${OBJECTDIR}/VideoHandler.o: VideoHandler.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -Wall -D__GXX_EXPERIMENTAL_CXX0X__ -DDEBUG -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/VideoHandler.o VideoHandler.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -Wall -D__GXX_EXPERIMENTAL_CXX0X__ -DDEBUG -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/NewCamHandler.o: NewCamHandler.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -Wall -D__GXX_EXPERIMENTAL_CXX0X__ -DDEBUG -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/NewCamHandler.o NewCamHandler.cpp

${OBJECTDIR}/ImageInput.o: ImageInput.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -Wall -D__GXX_EXPERIMENTAL_CXX0X__ -DDEBUG -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/ImageInput.o ImageInput.cpp

${OBJECTDIR}/FileManager.o: FileManager.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -Wall -D__GXX_EXPERIMENTAL_CXX0X__ -DDEBUG -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/FileManager.o FileManager.cpp

${OBJECTDIR}/CvVideoCapture.o: CvVideoCapture.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -Wall -D__GXX_EXPERIMENTAL_CXX0X__ -DDEBUG -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/CvVideoCapture.o CvVideoCapture.cpp

${OBJECTDIR}/CamHandler.o: CamHandler.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -Wall -D__GXX_EXPERIMENTAL_CXX0X__ -DDEBUG -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/CamHandler.o CamHandler.cpp

${OBJECTDIR}/NopImageModificator.o: NopImageModificator.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -Wall -D__GXX_EXPERIMENTAL_CXX0X__ -DDEBUG -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/NopImageModificator.o NopImageModificator.cpp

${OBJECTDIR}/ImageSequenceInput.o: ImageSequenceInput.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -Wall -D__GXX_EXPERIMENTAL_CXX0X__ -DDEBUG -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/ImageSequenceInput.o ImageSequenceInput.cpp

${OBJECTDIR}/ImageModificator.o: ImageModificator.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -Wall -D__GXX_EXPERIMENTAL_CXX0X__ -DDEBUG -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/ImageModificator.o ImageModificator.cpp

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
