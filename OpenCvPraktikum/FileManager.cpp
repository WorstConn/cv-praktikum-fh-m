/* 
 * File:   FileManager.cpp
 * Author: Nils Frenking, Julian Cordes
 * 
 * Created on 28. November 2012, 23:28
 */

#include "header.h"

using namespace std;
using namespace cv;

FileManager::FileManager() {
}

FileManager::FileManager(const FileManager& orig) {
}

FileManager::~FileManager() {
}

void FileManager::find(String name, String dir) {
    //    	const char* home = getenv("HOME");
    vector < vector < String >> mylist;
    if (seekdir(mylist, dir,name) == -1) {
        cerr<<"Error in seekdir"<<endl;
        return;
    }
    int ndirs = mylist.size();
    cout << "ndirs: " << ndirs << "\n";
    int nfiles = 0;
    vector < vector < String >> ::iterator it;
    for (it = mylist.begin(); it != mylist.end(); it++) {
        vector<String>& lst = *it;

        nfiles += lst.size();
        vector<String>::iterator iter;

        for (iter = lst.begin(); iter != lst.end(); iter++) {
            cout << "File: " << (*iter) << endl;
        }

    }
    cout << "nfiles: " << nfiles << "\n";




}

int FileManager::seekdir(vector<vector<String >> &mylist, String path, String name) {

    DIR* dir = opendir(path.c_str());
    vector<String> lst;
    if (dir == 0) {
        cout << "Can not open directory '" << path << "'\n";
        return -1;
    }
    //	cout << "directory '" << path << "' opened ok\n";
    struct dirent *d;
    while ((d = readdir(dir)) != 0) {
        if (d->d_type == DT_DIR && strcmp(d->d_name, ".") != 0 &&
                strcmp(d->d_name, "..") != 0) {
            String p = path + "/" + d->d_name;
            if (p.find("/.") != String::npos) {

            } else {
                if (seekdir(mylist, p,name) != 0) {
                    cerr << "Fehler in seek" << endl;
                }

            }


        } else if (d->d_type == DT_REG) {
            if (String(d->d_name).find(name) !=string::npos) {
                String fname = path + "/" + String(d->d_name);

                lst.push_back(fname);
            }

        }

    }

    closedir(dir);
    mylist.push_back(lst);
    return 0;
}

