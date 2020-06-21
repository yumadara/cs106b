#pragma once
#include "set.h"
#include "lexicon.h"

void predict(std::string digits, Set<std::string>& suggestions, Lexicon& lex, std::string sofar = "");
