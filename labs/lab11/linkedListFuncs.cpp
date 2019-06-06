
#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

/*
  functions for use with CS2124 rec11
  -jbs
*/

// Node to be used a part of linked list
struct Node {
	Node(int data = 0, Node* next = nullptr) : data(data), next(next) {}
	int data;
	Node* next;
};

// listAddHead: adds a data item to the beginning of a [possibly empty] list
//it basically does not have header
//this is add first? yeah - ADDHEAD You see????

void listAddHead(Node*& headPtr, int entry) {
	headPtr = new Node(entry, headPtr);
}

// listClear: frees up all the nodes in a list
void listClear(Node*& headPtr) {
    while (headPtr) {
        Node* next = headPtr->next;
        delete headPtr;
        headPtr = next;
    }
}

// listBuild: constructs a list from a vector of data items. Note that
// you can use a curly-braced sequence.
// This may be useful for setting up test cases. Feel free to use it
// or not as you like. 
// Example of using would be:
//    Node* myList = listBuild({1, 4, 9, 16}); // builds a list of: 1 4 9 16
Node* listBuild(const vector<int>& vals) {
    Node* result = nullptr;
    for (size_t index = vals.size(); index > 0; --index) {
        listAddHead(result, vals[index-1]);
    }
    return result;
}

void splice(Node* llst, Node* spliceStarter){
    if(!llst) return;
    Node* post = spliceStarter-> next;
    spliceStarter-> next = llst;
    Node* tracker = llst;
    while(tracker->next){
        tracker = tracker->next;
    }
    tracker->next = post;
}

void displayList(Node* llst){
    if(!llst) return;
    Node* tracker = llst;
    while(tracker){
        cout << tracker->data << ' ';
        tracker = tracker->next;
    }
    cout << endl;
}

//what if there is more than one match of the sublist
//the first one found
Node* isSubList(Node* subLTest, Node* fromLst){
    Node* trackerO = fromLst;
    Node* trackerS = subLTest;

    if(!subLTest) return fromLst;
    if(!fromLst){
        cout << "Failed to match"; 
        return nullptr; 
    } 
    //recursion
    while(trackerO){
        if(trackerO->data == trackerS->data){
            Node* trackerOCurr = trackerO;
            //trackerOCurr = trackerOCurr -> next;
            Node* trackerSCurr = trackerS;
            //trackerSCurr = trackerSCurr -> next;

            // unsigned Ocount = 0;
            // unsigned Scount = 0;
            //cout << "Testing\n";
            //dont do ->next: has to check the last element
            while(trackerOCurr && trackerSCurr && trackerOCurr-> data == trackerSCurr-> data){
                // if(trackerOCurr-> data != trackerSCurr-> data){
                //     break;
                // }
                //cout << trackerO ->data << ' ';
                trackerOCurr = trackerOCurr ->next;
                trackerSCurr = trackerSCurr -> next;
                // Ocount++;
                // Scount++;
            }
            //cout << endl;
            if(!trackerSCurr){
                return trackerO;
            }
            // else{
            //     trackerO = trackerOCurr;
            // }
        }
        trackerO = trackerO->next;
    }
    cout << "Failed to match" << endl;
    return nullptr;
}

Node* sharedListBruteForce(Node* ll1, Node* ll2){
    Node* tracker1 = ll1;
    Node* tracker2 = ll2;
    while(tracker1){
        while(tracker2){
             if(tracker1 == tracker2){
                cout << "Matched: " << tracker1->data << endl;
                return tracker1;
            }
            tracker2 = tracker2-> next;
        }
       
        tracker1 = tracker1->next;
        tracker2 = ll2;
    }
    cout << "No match\n";
    return nullptr;
}

Node* sharedListUsingSet(Node* ll1, Node* ll2){
    Node* tracker1 = ll1;
    Node* tracker2 = ll2;
    unordered_set<Node*> ll1Copy;
    while(tracker1){
        ll1Copy.insert(tracker1);
        tracker1 = tracker1->next;
    }
    while(tracker2){
        //Node* sharedStart = ll1Copy.find(tracker2);
        //
        if(ll1Copy.find(tracker2) != ll1Copy.end()){
            return tracker2;
        }
        tracker2 = tracker2->next;
    }
    return nullptr;
}

Node* sharedListUsingSetSpace(Node* ll1, Node* ll2){
    Node* tracker1 = ll1;
    Node* tracker2 = ll2;
    //hash_map
    unordered_set<Node*> llCopy;

    unsigned countLength1 = 0;
    unsigned countLength2 = 0;
    while(tracker1){
        countLength1 ++;
        tracker1 = tracker1 -> next;
    }
    while(tracker2){
        countLength2 ++;
        tracker2 = tracker2 ->next;
    }

    tracker1 = ll1;
    tracker2 = ll2;

    if(countLength1 > countLength2){
        while(tracker1 && countLength1 >= countLength2){//trouble when i didnt have ==
            llCopy.insert(tracker1);
            tracker1 = tracker1->next;
            countLength1 --;
        }
        while(tracker2){
            //Node* sharedStart = ll1Copy.find(tracker2);
            //
            if(llCopy.find(tracker2) != llCopy.end()){
                return tracker2;
            }
            tracker2 = tracker2->next;
        }
    }
    else{
        //also =< does not work loll
        while(tracker2 && countLength1 <= countLength2){//trouble when i didnt have ==
            llCopy.insert(tracker2);
            tracker2 = tracker2->next;
            countLength2 --;
        }
        while(tracker1){
            //Node* sharedStart = ll1Copy.find(tracker2);
            //
            if(llCopy.find(tracker1) != llCopy.end()){
                return tracker1;
            }
            tracker1 = tracker1->next;
        }
    }
    
    return nullptr;
}
Node* sharedListUsingSetSpace2(Node* ll1, Node* ll2){
    Node* tracker1 = ll1;
    Node* tracker2 = ll2;
    unsigned countLength1 = 0;
    unsigned countLength2 = 0;
    while(tracker1){
        countLength1 ++;
        tracker1 = tracker1 -> next;
    }
    while(tracker2){
        countLength2 ++;
        tracker2 = tracker2 ->next;
    }

    tracker1 = ll1;
    tracker2 = ll2;

    if(countLength1 > countLength2){
        while(tracker1 && countLength1 >= countLength2){
            if(tracker1 == tracker2){
                return tracker1;
            }
            tracker1 = tracker1->next;
            countLength1--;
        }
    }
    else{
        while(tracker2 && countLength1 <= countLength2){
            if(tracker1 == tracker2){
                return tracker2;
            }
            tracker2 = tracker2->next;
            countLength2--;
        }
    }
    return nullptr;
}


int main(){
    // Node* llst1 = listBuild({1,2,6,7,8});
    // displayList(llst1);

    // Node* spliceStarter = llst1 -> next ->next;

    // Node* lls2 = listBuild({3,4,5});
    // displayList(lls2);
    // splice(lls2, spliceStarter);
    // displayList(llst1);


    // Node* llst3 = listBuild({1,2,3,4,5,6});
    // Node* llst4 = listBuild({3,4,5});
    // Node* llst5 = listBuild({2,5,6});

    // displayList(llst3);
    // displayList(llst4);
    // displayList(llst5);

    // // cout << isSubList(llst4, llst3)-> data << endl;
    // // cout << isSubList(llst5, llst3)-> data << endl;
    // displayList(isSubList(llst4, llst3));
    // displayList(isSubList(llst5, llst3));

    cout << "Part One:\n";
    Node* l1 = listBuild({5,7,9,1});
    cout << "L1: ";
    displayList(l1);
    Node* l2 = listBuild({6,3,2});
    cout << "L2: ";
    displayList(l2);
    Node* target = l1->next;
    cout << "Target: ";
    displayList(target);

    cout << "Splicing L2 at target in L1" << endl;
    splice(l2,l1);
    cout << "L1: ";
    displayList(l1);
    cout << "L2: ";
    displayList(l2);

    cout << "\n==============================\n";

/*
    cout << "Part Two:\n";

    Node* target2 = listBuild({1,2,3,2,3,2,4,5,6});
    cout << "Target: ";
    displayList(target2);
    cout << "Attempt match: 1\n";
    Node* test1 = listBuild({1});
    displayList(sharedListBruteForce(test1, target2));

    cout << "Attempt match: 3 9 \n";
    Node* test2 = listBuild({3,9});
    displayList(sharedListBruteForce(test2, target2));

    cout << "Attempt match: 2 3 \n";
    Node* test3 = listBuild({2,3});
    displayList(sharedListBruteForce(test3, target2));

    cout << "Attempt match: 2 4 5 6 \n";
    Node* test4 = listBuild({2,4,5,6});
    displayList(sharedListBruteForce(test4, target2));

    cout << "Attempt match: 2 3 2 4 \n";
    Node* test5 = listBuild({2,3,2,4});
    displayList(sharedListBruteForce(test5, target2));
    cout << "Attempt match: 5 6 7 \n";
    Node* test6 = listBuild({5,6,7});
    displayList(sharedListBruteForce(test6, target2));
*/

    cout << "Part Three: Brute Force\n";

    Node* target2 = listBuild({1,2,3,4,5,6});
    cout << "Target: ";
    displayList(target2);
    cout << "Attempt match: 5\n";
    Node* test1 = target2 ->next->next->next->next;
    displayList(sharedListBruteForce(test1, target2));

    cout << "Attempt match: 3\n";
    Node* test2 = target2 ->next->next;
    displayList(sharedListBruteForce(test2, target2));

    cout << "Attempt match: 3 not same Node\n";
    Node* test3 = listBuild({3});
    displayList(sharedListBruteForce(test3, target2));


    cout << "\n==============================\n";
    cout << "Part Three: Set \n";

    // Node* target2 = listBuild({1,2,3,4,5,6});
    // cout << "Target: ";
    // displayList(target2);
    cout << "Attempt match: 5\n";
    Node* test4 = target2 ->next->next->next->next;
    displayList(sharedListUsingSet(test4, target2));

    cout << "Attempt match: 3\n";
    Node* test5 = target2 ->next->next;
    displayList(sharedListUsingSet(test5, target2));

    cout << "Attempt match: 3 not same Node\n";
    Node* test6 = listBuild({3});
    displayList(sharedListUsingSet(test6, target2));


     cout << "\n==============================\n";
    cout << "Part Three: Set with O(1) space\n";

    // Node* target2 = listBuild({1,2,3,4,5,6});
    // cout << "Target: ";
    // displayList(target2);
    cout << "Attempt match: 5\n";
    Node* test7 = target2 ->next->next->next->next;
    displayList(sharedListUsingSetSpace2(test7, target2));

    cout << "Attempt match: 3\n";
    Node* test8 = target2 ->next->next;
    displayList(sharedListUsingSetSpace2(test8, target2));

    cout << "Attempt match: 3 not same Node\n";
    Node* test9 = listBuild({3});
    displayList(sharedListUsingSetSpace2(test9, target2));


   


}