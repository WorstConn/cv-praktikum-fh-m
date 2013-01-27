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
	${OBJECTDIR}/Objects/ExtendedImageAttributes.o \
	${OBJECTDIR}/Test/ATest.o \
	${OBJECTDIR}/View/CvWindow.o \
	${OBJECTDIR}/Helper/TwoFingersPositiveSample.o \
	${OBJECTDIR}/Helper/SampleCreator.o \
	${OBJECTDIR}/Helper/FileManager.o \
	${OBJECTDIR}/Modifier/ImageModificator.o \
	${OBJECTDIR}/Helper/FourFingersPositveSample.o \
	${OBJECTDIR}/Objects/HistogramCreationMethod.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/Helper/NegativeSample.o \
	${OBJECTDIR}/Test/CreateNegativeSamplesTest.o \
	${OBJECTDIR}/Control/RecorderCtl.o \
	${OBJECTDIR}/Test/CreatePositiveSamplesTest.o \
	${OBJECTDIR}/View/ModificatorAction.o \
	${OBJECTDIR}/Test/WindowManagerTest.o \
	${OBJECTDIR}/Input/AInputHandler.o \
	${OBJECTDIR}/Modifier/HsvModifier.o \
	${OBJECTDIR}/Objects/Hand.o \
	${OBJECTDIR}/Objects/HsvHistogamCreation.o \
	${OBJECTDIR}/Test/MainTest.o \
	${OBJECTDIR}/Helper/FistPositiveSample.o \
	${OBJECTDIR}/Modifier/ModificatorComponent.o \
	${OBJECTDIR}/Test/Prak3A8.o \
	${OBJECTDIR}/Test/VideoInputToImageSequenceOutputTest.o \
	${OBJECTDIR}/Modifier/ScaleModificator.o \
	${OBJECTDIR}/Output/VideoOutput.o \
	${OBJECTDIR}/View/WindowManager.o \
	${OBJECTDIR}/Output/ImageListOutput.o \
	${OBJECTDIR}/CvVideoCapture.o \
	${OBJECTDIR}/Input/ImageSequenceInput.o \
	${OBJECTDIR}/Input/ImageInput.o \
	${OBJECTDIR}/Helper/CvHelper.o \
	${OBJECTDIR}/Output/Output.o \
	${OBJECTDIR}/View/AAction.o \
	${OBJECTDIR}/Test/ClassificationTest.o \
	${OBJECTDIR}/Objects/MaskCreationMethod.o \
	${OBJECTDIR}/Helper/ThumbUpPositiveSample.o \
	${OBJECTDIR}/Helper/CreationBehavior.o \
	${OBJECTDIR}/Input/InputHandler.o \
	${OBJECTDIR}/View/AImageAction.o \
	${OBJECTDIR}/Helper/ThreeFingersPositiveSample.o \
	${OBJECTDIR}/Helper/MyMath.o \
	${OBJECTDIR}/Objects/SimpleMaskCreation.o \
	${OBJECTDIR}/Modifier/CompositeModificator.o \
	${OBJECTDIR}/Objects/ContourCreationMethod.o \
	${OBJECTDIR}/Helper/PlainHandPositiveSample.o \
	${OBJECTDIR}/Objects/PixelObject.o \
	${OBJECTDIR}/Modifier/BgFgSegmModificator.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-m32 -std=gnu++0x
CXXFLAGS=-m32 -std=gnu++0x

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

${OBJECTDIR}/Objects/ExtendedImageAttributes.o: Objects/ExtendedImageAttributes.cpp 
	${MKDIR} -p ${OBJECTDIR}/Objects
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/Objects/ExtendedImageAttributes.o Objects/ExtendedImageAttributes.cpp

${OBJECTDIR}/Test/ATest.o: Test/ATest.cpp 
	${MKDIR} -p ${OBJECTDIR}/Test
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/Test/ATest.o Test/ATest.cpp

${OBJECTDIR}/View/CvWindow.o: View/CvWindow.cpp 
	${MKDIR} -p ${OBJECTDIR}/View
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/View/CvWindow.o View/CvWindow.cpp

${OBJECTDIR}/Helper/TwoFingersPositiveSample.o: Helper/TwoFingersPositiveSample.cpp 
	${MKDIR} -p ${OBJECTDIR}/Helper
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/Helper/TwoFingersPositiveSample.o Helper/TwoFingersPositiveSample.cpp

${OBJECTDIR}/Helper/SampleCreator.o: Helper/SampleCreator.cpp 
	${MKDIR} -p ${OBJECTDIR}/Helper
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/Helper/SampleCreator.o Helper/SampleCreator.cpp

${OBJECTDIR}/Helper/FileManager.o: Helper/FileManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/Helper
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/Helper/FileManager.o Helper/FileManager.cpp

${OBJECTDIR}/Modifier/ImageModificator.o: Modifier/ImageModificator.cpp 
	${MKDIR} -p ${OBJECTDIR}/Modifier
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/Modifier/ImageModificator.o Modifier/ImageModificator.cpp

${OBJECTDIR}/Helper/FourFingersPositveSample.o: Helper/FourFingersPositveSample.cpp 
	${MKDIR} -p ${OBJECTDIR}/Helper
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/Helper/FourFingersPositveSample.o Helper/FourFingersPositveSample.cpp

${OBJECTDIR}/Objects/HistogramCreationMethod.o: Objects/HistogramCreationMethod.cpp 
	${MKDIR} -p ${OBJECTDIR}/Objects
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/Objects/HistogramCreationMethod.o Objects/HistogramCreationMethod.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/Helper/NegativeSample.o: Helper/NegativeSample.cpp 
	${MKDIR} -p ${OBJECTDIR}/Helper
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/Helper/NegativeSample.o Helper/NegativeSample.cpp

${OBJECTDIR}/Test/CreateNegativeSamplesTest.o: Test/CreateNegativeSamplesTest.cpp 
	${MKDIR} -p ${OBJECTDIR}/Test
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/Test/CreateNegativeSamplesTest.o Test/CreateNegativeSamplesTest.cpp

${OBJECTDIR}/Control/RecorderCtl.o: Control/RecorderCtl.cpp 
	${MKDIR} -p ${OBJECTDIR}/Control
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/Control/RecorderCtl.o Control/RecorderCtl.cpp

${OBJECTDIR}/Test/CreatePositiveSamplesTest.o: Test/CreatePositiveSamplesTest.cpp 
	${MKDIR} -p ${OBJECTDIR}/Test
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/Test/CreatePositiveSamplesTest.o Test/CreatePositiveSamplesTest.cpp

${OBJECTDIR}/View/ModificatorAction.o: View/ModificatorAction.cpp 
	${MKDIR} -p ${OBJECTDIR}/View
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/View/ModificatorAction.o View/ModificatorAction.cpp

${OBJECTDIR}/Test/WindowManagerTest.o: Test/WindowManagerTest.cpp 
	${MKDIR} -p ${OBJECTDIR}/Test
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/Test/WindowManagerTest.o Test/WindowManagerTest.cpp

${OBJECTDIR}/Input/AInputHandler.o: Input/AInputHandler.cpp 
	${MKDIR} -p ${OBJECTDIR}/Input
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/Input/AInputHandler.o Input/AInputHandler.cpp

${OBJECTDIR}/Modifier/HsvModifier.o: Modifier/HsvModifier.cpp 
	${MKDIR} -p ${OBJECTDIR}/Modifier
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/Modifier/HsvModifier.o Modifier/HsvModifier.cpp

${OBJECTDIR}/Objects/Hand.o: Objects/Hand.cpp 
	${MKDIR} -p ${OBJECTDIR}/Objects
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/Objects/Hand.o Objects/Hand.cpp

${OBJECTDIR}/Objects/HsvHistogamCreation.o: Objects/HsvHistogamCreation.cpp 
	${MKDIR} -p ${OBJECTDIR}/Objects
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/Objects/HsvHistogamCreation.o Objects/HsvHistogamCreation.cpp

${OBJECTDIR}/Test/MainTest.o: Test/MainTest.cpp 
	${MKDIR} -p ${OBJECTDIR}/Test
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/Test/MainTest.o Test/MainTest.cpp

${OBJECTDIR}/Helper/FistPositiveSample.o: Helper/FistPositiveSample.cpp 
	${MKDIR} -p ${OBJECTDIR}/Helper
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/Helper/FistPositiveSample.o Helper/FistPositiveSample.cpp

${OBJECTDIR}/Modifier/ModificatorComponent.o: Modifier/ModificatorComponent.cpp 
	${MKDIR} -p ${OBJECTDIR}/Modifier
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/Modifier/ModificatorComponent.o Modifier/ModificatorComponent.cpp

${OBJECTDIR}/Test/Prak3A8.o: Test/Prak3A8.cpp 
	${MKDIR} -p ${OBJECTDIR}/Test
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/Test/Prak3A8.o Test/Prak3A8.cpp

${OBJECTDIR}/Test/VideoInputToImageSequenceOutputTest.o: Test/VideoInputToImageSequenceOutputTest.cpp 
	${MKDIR} -p ${OBJECTDIR}/Test
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/Test/VideoInputToImageSequenceOutputTest.o Test/VideoInputToImageSequenceOutputTest.cpp

${OBJECTDIR}/Modifier/ScaleModificator.o: Modifier/ScaleModificator.cpp 
	${MKDIR} -p ${OBJECTDIR}/Modifier
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/Modifier/ScaleModificator.o Modifier/ScaleModificator.cpp

${OBJECTDIR}/Output/VideoOutput.o: Output/VideoOutput.cpp 
	${MKDIR} -p ${OBJECTDIR}/Output
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/Output/VideoOutput.o Output/VideoOutput.cpp

${OBJECTDIR}/View/WindowManager.o: View/WindowManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/View
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/View/WindowManager.o View/WindowManager.cpp

${OBJECTDIR}/Output/ImageListOutput.o: Output/ImageListOutput.cpp 
	${MKDIR} -p ${OBJECTDIR}/Output
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/Output/ImageListOutput.o Output/ImageListOutput.cpp

${OBJECTDIR}/CvVideoCapture.o: CvVideoCapture.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/CvVideoCapture.o CvVideoCapture.cpp

${OBJECTDIR}/Input/ImageSequenceInput.o: Input/ImageSequenceInput.cpp 
	${MKDIR} -p ${OBJECTDIR}/Input
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/Input/ImageSequenceInput.o Input/ImageSequenceInput.cpp

${OBJECTDIR}/Input/ImageInput.o: Input/ImageInput.cpp 
	${MKDIR} -p ${OBJECTDIR}/Input
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/Input/ImageInput.o Input/ImageInput.cpp

${OBJECTDIR}/Helper/CvHelper.o: Helper/CvHelper.cpp 
	${MKDIR} -p ${OBJECTDIR}/Helper
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/Helper/CvHelper.o Helper/CvHelper.cpp

${OBJECTDIR}/Output/Output.o: Output/Output.cpp 
	${MKDIR} -p ${OBJECTDIR}/Output
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/Output/Output.o Output/Output.cpp

${OBJECTDIR}/View/AAction.o: View/AAction.cpp 
	${MKDIR} -p ${OBJECTDIR}/View
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/View/AAction.o View/AAction.cpp

${OBJECTDIR}/Test/ClassificationTest.o: Test/ClassificationTest.cpp 
	${MKDIR} -p ${OBJECTDIR}/Test
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/Test/ClassificationTest.o Test/ClassificationTest.cpp

${OBJECTDIR}/Objects/MaskCreationMethod.o: Objects/MaskCreationMethod.cpp 
	${MKDIR} -p ${OBJECTDIR}/Objects
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/Objects/MaskCreationMethod.o Objects/MaskCreationMethod.cpp

${OBJECTDIR}/Helper/ThumbUpPositiveSample.o: Helper/ThumbUpPositiveSample.cpp 
	${MKDIR} -p ${OBJECTDIR}/Helper
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/Helper/ThumbUpPositiveSample.o Helper/ThumbUpPositiveSample.cpp

${OBJECTDIR}/Helper/CreationBehavior.o: Helper/CreationBehavior.cpp 
	${MKDIR} -p ${OBJECTDIR}/Helper
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/Helper/CreationBehavior.o Helper/CreationBehavior.cpp

${OBJECTDIR}/Input/InputHandler.o: Input/InputHandler.cpp 
	${MKDIR} -p ${OBJECTDIR}/Input
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/Input/InputHandler.o Input/InputHandler.cpp

${OBJECTDIR}/View/AImageAction.o: View/AImageAction.cpp 
	${MKDIR} -p ${OBJECTDIR}/View
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/View/AImageAction.o View/AImageAction.cpp

${OBJECTDIR}/Helper/ThreeFingersPositiveSample.o: Helper/ThreeFingersPositiveSample.cpp 
	${MKDIR} -p ${OBJECTDIR}/Helper
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/Helper/ThreeFingersPositiveSample.o Helper/ThreeFingersPositiveSample.cpp

${OBJECTDIR}/Helper/MyMath.o: Helper/MyMath.cpp 
	${MKDIR} -p ${OBJECTDIR}/Helper
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/Helper/MyMath.o Helper/MyMath.cpp

${OBJECTDIR}/Objects/SimpleMaskCreation.o: Objects/SimpleMaskCreation.cpp 
	${MKDIR} -p ${OBJECTDIR}/Objects
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/Objects/SimpleMaskCreation.o Objects/SimpleMaskCreation.cpp

${OBJECTDIR}/Modifier/CompositeModificator.o: Modifier/CompositeModificator.cpp 
	${MKDIR} -p ${OBJECTDIR}/Modifier
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/Modifier/CompositeModificator.o Modifier/CompositeModificator.cpp

${OBJECTDIR}/Objects/ContourCreationMethod.o: Objects/ContourCreationMethod.cpp 
	${MKDIR} -p ${OBJECTDIR}/Objects
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/Objects/ContourCreationMethod.o Objects/ContourCreationMethod.cpp

${OBJECTDIR}/Helper/PlainHandPositiveSample.o: Helper/PlainHandPositiveSample.cpp 
	${MKDIR} -p ${OBJECTDIR}/Helper
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/Helper/PlainHandPositiveSample.o Helper/PlainHandPositiveSample.cpp

${OBJECTDIR}/Objects/PixelObject.o: Objects/PixelObject.cpp 
	${MKDIR} -p ${OBJECTDIR}/Objects
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/Objects/PixelObject.o Objects/PixelObject.cpp

${OBJECTDIR}/Modifier/BgFgSegmModificator.o: Modifier/BgFgSegmModificator.cpp 
	${MKDIR} -p ${OBJECTDIR}/Modifier
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 `pkg-config --cflags opencv`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/Modifier/BgFgSegmModificator.o Modifier/BgFgSegmModificator.cpp

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
