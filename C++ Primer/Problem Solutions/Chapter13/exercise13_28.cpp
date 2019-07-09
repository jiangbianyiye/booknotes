#include<iostream>
#include<string>

class TreeNode{
public:
    TreeNode(const std::string value = std::string(), TreeNode *lchild = nullptr, TreeNode *rchild = nullptr)
        :value(value), count(1), left(lchild), right(rchild){}
    TreeNode(const TreeNode& origin)
        :value(origin.value), count(origin.count), left(origin.left), right(origin.right){}
    
    void CopyTree(void){
        
    }

private:
    std::string value;
    int count;
    TreeNode *left;
    TreeNode *right;
};

class BinStrTree{
public:
    BinStrTree(TreeNode *root = nullptr)
        :root(root){}
    BinStrTree(const BinStrTree &bst)
        :root(bst.root){
        root->CopyTree();
    }
private:
    TreeNode *root;
};