/* 
 * File:   FileManager.h
 * Author: Nils Frenking, Julian Cordes
 *
 * Created on 28. November 2012, 23:28
 */

#ifndef FILEMANAGER_H
#define	FILEMANAGER_H

#include "../header.h"
using namespace std;

class FileManager {
public:

    virtual ~FileManager();



    static FileManager* getInstance();

    /**
     * Sucht rekursiv nach Dateien, in denen 'name' im Namen vorkommt.
     * @param name Die Suchworte.
     * @param dir der Ordner der durchsucht werden soll.
     */
    void find(CvStringSet name, String dir);
    /**
     * Pr&uuml;ft, ob die Datei, mit dem angegebenen Namen existiert.
     * @param path Der Pfad.
     * @return <code>true</code>, wenn die Datei existiert. Sonst <code>false</code>.
     */
    bool checkFile(String path);
    /**
     * Pr&uuml;ft, ob der gegebene Ordner Bilddateien enth&auml;lt.
     * @param path Der Pfrad des Ordners.
     * @return die Anzahl der gefundenen Dateien, oder <code>-1</code> bei fehler.
     */
    int checkDir(String path);

    /**
     * Gibt die Liste der zuletzt gefundenen Dateien zur&uuml;ck.
     * @return  Die Liste der Dateinamen;
     */
    CvStringArray getFoundList();
    /**
     * Gibt die Liste der zuletzt gesuchten Worte zur&uuml;ck.
     * @return Die Liste der Suchw&ouml;rter.
     */
    CvStringSet getSearchStrings();
    /**
     * Gibt den letzten Suchpfad zur&uuml;ck.
     * @return den letzten Suchpfad, oder einen leeren String,
     */
    String getSearchPath();
    
    void setSearchPath(String path);
    
    void setSearchStrings(CvStringSet strings);
    
    void addSearchString(String str);
    
    void clearAll();
    
    static String getParentPath(String path);
    
    static String getFileName(String path);
        
    
private:
    CvStringArray foundFiles;
    CvStringSet searchStrings;
    String searchPath;

    FileManager();
    FileManager(const FileManager& orig);
    static FileManager *instance;
    int seekdir(CvArrayOfStringArrays &mylist, String path, CvStringSet name);

};

#endif	/* FILEMANAGER_H */

