#include<fstream>
#include<iostream>
#include<vector>


struct Tree
{
	struct Node
	{
		int _key;
		Node * _rNode;
		Node * _lNode;
		Node* _parent;
		
		Node():_key(0),_rNode(nullptr),_lNode(nullptr),_parent(nullptr){}
		Node(int key):_key(key),_rNode(nullptr),_lNode(nullptr),_parent(nullptr){}
	};

	Node *_root;

	Tree():_root(nullptr){};
    /*
    
    THERE IS A MISTAKE IN DESTRUCTOR: RTE

    ~Tree()
    {  
        DestroyTree(_root);
    }
*/
	Node* InsertNode(int key)
	{
		
		Node* parentNode=new Node;
		if(!_root)
		{
			_root=new Node(key);
			return _root;
		}
		else
		{

			Node* insertNode(_root);
			
			while(insertNode!=nullptr)
			{
				parentNode=insertNode;
				if(key<insertNode->_key)
					insertNode=insertNode->_lNode;
				else if(key>insertNode->_key)
					insertNode=insertNode->_rNode;
				else 
					return nullptr;
			}
		
		
			if(key<parentNode->_key)
			{
				parentNode->_lNode=new Node(key);
				parentNode->_lNode->_parent=parentNode;
				return parentNode->_lNode;
			}
			else
			{
				parentNode->_rNode=new Node(key);
				parentNode->_rNode->_parent=parentNode;
				return parentNode->_rNode;
			}
		}
		
	}
/*	
	void DestroyTree(Node* curr)
	{
		if(curr!=nullptr)
		{
			DestroyTree(curr->_lNode);
			DestroyTree(curr->_rNode);
		}
		else
			return;
		
		if(curr!=_root)
		{
			if(curr->_parent->_lNode==curr)
				curr->_parent->_lNode=nullptr;
			else
				curr->_parent->_rNode=nullptr;
		}
		delete curr;	
	}
*/
	void DestroyKey(int key)
	{
		Node* nodeKey=SearchKey(key);
		if(!nodeKey)
			return;
		if(!nodeKey->_lNode&&!nodeKey->_rNode)
		{
			if(nodeKey==_root)
			{
				delete _root;
				_root=nullptr;
				return;
			}
			else{
				if(nodeKey->_parent->_lNode==nodeKey)
					nodeKey->_parent->_lNode=nullptr;
				else
					nodeKey->_parent->_rNode=nullptr;
			}
			delete nodeKey;
			return;
		}
		if(!nodeKey->_lNode)
		{
			if(nodeKey==_root)
			{
				Node* newRoot=_root->_rNode;
				delete _root;
				_root=newRoot;
				_root->_parent=nullptr;
				return;
			}
			if(nodeKey->_parent->_lNode==nodeKey)
				nodeKey->_parent->_lNode=nodeKey->_rNode;
			else
				nodeKey->_parent->_rNode=nodeKey->_rNode;
			delete nodeKey;
			return;
		}	
		if(!nodeKey->_rNode)
		{
			if(nodeKey==_root)
			{
				Node* newRoot=_root->_lNode;
				delete _root;
				_root=newRoot;
				_root->_parent=nullptr;
				return;
			}
			if(nodeKey->_parent->_lNode==nodeKey)
				nodeKey->_parent->_lNode=nodeKey->_lNode;
			else
				nodeKey->_parent->_rNode=nodeKey->_lNode;
			delete nodeKey;
			return;
		}
	
		Node* minNode=nodeKey->_rNode;
		while(minNode->_lNode)
			minNode=minNode->_lNode;	
		
		int tmp(minNode->_key);
		DestroyKey(minNode->_key);
		nodeKey->_key=tmp;
	
	}

	void PreOrderL(Node* node,std::ofstream& out)
	{
		if(!node)	
			return;
		out<<node->_key<<"\n";
		PreOrderL(node->_lNode,out);
		PreOrderL(node->_rNode,out);
	}

	Node* SearchKey(int key)
	{
		if(!_root)	
			return nullptr;
		
		Node *currNode=_root;

		while(currNode)
		{
			if(currNode->_key==key)	
				return currNode;
			else if(key<currNode->_key)
				currNode=currNode->_lNode;
			else
				currNode=currNode->_rNode;
		}
		return nullptr;
	}

    int FindMaxDiff(Node* startNode, int&maxDiff,Node*&_maxDiffNode)
    {
        if(!startNode)
            return 0;
        int lCount(0),rCount(0);
        int diff(0);
        
        lCount+=FindMaxDiff(startNode->_lNode,maxDiff,_maxDiffNode);
        rCount+=FindMaxDiff(startNode->_rNode,maxDiff,_maxDiffNode);
        diff=std::abs(lCount-rCount);
        if(diff>maxDiff)
        {
            maxDiff=diff;
            _maxDiffNode=startNode;
        }
        else if(diff==maxDiff)
            if(startNode->_key>_maxDiffNode->_key)   
                _maxDiffNode=startNode;
        return lCount+rCount+1;
    }

    void Problem_26()
    {
               
        int maxDiff(-1);
        Node*maxDiffNode=_root;

        FindMaxDiff(_root,maxDiff,maxDiffNode);
 
        DestroyKey(maxDiffNode->_key);

    }

};

int main()
{

	int tmp(0);
	
	std::ifstream in("tst.in");
	std::ofstream out("tst.out");

	std::vector<int> array_keys;
	
	while(!in.eof())
	{
		in>>tmp;				
		array_keys.push_back(tmp);
	}
	
	Tree tree1;

	for(int i(0);i<array_keys.size();++i)
		tree1.InsertNode(array_keys[i]);
		
    tree1.Problem_26();
    tree1.PreOrderL(tree1._root,out);

	in.close();
	out.close();
	
}
