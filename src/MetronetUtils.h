//
// Created by dawid on 16.03.17.
// Original source: TicTacToe voorbeeldproject by Serge Demeyer
//

#ifndef PROJECTFMM_METRONETUTILS_H
#define PROJECTFMM_METRONETUTILS_H


#include <iostream>


bool DirectoryExists(const std::string dirname);

bool FileExists(const std::string dirname);

bool FileIsEmpty(const std::string filename);

bool FileCompare(const std::string leftFileName, const std::string rightFileName);

#endif //PROJECTFMM_METRONETUTILS_H
