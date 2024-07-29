#include "words.h"

// WORD

Word::Word()
{
    word = " ";
}
Word::Word(string word)
{
    this->word = word;
}
string Word::getWordString() const
{
    return word;
}

// WORD COLLECTION

WordCollection::WordCollection()
{
    size = 0;
    capacity = 500;
    words = new Word[capacity];
    letterPool = "abcdefghijklmnopqrstuvwxyz";
}
WordCollection::~WordCollection()
{
    delete [] words;
}
int WordCollection::getSize() const
{
    return size;
}
int WordCollection::getCap() const
{
    return capacity;
}
Word* WordCollection::getWord() const
{
    return words;
}
WordCollection& WordCollection::operator=(const WordCollection& w)
{
    size = w.getSize();
    capacity = w.getCap();
    correctWord = w.getCorrectWord();
    userGuess = w.getUserGuess();
    letterPool = w.getLetterPool();
    delete [] words;
    words = new Word[capacity];
    for (int i = 0; i < size; i++)
    {
        words[i] = w.words[i];
    }
    return *this;
}
WordCollection::WordCollection(const WordCollection& w)
{
    size = w.getSize();
    capacity = w.getCap();
    correctWord = w.getCorrectWord();
    userGuess = w.getUserGuess();
    letterPool = w.getLetterPool();
    words = new Word[capacity];
    for (int i = 0; i < size; i++)
    {
        words[i] = w.words[i];
    }
}
void WordCollection::AddWord(Word word)
{
    // adding a word to the word collection
    if (size >= capacity)
    {
        Word *tmp = new Word[capacity+500];
        for (int i = 0; i < size; i++)
        {
            tmp[i] = words[i];
        }
        capacity += 500;
    }
    words[size++] = word;
}
void WordCollection::setUserGuess(Word word)
{
    userGuess = word;
}
void WordCollection::setCorrectWord(Word word)
{
    correctWord = word;
}
Word WordCollection::getCorrectWord() const
{
    return correctWord;
}
Word WordCollection::getUserGuess() const
{
    return userGuess;
}
string WordCollection::getLetterPool() const
{
    return letterPool;
}
void WordCollection::setLetterPool(char letter, int pos)
{
    letterPool[pos] = letter;
}
