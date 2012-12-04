/* 
 * File:   FileManager.h
 * Author: Nils Frenking, Julian Cordes
 *
 * Created on 28. November 2012, 23:28
 */

#ifndef FILEMANAGER_H
#define	FILEMANAGER_H

#include "header.h"

class FileManager {
public:
    FileManager();
    FileManager(const FileManager& orig);
    virtual ~FileManager();





    void find(String name, String dir);

private:

    int seekdir(vector<vector<String >> &mylist, String path, String name);

};

#endif	/* FILEMANAGER_H */

