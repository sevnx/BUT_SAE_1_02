/**
 * @file testDictionary.cpp
 * @brief SAE 1.02
 * @author CZYKINOWSKI Seweryn / LENCLOS Corentin
 * @version 2 24/11/2022
 * Test of dictionary component
 */
#include "Dictionary.h"
#include <cassert>

int main(){
    Dictionary testDictionary{};
    initDictionary(testDictionary);
    assert(inDictionaryExist(testDictionary,"TEST"));
    assert(!inDictionaryExist(testDictionary,"JESUISFAUX"));
    assert(inDictionaryExist(testDictionary,"AA"));
    assert(firstWordMatch("tes","test")==0);
    assert(firstWordMatch("oui","non")!=0);
    assert(wordStartWithExist(testDictionary,"A"));
    assert(!wordStartWithExist(testDictionary,"HAHAHA"));
    char* testWord = new char[MAX_LENGTH];
    findWord(testDictionary,"A",testWord);
    assert(inDictionaryExist(testDictionary,testWord));
    testWord=NULL;
    char* testWord2 =new char[MAX_LENGTH];
    findWord(testDictionary,"AAAAAAAAAA",testWord2);
    assert(strcmp(testWord2,"!(j'ai gagne)")==0);
    delete [] testWord2;
    testWord2=NULL;
    assert(isUnreachable(testDictionary,"ABAISSABLE"));
    assert(isUnreachable(testDictionary,"IQALUMMIUQS"));
    assert(isUnreachable(testDictionary,"IRAKIENNES"));
    assert(isUnreachable(testDictionary,"IRISERAIENT"));
    assert(!isUnreachable(testDictionary,"QWERTY"));
    assert(!isUnreachable(testDictionary,"AA"));
    assert(!isUnreachable(testDictionary,"AAS"));
    assert(getLetterEfficiency(testDictionary,"ABACOST",'S',2)==finishesWord);
    assert(getLetterEfficiency(testDictionary,"ABACOST",'X',2)==noWords);
    assert(getLetterEfficiency(testDictionary,"",'A',2)==unsecureWordsExist);
    assert(getLetterEfficiency(testDictionary,"QWE",'R',2)==unsecureWordsOnly);
    assert(getLetterEfficiency(testDictionary,"QWER",'T',2)==secureWordsOnly);
    destroyDictionary(testDictionary);
}