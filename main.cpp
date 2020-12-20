#include "avl.h"
#include <vector>

using namespace std;

int main(int argc, const char* argv[]){
    AVL tree;
    string temp;
    string input = argv[1];
    vector<string> inputs;

    int begin = 0;
    for(int i = 0; i < input.length(); i++){
        if (input[i] == ','){
            inputs.push_back(input.substr(begin, i-begin));
            begin = i + 2;
            i =begin;
        }
        if (i == input.length()-1){
            inputs.push_back(input.substr(begin, i-begin+1));
        }
    }

    for (int i = 0; i < inputs.size(); i++){
        string sen = inputs[i];
        vector<string> parts;
        int begin = 0;
        for(int i = 0; i < sen.length(); i++){
            if (sen[i] == ' '){
                parts.push_back(sen.substr(begin, i-begin));
                begin = i + 1;
                i =begin;
            }
            if (i == sen.length()-1){
                parts.push_back(sen.substr(begin, i-begin+1));
            }
        }
        if (parts[0] == "insert"){
            tree.insert(stoi(parts[1]), stoi(parts[2]));
        } else if (parts[0] == "search"){
            tree.search(stoi(parts[1]), stoi(parts[2]));
        }  else if (parts[0] == "approx_search"){
            tree.approxSearch(stoi(parts[1]), stoi(parts[2]));
        } else if (parts[0] == "in_order"){
            tree.inorder();
        } else if (parts[0] == "pre_order"){
            tree.preorder();
        } else if (parts[0] == "delete"){
            tree.remove(stoi(parts[1]), stoi(parts[2]));
        } else {
            tree.setk(stoi(parts[0]));
        }
    }
}