//============================================================================
// Name        : TreeTraversal.cpp
// Author      : Manish Sharma
// Version     :
// Copyright   : Your copyright notice
// Description : Different Tree Traversals Without Recursions
//============================================================================

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
using namespace std;

// Non owning node design, actual RAII nodes are held in a separate constructor
class node
{
    public:
		node(int32_t dt):
			val(dt),
			left(nullptr),
			right(nullptr){}

		int32_t val;
		node* left;
		node* right;
};

void constructTree(node** root, std::vector<node>& dataOwningArray){
	dataOwningArray.emplace_back(node(10));
	*root = &dataOwningArray[0];

	dataOwningArray.emplace_back(node(23));
	dataOwningArray.emplace_back(node(29));
	(*root)->left = &dataOwningArray[1];
	(*root)->right = &dataOwningArray[2];

	dataOwningArray.emplace_back(node(33));
	dataOwningArray.emplace_back(node(69));
	dataOwningArray[1].left = &dataOwningArray[3];
	dataOwningArray[1].right = &dataOwningArray[4];

	dataOwningArray.emplace_back(node(-100));
	dataOwningArray.emplace_back(node(-7));
	dataOwningArray[2].left = &dataOwningArray[5];
	dataOwningArray[2].right = &dataOwningArray[6];

	dataOwningArray.emplace_back(node(7));
	dataOwningArray.emplace_back(node(11));
	dataOwningArray[3].left = &dataOwningArray[7];
	dataOwningArray[7].right = &dataOwningArray[8];

	dataOwningArray.emplace_back(node(0));
	dataOwningArray[5].left = &dataOwningArray[9];

}

void preOrder(node* root){
    if(root != nullptr) {
        std::cout<<root->val<<", ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

void postOrder(node* root){
    if(root != nullptr) {
        postOrder(root->left);
        postOrder(root->right);
        std::cout<<root->val<<", ";
    }
}

void inOrder(node* root){
    if(root != nullptr) {
        inOrder(root->left);
        std::cout<<root->val<<", ";
        inOrder(root->right);
    }
}

int main() {
	std::vector<node> dataOwningArray;
	dataOwningArray.reserve(100);
	node* root = nullptr;
	constructTree(&root, dataOwningArray);

	std::stack<node*> dataStack;
	node* curr = root;

	// Inorder Traversal
	std::cout<<"InOrder Traversal : ";
	while(!dataStack.empty() || curr != nullptr){
		if(curr != nullptr){
			dataStack.push(curr);
			curr = curr->left;
		}else{
			auto poppedElement = std::move(dataStack.top());
			dataStack.pop();
			std::cout<<poppedElement->val<<", ";
			curr = poppedElement->right;
		}
	}std::cout<<"\n";

	// PreOrder Traversal, this is very similar to DFS
	dataStack=std::stack<node*>{};
	dataStack.push(root);
	std::cout<<"PreOrder Traversal(DFS) : ";
	while(!dataStack.empty()){
		auto poppedElement = std::move(dataStack.top());
		dataStack.pop();
		std::cout<<poppedElement->val<<", ";

		if(poppedElement->right !=nullptr){
			dataStack.push(poppedElement->right);
		}
		if(poppedElement->left !=nullptr){
			dataStack.push(poppedElement->left);
		}
	}std::cout<<"\n";


	// PostOrder Traversal
	dataStack=std::stack<node*>{};
	std::vector<node*> outputReverseStack{};
	dataStack.push(root);
	std::cout<<"PostOrder Traversal : ";
	while(!dataStack.empty()){
		//pop top element and insert in outputStack
		outputReverseStack.emplace_back(std::move(dataStack.top()));
		dataStack.pop();

		if(outputReverseStack.back()->left !=nullptr){
			dataStack.push(outputReverseStack.back()->left);
		}
		if(outputReverseStack.back()->right !=nullptr){
			dataStack.push(outputReverseStack.back()->right);
		}
	}
	std::for_each(outputReverseStack.rbegin(),outputReverseStack.rend(),[](node* input){std::cout<<input->val<<", ";});
	std::cout<<"\n";

	// LevelOrder Traversal or BFS
	// PreOrder Traversal, this is very similar to DFS
	std::queue<node*> dataQueue{};
	dataQueue.push(root);
	std::cout<<"LevelOrder Traversal(BFS) : ";
	while(!dataQueue.empty()){
		auto poppedElement = std::move(dataQueue.front());
		dataQueue.pop();
		std::cout<<poppedElement->val<<", ";


		if(poppedElement->left !=nullptr){
			dataQueue.push(poppedElement->left);
		}
		if(poppedElement->right !=nullptr){
			dataQueue.push(poppedElement->right);
		}

	}std::cout<<"\n";

    std::cout<<"Recursive Implementation Outputs : \n";
    std::cout<<"Recursive PreOrder : ";
    preOrder(root);
    std::cout<<"\nRecursive PostOrder : ";
    postOrder(root);
    std::cout<<"\nRecursive InOrder : ";
    inOrder(root);
	return 0;
}
