#include <iostream>
using namespace std;


class TreeNode {
public:
    int Value;
    bool IsRed;
    TreeNode* Left, * Right, * Parent;
    TreeNode(int Value)
    {
        this->Value = Value;
        Left = Right = Parent = nullptr;
        this->IsRed = true;
    }
};

class RedBlackTree{
private:
    TreeNode* Root;
    void FixInsertion(TreeNode* ViolatedNode)
    {
        TreeNode* Parent = nullptr;
        TreeNode* GrandParent = nullptr;
        while (ViolatedNode != Root && ViolatedNode->IsRed && ViolatedNode->Parent->IsRed)
        {
            Parent = ViolatedNode->Parent;
            GrandParent = Parent->Parent;
            if (Parent == GrandParent->Left)
            {
                TreeNode* Uncle = GrandParent->Right;
                if (Uncle != nullptr && Uncle->IsRed)
                {
                    GrandParent->IsRed = true;
                    Parent->IsRed = false;
                    Uncle->IsRed = false;
                    ViolatedNode = GrandParent;
                }
                //Uncle is black
                else
                {
                    if (ViolatedNode == Parent->Right)
                    {
                        RotateLeft(Parent);
                        ViolatedNode = Parent;
                        Parent = ViolatedNode->Parent;
                    }
                    // line Case
                    else
                    {
                        RotateRight(GrandParent);

                        bool Temp = Parent->IsRed;
                        Parent->IsRed = GrandParent->IsRed;
                        GrandParent->IsRed = Temp;

                        ViolatedNode = Parent;
                    }
                }
            }
            // parent is Right Child
            else
            {
                TreeNode* Uncle = GrandParent->Left;
                if (Uncle != nullptr && Uncle->IsRed)
                {
                    GrandParent->IsRed = true;
                    Parent->IsRed = false;
                    Uncle->IsRed = false;
                    ViolatedNode = GrandParent;
                }
                //Uncle is black
                else
                {
                    if (ViolatedNode == Parent->Left)
                    {
                        RotateRight(Parent);
                        ViolatedNode = Parent;
                        Parent = ViolatedNode->Parent;
                    }
                    // line Case
                    else
                    {
                        RotateLeft(GrandParent);

                        bool Temp = Parent->IsRed;
                        Parent->IsRed = GrandParent->IsRed;
                        GrandParent->IsRed = Temp;

                        ViolatedNode = Parent;
                    }
                }
            }
        }
        Root->IsRed = false;
    }
    void RotateLeft(TreeNode* Node) {
        TreeNode* Right = Node->Right;
        Node->Right = Right->Left;
        if (Node->Right != nullptr)
            Node->Right->Parent = Node;

        Right->Parent = Node->Parent;

        if (Node->Parent == nullptr)
            Root = Right;
        else if (Node == Node->Parent->Left)
            Node->Parent->Left = Right;
        else
            Node->Parent->Right = Right;

        Right->Left = Node;
        Node->Parent = Right;
    }

    void RotateRight(TreeNode* Node) {
        TreeNode* Left = Node->Left;
        Node->Left = Left->Right;
        if (Node->Left != nullptr)
            Node->Left->Parent = Node;

        Left->Parent = Node->Parent;

        if (Node->Parent == nullptr)
            Root = Left;
        else if (Node == Node->Parent->Right)
            Node->Parent->Right = Left;
        else
            Node->Parent->Left = Left;

        Left->Right = Node;
        Node->Parent = Left;
    }
    TreeNode* FindNode(TreeNode* Node, int Value)
    {
        if (Node == nullptr || Node->Value == Value)
            return Node;
        else if (Value > Node->Value)
            return FindNode(Node->Right, Value);
        else
            return FindNode(Node->Left, Value);
    }
    void Replace(TreeNode* target, TreeNode* with) {
        if (target->Parent == nullptr)
            Root = with;
        else if (target == target->Parent->Left)
            target->Parent->Left = with;
        else
            target->Parent->Right = with;

        if (with != nullptr)
            with->Parent = target->Parent;
    }
    TreeNode* Minimum(TreeNode* node) {
        while (node->Left != nullptr)
            node = node->Left;
        return node;
    }
    void FixDelete(TreeNode* node) {
        while (node != Root && !node->IsRed) {
            if (node == node->Parent->Left) {
                TreeNode* sibling = node->Parent->Right;
                if (sibling->IsRed) {
                    sibling->IsRed = false;
                    node->Parent->IsRed = true;
                    RotateLeft(node->Parent);
                    sibling = node->Parent->Right;
                }

                if (!sibling->Left->IsRed && !sibling->Right->IsRed) {
                    sibling->IsRed = true;
                    node = node->Parent;
                }
                else {
                    if (!sibling->Right->IsRed) {
                        sibling->Left->IsRed = false;
                        sibling->IsRed = true;
                        RotateRight(sibling);
                        sibling = node->Parent->Right;
                    }

                    sibling->IsRed = node->Parent->IsRed;
                    node->Parent->IsRed = false;
                    sibling->Right->IsRed = false;
                    RotateLeft(node->Parent);
                    node = Root;
                }
            }
            else {
                TreeNode* sibling = node->Parent->Left;
                if (sibling->IsRed) {
                    sibling->IsRed = false;
                    node->Parent->IsRed = true;
                    RotateRight(node->Parent);
                    sibling = node->Parent->Left;
                }

                if (!sibling->Left->IsRed && !sibling->Right->IsRed) {
                    sibling->IsRed = true;
                    node = node->Parent;
                }
                else {
                    if (!sibling->Left->IsRed) {
                        sibling->Right->IsRed = false;
                        sibling->IsRed = true;
                        RotateLeft(sibling);
                        sibling = node->Parent->Left;
                    }

                    sibling->IsRed = node->Parent->IsRed;
                    node->Parent->IsRed = false;
                    sibling->Left->IsRed = false;
                    RotateRight(node->Parent);
                    node = Root;
                }
            }
        }
        node->IsRed = false;
    }
    void DeleteNode(TreeNode* nodeToDelete) {
        TreeNode* nodeToFix = nullptr;
        TreeNode* parent = nullptr;
        TreeNode* child = nullptr;

        bool originalColor = nodeToDelete->IsRed;

        if (nodeToDelete->Left == nullptr) {
            child = nodeToDelete->Right;
            Replace(nodeToDelete, child);
        }
        else if (nodeToDelete->Right == nullptr) {
            child = nodeToDelete->Left;
            Replace(nodeToDelete, child);
        }
        else {
            TreeNode* successor = Minimum(nodeToDelete->Right);
            originalColor = successor->IsRed;
            child = successor->Right;

            if (successor->Parent == nodeToDelete) {
                if (child != nullptr)
                    child->Parent = successor;
            }
            else {
                Replace(successor, successor->Right);
                successor->Right = nodeToDelete->Right;
                successor->Right->Parent = successor;
            }

            Replace(nodeToDelete, successor);
            successor->Left = nodeToDelete->Left;
            successor->Left->Parent = successor;
            successor->IsRed = nodeToDelete->IsRed;
        }

        if (!originalColor && child != nullptr) {
            FixDelete(child);
        }
    }
    void PrintHelper(TreeNode* Node, string Indent, bool Last) {
        if (Node != nullptr) {
            cout << Indent;
            if (Last) {
                cout << "R----";
                Indent += "   ";
            }
            else {
                cout << "L----";
                Indent += "|  ";
            }
            string Color = (Node->IsRed == true) ? "RED" : "BLK";
            cout << Node->Value << "(" << Color << ")" << endl;
            PrintHelper(Node->Left, Indent, false);
            PrintHelper(Node->Right, Indent, true);
        }
    }
public:
    RedBlackTree()
    {
        Root = nullptr;
    }
    void Insert(int Value)
    {
        TreeNode* NewNode = new TreeNode(Value);
        if (Root == nullptr)
        {
            Root = NewNode;
            Root->IsRed = false;
            return;
        }
        TreeNode* Current = Root;
        TreeNode* Parent = nullptr;
        while (Current != nullptr)
        {
            Parent = Current;
            if (Value > Current->Value)
                Current = Current->Right;
            else
                Current = Current->Left;
        }
        
        NewNode->Parent = Parent;
        if (Value > Parent->Value)
            Parent->Right = NewNode;
        else
            Parent->Left = NewNode;

        FixInsertion(NewNode);

    }
    void PrintTree()
    {
        PrintHelper(Root, "", true);
    }
    TreeNode* Find(int Value)
    {
        return FindNode(Root, Value);
    }
    bool Delete(int value) {
        TreeNode* nodeToDelete = FindNode(Root, value);
        if (nodeToDelete == nullptr)
            return false;

        DeleteNode(nodeToDelete);
        return true;
    }
};


int main() 
{
    RedBlackTree r;
    r.Insert(47);
    r.Insert(32);
    r.Insert(71);
    r.Insert(93);
    r.Insert(65);
    r.Insert(82);
    r.Insert(22);
    r.PrintTree();
    r.Delete(47);
    cout << endl;
    r.PrintTree();

   
}
