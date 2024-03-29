/* 
 * File:   FileManager.cpp
 * Author: Nils Frenking, Julian Cordes
 * 
 * Created on 28. November 2012, 23:28
 */

#include "../header.h"

using namespace std;
using namespace cv;

FileManager* FileManager::instance = NULL;

FileManager::FileManager() {
    foundFiles = StringArray();
    searchPath = "";
    searchStrings = StringSet();
}

FileManager::FileManager(const FileManager& orig) {
    foundFiles = orig.foundFiles;
    searchPath = searchPath;
    searchStrings = orig.searchStrings;
}

FileManager::~FileManager() {
}

FileManager* FileManager::getInstance() {
    if (instance == NULL) {
        instance = new FileManager();
    }
    return instance;
}

void FileManager::find(StringSet name, String dir) {

    // <editor-fold defaultstate="collapsed" desc="Parameterpruefung">
    if (dir.empty() or checkDir(dir) == -1) {
        DBG("%s ist kein gültiger Pfad", dir.c_str());
        return;
    }
    if (name.empty()) {
        DBG("Kein Suchwort angegeben");
        return;
    }// </editor-fold>

    vector < vector < String >> mylist;
    if (seekdir(mylist, dir, name) == -1) {
        cerr << "Error in seekdir" << endl;
        return;
    }


    int nfiles = 0;
    vector < vector < String >> ::iterator it;
    StringArray::iterator iter;
    StringArray erg = StringArray();
    for (it = mylist.begin(); it != mylist.end(); it++) {
        StringArray& lst = *it;

        nfiles += lst.size();


        for (iter = lst.begin(); iter != lst.end(); iter++) {
            erg.push_back((*iter));
            //cout << "File: " << (*iter) << endl;
        }
        lst.clear();

    }
    mylist.clear();

    DBG("%i Dateien gefunden", nfiles);
    searchPath = dir;
    foundFiles = erg;
    searchStrings = name;



}

int FileManager::seekdir(ArrayOfStringArrays &mylist, String path, StringSet name) {

    DIR* dir = opendir(path.c_str());
    vector<String> lst;
    vector<String> vname = StringArray(name.begin(), name.end());

    if (dir == 0) {
        cout << "Can not open directory '" << path << "'\n";
        return -1;
    }
    //	cout << "directory '" << path << "' opened ok\n";
    struct dirent *d;
    while ((d = readdir(dir)) != 0) {
        if (d->d_type == DT_DIR && strcmp(d->d_name, ".") != 0 && strcmp(d->d_name, "..") != 0) {
            String p = path + "/" + d->d_name;
            if (p.find("/.") != String::npos) {

            } else {
                if (seekdir(mylist, p, name) != 0) {
                    cerr << "Fehler in seek" << endl;
                }

            }


        } else if (d->d_type == DT_REG) {
            StringSet::iterator iter;

            for (iter = name.begin(); iter != name.end(); iter++) {
                String lower = "";
                transform(iter->begin(), iter->end(), lower.begin(), ::tolower);
                if (String(d->d_name).find((*iter)) != String::npos) {
                    String fname = path + "/" + String(d->d_name);

                    lst.push_back(fname);
                }
            }
            for (unsigned int i = 0; i < name.size(); i++) {

            }

        }

    }

    closedir(dir);

    mylist.push_back(lst);

    return 0;
}

/**
 * Pr&uuml;ft, ob die Datei, mit dem angegebenen Namen existiert.
 * @param path Der Pfad.
 * @return <code>true</code>, wenn die Datei existiert. Sonst <code>false</code>.
 */
bool FileManager::checkFile(String path) {
    FILE* fp = fopen(path.c_str(), "r");
    if (fp) {

        fclose(fp);
        return true;
    } else {

        return false;
    }
}

/**
 * Pr&uuml;ft, ob der gegebene Ordner Bilddateien enth&auml;lt.
 * @param path Der Pfrad des Ordners.
 * @return die Anzahl der gefundenen Dateien, oder <code>-1</code> bei fehler.
 */
int FileManager::checkDir(String path) {
    DIR* dir = opendir(path.c_str());
    if (dir == 0) {
        cout << "Can not open directory '" << path << "'\n";
        return -1;
    }
    //	cout << "directory '" << path << "' opened ok\n";
    struct dirent *d;

    try {
        if ((d = readdir(dir)) != 0) {
            closedir(dir);
            return 1;


        } else {
            DBG("Ordner kann nicht gelesen werden");
            return -1;
        }
    } catch (Exception& ex) {
        DBG("%s", ex.what());
        return -1;
    }


}

/**
 * Gibt die Liste der zuletzt gefundenen Dateien zur&uuml;ck.
 * @return  Die Liste der Dateinamen;
 */
StringArray FileManager::getFoundList() {
    if (foundFiles.empty()) {
        if (searchStrings.empty() or searchPath.empty()) {
            DBG("Keine Eingabe festgelegt");
            return foundFiles;
        } else {
            DBG("Suche Dateien");
            find(searchStrings, searchPath);
        }
    }
    return foundFiles;
}

/**
 * Gibt die Liste der zuletzt gesuchten Worte zur&uuml;ck.
 * @return Die Liste der Suchw&ouml;rter.
 */
StringSet FileManager::getSearchStrings() {
    return searchStrings;
}

/**
 * Gibt den letzten Suchpfad zur&uuml;ck.
 * @return den letzten Suchpfad, oder einen leeren String,
 */
String FileManager::getSearchPath() {
    return searchPath;

}

void FileManager::setSearchPath(String path) {
    if (checkDir(path)) {
        searchPath = path;
        foundFiles.clear();
    } else {
        DBG("Kein gueltiger Pfad: %s", path.c_str());
    }

}

void FileManager::setSearchStrings(StringSet strings) {
    searchStrings.insert(strings.begin(), strings.end());
}

void FileManager::addSearchString(String str) {
    searchStrings.insert(str);
}

String FileManager::getParentPath(String path) {
    if (path.empty()) {
        DBG("Pfad ist ungueltig %s", path.c_str());
    }
    String parent = path.substr(0, path.find_last_of(PATH_SEPARATOR));
    parent += PATH_SEPARATOR;
    return parent;
}

String FileManager::getFileName(String path) {
    if (path.empty()) {
        DBG("Pfad ist ungueltig %s", path.c_str());
    }
    int pos = path.find_last_of(PATH_SEPARATOR) + 1;
    int n = path.length() - pos;
    String parent = path.substr(pos, n);
    pos = parent.find_last_of(".");
    parent = parent.substr(0, pos);


    return parent;

}

void FileManager::clearAll() {
    searchStrings = StringSet();
    if (!searchStrings.empty()) {
        DBG("Suchstrings nicht leer nach neuer erstellung...");
    }
    foundFiles = StringArray();
    if (!foundFiles.empty()) {
        DBG("Gefundene Dateien nicht leer nach neuer erstellung...");
    }
    searchPath = String("");

}