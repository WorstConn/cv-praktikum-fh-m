/* 
 * File:   Output.h
 * Author: Julian Cordes, Nils Frenking
 *
 * Created on 19. Dezember 2012, 20:47
 */

#ifndef OUTPUT_H
#define	OUTPUT_H
#include "../header.h"
using namespace std;
using namespace cv;

class Output {
public:
    Output(String path, String name, String fileExt);

    Output(const Output& orig);
    virtual ~Output();
    virtual String getOutputName();
    virtual String getOutputPath();
    virtual void write(Mat& mat) = 0;
    virtual bool open() = 0;
    virtual void close() = 0;
    virtual bool isOpen();
    virtual void setSize(Size s);
private:
    virtual bool checkPath(String p);
    virtual bool checkFile(String f);
protected:
    virtual String getFullPath();

    String fileExtension;
    String outputPath;
    String outputName;
    Size outputSize;
    bool pathExists;
    bool fileExists;
    bool opened;


};

#endif	/* OUTPUT_H */

