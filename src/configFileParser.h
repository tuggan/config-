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
 * File:         log.h
 * Created:      2013-02-07
 * Authors:      Dennis Vesterlund
 * License:      Apache License, see LICENSE
 * Description:  
 * Platforms:    Linux
 */

#include <cstdio>
#include <string>
#include <vector>

class fileParser {
 public:
  struct configOption {
    std::string optionName;
    std::string optionValue;
  };
  fileParser(const char * f, int i = 255);
  int parseFile();
  std::vector<configOption> getAllOptions();
  configOption getOneOption();
 private:
  std::vector<configOption> configOptions;
  void cleanCString( char * string, int length );
  configOption parseLine(char * line);
  std::string fileName;
  int bufferSize;
  std::string stripComment(std::string line);
  std::string cleanStringFrom(std::string s, const char c);
};



















