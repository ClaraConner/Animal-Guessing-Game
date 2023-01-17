/*
Author: Clara Conner
HW 5 Animal Guessing Game
Purpose: Attempts to guess what animal the user is thinking of by asking a series of y/n questions

Instructions:
    -Please only enter 'y' or 'n' unless otherwise instructed
    -The program will ask a series of questions. If you answer 'n' to one
    of the animal guesses, then additional input will be required
   

************************* EXTRA CREDIT NOTES ******************************************************
//IMPORTANT: Please ensure these files match which you intend to use
//NOTE: The output file must be blank for it to be properly saved
//Please use the exact .txt files I provide when running my code for easiest operation.
//You can view the .txt files afterwards in order to prove that I have saved my binary tree to a blank .txt file
//If you wish to run again, you have several options:
    1) Delete the two new .txt files from the folder and recopy the .txt files from my elearning submition
        This will start the binary tree over to the initial input file.
    2) Delete the old input file, rename the output file as the input file, then create a new output file.
        Please make sure the names of the documents match the ones in my code, which is highlighted below
        This will allow you to keep adding onto the previous binary trees.

*/

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

//*****************************************************************
//IMPORTANT: Please ensure these files match which you intend to use
//NOTE: The output file must be blank for it to be properly saved
ofstream outputFile;
string outputFileName = "animalGuessingOutputTree.txt";

ifstream inputFile;
string inputFileName = "animalGuessingInputTree.txt";
//*****************************************************************

void line() {
    cout << "=======================================================================================\n" << endl;
}

struct animalNode {
    string question; 
    string guess; 
    animalNode* yesAnswer; 
    animalNode* noAnswer; 
};
//the very first node of the tree
animalNode* root = new animalNode();

void deleteBinaryTree(animalNode*& node) {
    // Base case: empty tree
    if (node == nullptr) {
        return;
    }

    // delete left and right subtree first (Postorder)
    deleteBinaryTree(node->yesAnswer);
    deleteBinaryTree(node->noAnswer);

    // delete the current node after deleting its left and right subtree
    delete node;

    // set root as null before returning
    node = nullptr;
}

//saves binary tree onto the output file
void saveBinaryTree(animalNode*& node) {
    if (node) {
        outputFile << "NEW NODE" << endl;
        outputFile << node->question << endl;
        outputFile << node->guess << endl;
        saveBinaryTree(node->yesAnswer);
        saveBinaryTree(node->noAnswer);
    }
}

//creates binary tree from the input file
void createBinaryTree(animalNode*& node) {

    string line, question, guess;
    getline(inputFile, line);
    getline(inputFile, question);
    getline(inputFile, guess);

    animalNode* newNode = new animalNode;
    animalNode* newNode2 = new animalNode;

    if (guess == "") {
        node->question = question;
        node->guess = "";
        node->yesAnswer = newNode;
        createBinaryTree(newNode);
        node->noAnswer = newNode2;
        createBinaryTree(newNode2);
    }
    else {
        node->question = "";
        node->guess = guess;
        node->yesAnswer = nullptr;
        node->noAnswer = nullptr;
    }
}

//function to print the tree
void printBinaryTree(animalNode*& node) {

    if (node) {
        cout << "NEW NODE" << endl;
        cout << "Q: " << node->question << endl;
        cout << "A: " << node->guess << endl;
        printBinaryTree(node->yesAnswer);
        printBinaryTree(node->noAnswer);
    }
}

//creates a node
void createNode(animalNode*& node, string answer, string oldGuess, string animal) {

    //creates a node for the new guess
    animalNode* newGuessNode = nullptr;
    newGuessNode = new animalNode;
    newGuessNode->guess = animal;
    newGuessNode->question = "";
    newGuessNode->yesAnswer = nullptr;
    newGuessNode->noAnswer = nullptr;

    //creates a node for the old guess
    animalNode* oldGuessNode = nullptr;
    oldGuessNode = new animalNode;
    oldGuessNode->guess = oldGuess;
    oldGuessNode->question = "";
    oldGuessNode->yesAnswer = nullptr;
    oldGuessNode->noAnswer = nullptr;

    //inserts nodes where appropriate
    if (answer == "yes") {
        node->yesAnswer = newGuessNode;
        node->noAnswer = oldGuessNode;
    }
    else {
        node->yesAnswer = oldGuessNode;
        node->noAnswer = newGuessNode;
    }
}

//creates variables with new node information
void addQuestion(animalNode*& node) {
    cout << "\nOh dang, I got the wrong answer :(\nWhat animal were you thinking of?" << endl;
    string animal;
    cin >> animal;
    cout << "Oh, I see. What is a y/n question to differentiate between a(n) " << animal << " and a " << node->guess << "?" << endl;
    string question;
    cin.ignore();
    getline(cin, question);
    cout << "And would a 'yes' or a 'no' get you a(n) " << animal << "?" << endl;
    string answer;
    cin >> answer;
    string oldGuess = node->guess;
    node->guess = "";
    node->question = question;
    createNode(node, answer, oldGuess, animal);
}

//reads the nodes and interacts with the user by asking questions
void askQuestion(animalNode*& node) {

    if (node->yesAnswer == nullptr && node->noAnswer == nullptr) {     
        //if the children nodes are nullptrs, then the node is a guess node
        cout << "\nIs your animal a " << node->guess << "? y/n" << endl;
        char ans;
        cin >> ans;
        if (ans == 'y') {
            cout << "Yay! I got it right!\nPlay again? y/n" << endl;
            cin >> ans;
            if (ans == 'y') {
                line();
                askQuestion(root);
            }
        }
        else {
            //if the program is wrong then the program adds the guess
            addQuestion(node);                
            cout << "\nPlay again? y/n" << endl;
            cin >> ans;
            if (ans == 'y') {
                line();
                askQuestion(root);
            }
        }
    }
    else {
        //if the node has children then it is a question node
        cout << node->question << " y/n" << endl;       
        char ans;
        cin >> ans;
        if (ans == 'y') {
            askQuestion(node->yesAnswer);
        }
        else {
            askQuestion(node->noAnswer);
        }
    }
}

int main() {
    //beginning dialogue
    line();
    cout << "Welcome to the animal guessing game!" << endl;
    cout << "Simply think of an animal and the game will try to guess it." << endl;
    cout << "Please answer each question as \'y\' or \'n\' unless otherwise stated." << endl << endl;
    line();

    inputFile.open(inputFileName);
    if (!inputFile.is_open()) {
        cout << "File was not opened" << endl;
        cout << "Press any key to quit the program. . ." << endl;
        cin.ignore();
        return 0;
    }

    createBinaryTree(root);
    askQuestion(root);
    line();

    cout << "Would you like to print the binary tree? y/n" << endl;
    char answer;
    cin >> answer;
    if(answer == 'y')
        printBinaryTree(root);

    line();
    
    cout << "Would you like to save the binary tree? y/n" << endl;
    cout << "Please make sure that the files you have entered are correct." << endl;
    cin >> answer;
    if (answer == 'y') {
        outputFile.open(outputFileName);
        saveBinaryTree(root);
    }
}
