
#include <vector>
#include <exception>

#include <fstream>
#include <iostream>
#include <string>

#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

using namespace std;

vector<string> listFiles(string dir);

vector<string> listFiles(string dir)
{
  vector<string> files;
  string filepath;
  DIR *dp;
  struct dirent *dirp;

  try
  {
    dp = opendir(dir.c_str());
  }catch(const char* msg)
  {
    cerr << msg << endl;
  }
 

  while ((dirp = readdir( dp )))
  {

    filepath = dir + "/" + dirp->d_name;

    files.push_back(filepath);

    // If the file is a directory (or is in some way invalid) we'll skip it 
    if (stat( filepath.c_str(), &filestat ))
      continue;
    
    if (S_ISDIR( filestat.st_mode ))
      continue;


    // Endeavor to read a single number from the file and display it
    /*fin.open( filepath.c_str() );
    
    if (fin >> num)
      cout << filepath << ": " << num << endl;
    
    fin.close();*/
    
  }

  closedir( dp );

  return files;

}
