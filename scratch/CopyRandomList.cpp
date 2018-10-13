/**
 * 剑指offer,面试35:复杂链表的复制
 */

#include<iostream>

struct RandomListNode {
    int label;
    struct RandomListNode *next, *random;
    RandomListNode(int x) :
            label(x), next(nullptr), random(nullptr) {
    }
};

void printRandomList(RandomListNode * pHead);

class Solution {
public:
    RandomListNode* Clone(RandomListNode* pHead)
    {
        auto pCur = pHead;
        while(pCur != nullptr){
            RandomListNode * newNode = new RandomListNode(pCur->label);
            auto pNext = pCur->next;
            pCur->next = newNode;
            newNode->next = pNext;
            pCur = pNext;
        }

        pCur = pHead;
        while(pCur != nullptr){
            if(pCur->random != nullptr){
                pCur->next->random = pCur->random->next;
            }
            pCur = pCur->next->next;
        }

        pCur = pHead;
        RandomListNode * pClonedHead = nullptr;
        RandomListNode * pClonedCur = nullptr;
        RandomListNode * pOriginCur = nullptr;
        
        while(pCur != nullptr){
            auto pNext = pCur->next;
            
            if(pOriginCur == nullptr){
                pOriginCur = pCur;
            }
            else{
                pOriginCur->next = pCur;
                pOriginCur = pCur;
            }
            
            if(pClonedHead == nullptr){
                pClonedCur = pClonedHead = pNext;
            }
            else{
                pClonedCur->next = pNext;
                pClonedCur = pNext;
            }
            pCur = pNext->next;
        }
        if(pOriginCur != nullptr)
            pOriginCur->next = nullptr;
        return pClonedHead;
    }
};

void printRandomList(RandomListNode * pHead){
    auto pCur = pHead;
    while(pCur != nullptr){
        std::cout<<pCur->label<<"\t";
        pCur = pCur->next;
    }
    std::cout<<std::endl;
}

int main(int argc, char const *argv[])
{
    Solution sl;

    RandomListNode * pHead = new RandomListNode(0);
    auto pCur = pHead;
    for(int i=1; i<5; ++i){
        pCur->next = new RandomListNode(i);
        pCur = pCur->next;
    }

    pHead->random = pHead->next->next;

    RandomListNode * pColendHead = sl.Clone(pHead);
    printRandomList(pHead);
    printRandomList(pColendHead);


    return 0;
}
