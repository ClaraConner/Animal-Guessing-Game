/*
Author: Clara Conner
HW 5 Animal Guessing Game
Purpose: Attempts to guess what animal the user is thinking of by asking a series of y/n questions

Changelog:
    - Create start dialogue
    - Create animal structure
    - Add first question and answer
    - Create function to add questions
    - Complete dialogue
    - Code now reads input from a file
    - Can save binary tree to a new file

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

struct animalNode {
    string question;
    string guess;
    animalNode* yesAnswer;
    animalNode* noAnswer;
};
animalNode* root = new animalNode();


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

void deleteBinaryTree(animalNode*& root)
{
    // Base case: empty tree
    if (root == nullptr) {
        return;
    }

    // delete left and right subtree first (Postorder)
    deleteBinaryTree(root->yesAnswer);
    deleteBinaryTree(root->noAnswer);

    // delete the current node after deleting its left and right subtree
    delete root;

    // set root as null before returning
    root = nullptr;
}

//saves binary tree onto the output file
void saveBinaryTree(animalNode*& root) {

    if (root) {

        outputFile << "NEW NODE" << endl;
        outputFile << root->question << endl;
        outputFile << root->guess << endl;
        saveBinaryTree(root->yesAnswer);
        saveBinaryTree(root->noAnswer);

    }
}

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

//function to print the tree, useful in debugging
void printBinaryTree(animalNode*& root) {

    if (root) {

        cout << "NEW NODE" << endl;
        cout << "Q: " << root->question << endl;
        cout << "A: " << root->guess << endl;
        printBinaryTree(root->yesAnswer);
        printBinaryTree(root->noAnswer);

    }

}

//creates a node
void createNode(animalNode*& node, string answer, string oldGuess, string animal) {

    //creates a node for the new guess
    animalNode* newNode = nullptr;
    newNode = new animalNode;
    newNode->guess = animal;
    newNode->question = "";
    newNode->yesAnswer = nullptr;
    newNode->noAnswer = nullptr;

    //creates a node for the old guess
    animalNode* newNodeTwo = nullptr;
    newNodeTwo = new animalNode;
    newNodeTwo->guess = oldGuess;
    newNodeTwo->question = "";
    newNodeTwo->yesAnswer = nullptr;
    newNodeTwo->noAnswer = nullptr;

    //inserts nodes where appropriate
    if (answer == "yes") {
        node->yesAnswer = newNode;
        node->noAnswer = newNodeTwo;
    }
    else {
        node->yesAnswer = newNodeTwo;
        node->noAnswer = newNode;
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

    if (node->yesAnswer == nullptr && node->noAnswer == nullptr) {      //if the children nodes are nullptrs, then the node is a guess node
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
            addQuestion(node);                      //if the program is wrong then the program adds the guess
            cout << "\nPlay again? y/n" << endl;
            cin >> ans;
            if (ans == 'y') {
                line();
                askQuestion(root);
            }
        }
    }
    else {
        cout << node->question << " y/n" << endl;       //if the node has children then it is a question node
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
    if (!inputFile.is_open())
        cout << "File was not opened" << endl;
    createBinaryTree(root);

    askQuestion(root);

    line();

    cout << "Would you like to print the binary tree? y/n" << endl;
    char answer;
    cin >> answer;
    if (answer == 'y')
        printBinaryTree(root);          //prints binary tree from left children to right children, used in debugging

    line();

    cout << "Would you like to save the binary tree? y/n" << endl;
    cout << "Please make sure that the files you have entered are correct." << endl;
    cin >> answer;
    if (answer == 'y') {
        outputFile.open(outputFileName);
        saveBinaryTree(root);
    }


    //deleteBinaryTree(root);         //Used to delete the binary tree, comment out when trying to expand
}