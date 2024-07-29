#include "words.h"

bool checkGuess(WordCollection *words, bool guessBool);
void playGame(string fullPath);
void PrintRules();
void PrintMenu();

// Function to run a command in terminal and capture its output
string exec(const char* cmd) 
{
    array<char, 128> buffer;
    string result;
    unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) 
    {
        throw runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
    {
        result += buffer.data();
    }
    return result;
}

int main()
{
    string fullPath;
    try
    {
        string cwd = exec("pwd");
        cwd.erase(cwd.find_last_not_of("\n\r") + 1); // Remove trailing newline character
        string textFile = "wordleWords.txt";
        fullPath = cwd+"/downloads/"+textFile;
    } 
    catch (const runtime_error& e)
    {
        cerr<<"Error: "<< e.what()<<endl;
        return 1;
    }
    cout<<endl;
    cout<<"Welcome to Jaylon Coad's v2.0 of Wordle in C++!"<<endl;
    cout<<endl;
    char choice;
    srand(time(nullptr)); // generates random number based on the exact time to guarantee a different number each compilation
    PrintMenu();
    cin>>choice;
    while (choice != 'Q' && choice != 'q')
    {
        if (choice == 's' || choice == 'S')
        {
            playGame(fullPath);
            PrintMenu();
            cin>>choice;
        }
        else if (choice == 'r' || choice == 'R')
        {
            PrintRules();
            PrintMenu();
            cin>>choice;
        }
    }
    return 0;
}
void PrintMenu()
{
    cout<<endl;
    cout<<"-------Options-------"<<endl;
    cout<<endl;
    cout<<"'S' to start game\n'R' to print rules\n'Q' to quit"<<endl;
    cout<<"Choice: "<<endl;
}
void PrintRules()
{
    cout<<endl;
    cout<<"Similar to the popular New York Times game 'Wordle', this game allows a user to enter up to six guesses to guess a five-letter word.\nAfter each valid guess, meaning that the word exists in the pool of words that I curated, your guess feedback will be returned.\nIn 'Guess Data', if a letter shows up as lower case, that means that the letter is in the word but in the wrong spot, and if the letter shows up capitalized, that letter is in the correct spot.\nThe list of curated words contains no plurals and no words that have repeating letters.\nAdditionally, after each guess, letters in the 'Letter Pool' will become a period if they are not in the word at all."<<endl;
}
void playGame(string fullPath)
{
    cin.ignore();
    WordCollection *words = new WordCollection; // creating a new word collection to store all of the words from the file
    Word userGuess, correctWord;
    string userGuessString, correctWordString;
    bool guessBool = false;
    int guesses = 1, wordCount = 0;
    ifstream myIn;
    myIn.open(fullPath);
    if (!myIn)
    {
        cout<<"Error opening file, try again."<<endl;
    }
    else
    {
        while (!myIn.eof())
        {
            string stringWord; // stringWord is just a simple word
            getline(myIn, stringWord); // putting each line as a regular word
            Word *newWord = new Word(stringWord); // takes in a string word and makes it a new word object in heap
            words->AddWord(*newWord); // finally adds the word object to the word collection
            delete newWord;
            wordCount++;
        }
        myIn.close();
        words->setCorrectWord(words->getWord()[(rand() % wordCount)]);
        while (guesses < 7 && guessBool == false)
        {
            bool wordFound = false;
            cout<<"Enter your guess in all lowercase: "<<endl;
            getline(cin, userGuessString);
            Word userGuess(userGuessString);
            words->setUserGuess(userGuess);
            for (int i = 0; i < wordCount; i++)
            {
                if (words->getWord()[i].getWordString() == userGuessString)
                {
                    wordFound = true;
                }
            }
            if (wordFound == true)
            {
                guessBool = checkGuess(words, guessBool);
                cout<<"Guesses: "<<guesses<<"/6"<<endl;
                guesses+=1;
            }
            else
            {
                cout<<"Not in word list."<<endl;
            }
        }
        if (guessBool == false)
        {
            cout<<"Nice try! The word was: "<<words->getCorrectWord().getWordString()<<endl;
        }
    }
    delete words;
}
bool checkGuess(WordCollection *words, bool guessBool)
{
    char guessData[6] = "_____";
    int wrongLetter = 0, rightLetter = 0;
    for (int i = 0; i < 5; i++) // traverses the userGuess character array
    {
        for (int j = 0; j < 5; j++) // traverses the correctWord character array
        {
            if (words->getUserGuess().getWordString()[i] == words->getCorrectWord().getWordString()[j] && i == j) // if the two letters match and are in the same place
            {
                guessData[i] = toupper(words->getUserGuess().getWordString()[i]);
                rightLetter++;
            }
            else if (words->getUserGuess().getWordString()[i] == words->getCorrectWord().getWordString()[j] && i != j) // if the two letters match but are not in the same place
            {
                guessData[i] = tolower(words->getUserGuess().getWordString()[i]);
            }
            else if (words->getUserGuess().getWordString()[i] != words->getCorrectWord().getWordString()[j]) // if the letter doesn't equal the one in the correctWord list (figuring out if it exists)
            {
                wrongLetter++;
            }
        }
        if (wrongLetter == 5)
        {
            for (int k = 0; k < 26; k++)
            {
                if (words->getLetterPool()[k] == words->getUserGuess().getWordString()[i])
                {
                    words->setLetterPool('.', k);
                }
            }
        }
        if (rightLetter >= 5)
        {
            guessBool = true;
            cout<<"Correct Word!"<<endl;
        }
        wrongLetter = 0;
    }
    rightLetter = 0;
    cout<<"Letter Pool: ";
    for (int i = 0; i < 26; i++)
    {
        cout<<words->getLetterPool()[i]<<" ";
    }
    cout<<endl;
    cout<<"Guess Data: ";
    for (int i = 0; i < 5; i++)
    {
        cout<<guessData[i]<<" ";
    }
    cout<<endl;
    return guessBool;
}
