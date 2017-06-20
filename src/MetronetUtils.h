//
// Created by dawid on 16.03.17.
// Original source: TicTacToe voorbeeldproject by Serge Demeyer
//

#ifndef PROJECTFMM_METRONETUTILS_H
#define PROJECTFMM_METRONETUTILS_H


#include <iostream>

const unsigned int TESTS_LEGAL = 5;
const unsigned int TESTS_ILLEGAL = 7;
const unsigned int TESTS_INCORRECT = 43;
const unsigned int TESTS_SYNTAX = 3;

bool DirectoryExists(const std::string dirname);

bool FileExists(const std::string dirname);

bool FileIsEmpty(const std::string filename);

bool FileCompare(const std::string leftFileName, const std::string rightFileName);

#endif //PROJECTFMM_METRONETUTILS_H
