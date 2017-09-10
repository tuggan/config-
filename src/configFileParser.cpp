/*
  Copyright 2017 Dennis Vesterlund

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
*/

/*
 * File:         log.cpp
 * Created:      2013-02-07
 * Authors:      Dennis Vesterlund
 * License:      Apache License, see LICENSE
 * Description:  
 * Platforms:    Linux
 */

#include "configFileParser.h"

/*
 * Constructor
 * Takes path and filename to config file
 */
fileParser::fileParser(const char *f, const int i){
  this->fileName = f;
  this->bufferSize = i;
}

/*
 * Parses file
 * Returns:
 * 0 - if file could not be opened or no options found
 * else the it returns the number of options found
 * 
 */
int fileParser::parseFile() {
  FILE *f;
  f = fopen(this->fileName.c_str(), "r");
  if ( f == NULL )
    return 0;
  char buffer[this->bufferSize];
  unsigned long nrOfOptions = 0;
  //std::string buffer;
  while ( fgets(buffer, this->bufferSize, f) != NULL ) {
    configOption temp = this->parseLine(buffer);
    if ( temp.optionValue.length() != 0 ) {
      configOptions.push_back(temp);
      nrOfOptions++;
    }
    this->cleanCString(buffer, this->bufferSize);
  }
  
  fclose(f);
  return nrOfOptions;
}

fileParser::configOption fileParser::parseLine(char * line) {
  std::string parseline = line;
  configOption option;
  parseline = this->stripComment(parseline);
  if ( parseline.length() < 3 )
    return option;
  parseline = this->cleanStringFrom(parseline, ' ');
  size_t found= parseline.find('=');
  if ( found != std::string::npos && found > 0 ) {
    parseline = this->cleanStringFrom(parseline, '\n');
    parseline = this->cleanStringFrom(parseline, '\r');
    option.optionName = parseline.substr(0, found);
    option.optionValue = parseline.substr(found+1);
  }
  return option;
}

std::string fileParser::stripComment(std::string line) {
  size_t found = line.find('#');
  while ( found != std::string::npos ) {
    if ( line[found-1] != '\\' ) {
      line = line.substr(0, found);
      found = std::string::npos;
    } else {
      found = line.find('#', found);
    }
  }
  return line;
}

std::string fileParser::cleanStringFrom(std::string s, const char c) {
  for(int i = 0; i < s.length(); i++)
    if(s[i] == c && s[-1] != '\\') {
      s.erase(i,1);
      i--;
    } 
  return s;
}

void fileParser::cleanCString( char * string, int length ) {
  for( int i = 0; i < length; i++)
    string[i] = '\0';
}

std::vector<fileParser::configOption> fileParser::getAllOptions() {
  return this->configOptions;
}

fileParser::configOption fileParser::getOneOption() {
  fileParser::configOption temp;
  temp.optionName = this->configOptions.back().optionName;
  temp.optionValue = this->configOptions.back().optionValue;
  return temp;
}




















