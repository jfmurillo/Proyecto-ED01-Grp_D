#include "DecisionTree.h"

DecisionTree::DecisionTree(){
  root = new DecisionNode();
}

DecisionTree::~DecisionTree(){
  delete root;
}

void DecisionTree::addCombo(const std::string &combo, const std::string &action){
  DecisionNode *currentNode = root;
  for (char key : combo)
  {

    if (currentNode->children.find(key) == currentNode->children.end()){
      currentNode->children[key] = new DecisionNode(key);
    }
    currentNode = currentNode->children[key];
  }

  currentNode->action = action;
}

std::string DecisionTree::findCombo(const std::string &sequence) const{
  DecisionNode *currentNode = root;
  for (char key : sequence){
    if (currentNode->children.find(key) == currentNode->children.end()){
      return "";
    }
    currentNode = currentNode->children[key];
  }
  return currentNode->action;
}
