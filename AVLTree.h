#include <string>
#include <vector>
#include <exception>
#include <iterator>
#include <utility>
#include <memory>

#ifndef AVLTREE_H
#define AVLTREE_H


template<class T>
class AVLTree
{
public:
	AVLTree();
	~AVLTree();
	void insert( T element)
	{
		insert(element, Root);
	}
	void remove(T element)
	{
		remove( element, Root);
	}
	bool find(T element)
	{
		return find(  element, Root);
	}
	std::vector<T> preOrderWalk()
	{
		return preOrderWalk(Root);
	}
	std::vector<T> inOrderWalk()
	{
		return inOrderWalk( Root);
	}
	std::vector<T> postOrderWalk()
	{
		return postOrderWalk( Root);
	}
	size_t getTreeHeight()	
	{
		return getTreeHeight( Root);
	}
	T getMin() 
	{
		return getMin(Root);
	}
	T getMax() 
	{
		return getMax(Root);
	}

private:
	struct AVLnode
	{
		T element;
		AVLnode* left;
		AVLnode* right;
		int height;

		AVLnode(const T& item, AVLnode *lt, AVLnode *rt, int h=0)
			: element{item},left{lt},right{rt}, height{h} { }
		AVLnode( T&& item, AVLnode* lt, AVLnode* rt, int h = 0)
			: element{ std::move(item)}, left{ lt }, right{ rt }, height{ h } { }

	};
	AVLnode* Root;
	

	void insert( T& element, AVLnode* Root);
	bool find( T& element, AVLnode* Root);
	void remove( T& element, AVLnode* Root);
	void Balance(AVLnode* Root);
	void Singlerotateleft(AVLnode* &Root);
	void Dubblerotateleft(AVLnode* &Root);
	void Singlerotateright(AVLnode* &Root);
	size_t getTreeHeight(AVLnode* Root);
	T& getMin(AVLnode* Root);
	const T& getMax(AVLnode* Root);
	std::vector<T> preOrderWalk(AVLnode* Root);
	std::vector<T> inOrderWalk(AVLnode* Root);
	std::vector<T> postOrderWalk(AVLnode* Root);
	size_t get_height(AVLnode* Root, int counter);
	T Max(T  A, T B);
};
static const int allowed_imbalance = 1;


template <typename T>
AVLTree<T>::AVLTree()
{
	/*Root = nullptr;*/

}
template <typename T>
AVLTree<T>::~AVLTree()
{

}


template<typename T>
T AVLTree<T>::Max(T A, T B)
{
	if (A < B)
	{
		return B;
	}
	return A;
}

template<typename T>
std::vector<T> AVLTree<T>::postOrderWalk(AVLnode* t)
{
	std::vector<T> PostorderVector;
	if (t == nullptr)
	{
		return PostorderVector;
	}
	if (t->left != nullptr)
	{
		postOrderWalk(t->left);
	}
	if (t->right != nullptr)
	{
		postOrderWalk(t->right);
	}
	PostorderVector.push_back(t->element);
	return PostorderVector;
}

template<typename T>
std::vector<T> AVLTree<T>::inOrderWalk(AVLnode* t)
{
	std::vector <T> InorderVector;
	if (t == nullptr)
	{
		return InorderVector;
	}

	if (t->left != nullptr)
	{
		inOrderWalk(t->left);
	}

	InorderVector.push_back(t->element);

	if (t->right != nullptr)
	{
		inOrderWalk(t->right);
	}
	return InorderVector;
}

template<typename T>
std::vector<T> AVLTree<T>::preOrderWalk(AVLnode* t)
{
	std::vector<T> PreorderVector;
	if (t == nullptr)
	{
		return PreorderVector;
	}
	PreorderVector.push_back(t->element);
	if (t->left != nullptr)
	{
		preOrderWalk(t->left);
	}
	if (t->right != nullptr)
	{
		preOrderWalk(t->right);
	}
	return PreorderVector;
}


template<typename T>
const T& AVLTree<T>::getMax(AVLnode* t) 
{
	try
	{
		if (t == nullptr)
		{
			throw std::runtime_error("");
		}
		while (t->right != nullptr)
		{
			t = t->right;
		}
		return t->element;
	}
	catch (const std::exception& z)
	{
		z.what();
	}
}


template<typename T>
 T& AVLTree<T>::getMin(AVLnode* t) 
{
	try
	{
		if (t == nullptr)
		{
			throw std::runtime_error("Exception accured");
		}	
		if (t->left == nullptr)
		{
			return t->element;
		}
		return getMin(t->left);
	}
	catch (const std::exception& z)
	{
		z.what();
	}
}

template<typename T>
size_t AVLTree<T>::get_height(AVLnode* t, int counter)
{
	if (t == nullptr)
	{
		return (counter +1);
	}
	counter++;
	int temporary1=0, Temporary2=0;
	counter += Max(get_height(t->left, temporary1), get_height(t->right, Temporary2));
	return (counter+1);

}


template<typename T>
size_t AVLTree<T>::getTreeHeight(AVLnode* t)
{
	int counter =-1;
	if (t == nullptr)
	{
		return static_cast<size_t>(counter);
	}
	size_t h = static_cast<size_t>(get_height(t, counter));
	return h;
}

template<typename T>
void AVLTree<T>::Singlerotateleft(AVLnode* &t)
{
	AVLnode* lefty = t->right;
	t->right = lefty->left;
	lefty->left = t;
	t->height = Max(getTreeHeight(t->right), getTreeHeight(t->left)) + 1;
	lefty->height = Max(getTreeHeight(lefty->right),t->height) + 1;
	t = lefty;
}

template<typename T>
void AVLTree<T>::Singlerotateright(AVLnode* &t)
{
	AVLnode* righty = t->left;
	t->left = righty->right;
	righty->right = t;
	t ->height = Max(getTreeHeight(t->left), getTreeHeight(t->right)) + 1;
	righty->height = Max(getTreeHeight(righty->left), t->height) + 1;
	t = righty;
}


template<typename T>
void AVLTree<T>::Dubblerotateleft(AVLnode* &t)
{
	Singlerotateright(t->left);
	Singlerotateleft(t);
}


template<typename T>
void AVLTree<T>::Balance(AVLnode* t)
{
	if (t == nullptr)
	{
		;
	}
	else if (getTreeHeight(t->left) - getTreeHeight(t->right) > allowed_imbalance)
	{
		if (getTreeHeight(t->left->left) >= getTreeHeight(t->left->right))
		{
			Singlerotateleft(t);
		}
		else
		{
			Dubblerotateleft(t);
		}
	}
	else
	{
		if (getTreeHeight(t->right) - getTreeHeight(t->left) > allowed_imbalance)
		{
			if (getTreeHeight(t->right->right) >= getTreeHeight(t->right->left))
			{
				Singlerotateright(t);
			}
			else
			{
				Dubblerotateleft(t);
			}
		}
	}
	t->height = Max(getTreeHeight(t->left), getTreeHeight(t->right)) + 1;
}


template<typename T>
void AVLTree<T>::insert( T& element, AVLnode* t)
{
	bool exist = find(element, t);
	if (exist == false)
	{
		if (t == nullptr)	
		{
			t = new AVLnode{ element, nullptr, nullptr };
		}
		else if (element < t->element)	
		{
			insert(element, t->left);	
		}
		else if (element > t->element)	
		{
			insert(element, t->right);	
		}
		Balance(t);
	}
	
}


template<typename T>
bool AVLTree<T>::find( T& element, AVLnode * t)
{
	if (t == nullptr)	//Om det inte längre finns något att iterera genom eller om trädet är tomt
	{
		return false;	//Nod finns inte
	}
	else if ( element < t->element)	//om element är mindre än roten
	{
		return find(element, t->left);	//letar genom vänster subträdet rekursivt
	}
	else if ( element > t->element)	//om elementet är större än roten
	{
		return find(element, t->right);	//letar genom höger subträd rekursivt
	}
	else	//om roten är det som letas efter
	{
		return true; //node hittad
	}
}


template<typename T>
void AVLTree<T>::remove( T &element, AVLnode* t)
{
	if (t == nullptr)
	{
		return;	//Om elementet som ska tas bort inte hittas
	}
	if(element < t->element)	//Om element är mindre än roten
	{
		remove(element, t->left);	//Kallar remove rekursivt för vänster subträd
	}
	else if(element > t->element)	//om element är större än roten
	{
		remove(element, t->right);	//kallar funktione rekursivt för höger subträd 
	}
	else if(t->left !=nullptr && t->right != nullptr)	//Om noden har två barn
	{
		t->element = getMin(t->right);	//ta fram det minsta elementet i högersubträd
		remove(t->element, t->right);	//kalla funktionen rekursivt med nytt element
	}
	else	
	{
		AVLnode* old_Node = t;	//Skapar ett objekt för  att hålla root
		t = (t->left != nullptr) ? t->left : t->right;	//om Root->left int är nullptr kommer Root = Root->left, annars Root->right 
		delete old_Node;	//tar bort vårt objekt från minnet
	}
	Balance(t);
}














//std::string ToGraphviz() // Member function of the AVLTree class
//{
//	std::string toReturn = "";
//	if(root) // root is a pointer to the root node of the tree
//	{
//		std::string listOfNodes;
//		std::string listOfConnections = std::string("\t\"Root\" -> ") + std::to_string(0) + std::string(";\n");
//		toReturn += std::string("digraph {\n");
//		size_t id = 0;
//		ToGraphvizHelper(listOfNodes, listOfConnections, root, id);
//		toReturn += listOfNodes;
//		toReturn += listOfConnections;
//		toReturn += std::string("}");
//	}
//	return std::move(toReturn);
//}
//
//void ToGraphvizHelper(std::string& listOfNodes, std::string& listOfConnections, Node* toWorkWith, size_t& uniqueID) // Member function of the AVLTree class
//{
//	size_t myID = uniqueID;
//	listOfNodes += std::string("\t") + std::to_string(myID) + std::string(" [label=\"") + std::to_string(toWorkWith->element) + std::string("\"];\n");
//	if(toWorkWith->leftChild)
//	{
//		listOfConnections += std::string("\t") + std::to_string(myID) + std::string(" -> ") + std::to_string(uniqueID + 1) + std::string(" [color=blue];\n");
//		ToGraphvizHelper(listOfNodes, listOfConnections, toWorkWith->leftChild, ++uniqueID);
//	}
//	else
//	{
//		listOfNodes += std::string("\t") + std::to_string(++uniqueID) + std::string(" [label=") + std::string("nill, style = invis];\n");
//		listOfConnections += std::string("\t") + std::to_string(myID) + std::string(" -> ") + std::to_string(uniqueID) + std::string(" [ style = invis];\n");
//	}
//			
//	if(toWorkWith->rightChild)
//	{
//		listOfConnections += std::string("\t") + std::to_string(myID) + std::string(" -> ") + std::to_string(uniqueID + 1) + std::string(" [color=red];\n");
//		ToGraphvizHelper(listOfNodes, listOfConnections, toWorkWith->rightChild, ++uniqueID);
//	}
//	else
//	{
//		listOfNodes += std::string("\t") + std::to_string(++uniqueID) + std::string(" [label=") + std::string("nill, style = invis];\n");
//		listOfConnections += std::string("\t") + std::to_string(myID) + std::string(" -> ") + std::to_string(uniqueID) + std::string(" [ style = invis];\n");
//	}
//}
#endif // !AVLTREE_H