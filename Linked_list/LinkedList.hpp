// putting linkedlist in a template
// with new modification for stack and queue 

#ifndef linkedlist_h
#define linkedlist_h

namespace GT {

    //---------------------------------------------------------------

    template <typename T>
    class LinkedList {
    public:
        class INodeVisitor;
        struct Node {
            Node* next;
            T value;

            //Node OCF
            Node(T aValue = 0, Node*next =nullptr) : value(aValue) {}
            ~Node() = default;
            Node(const Node& aCopy) { *this = aCopy; }
            
            Node& operator = (const Node& aCopy) {
                return *this;
            }

            Node operator ()(INodeVisitor& aVisitor) const {
                aVisitor.visit(*this);
                return *this;
            }
            

        }; // end of Node struct

    protected:
        Node* root;  //FRONT of list (may be nullptr)
        size_t  count;  //oooh, let's keep track of the count as we go!

    public:
        // Linked list OCF
        LinkedList() { root = nullptr; count = 0; }
        LinkedList(const LinkedList<T>& aCopy) { *this = aCopy; }
        LinkedList<T>& operator = (const LinkedList<T>& aCopy) {
            root = new Node(*aCopy.root);
            count = aCopy.count;
            return *this;
        }
        ~LinkedList() {
            while (root) {
                auto temp = root;
                root = root->next;
                delete temp;
            }
        }

        //Other methods in linked list 
        Node* first() const { //retrieve first node in the list.
          //if LinkedList is empty, root pointer will be a nullptr, we initialized this on const
            return root;
        }
        bool isempty() {
            return root == nullptr;
        }

        size_t size() {//return # of nodes in the list...

            Node* temp = root;
            int count = 0;

            while (temp != nullptr) { // traverse
                count++;
                temp = temp->next; // update temp 
            }
            return count;
        }

        //find a Node that contains a given value
        Node* find(const T& aValue, Node* anOrigin = nullptr) {

            // in case anOrigin is not nullptr, start at specified node
            if (anOrigin != nullptr) {
                Node* temp = anOrigin; // temp is specified node
                while (temp != nullptr) {//traverse
                    if (temp->value == aValue) {
                        //If element found return index
                        return temp;
                    }
                    temp = temp->next; // update temp, still in while

                }
            }
            //default case
            //anOrigin == nullptr
            Node* temp = root;
            while (temp != nullptr) {//traverse
                if (temp->value == aValue) {
                    return temp;
                }
                temp = temp->next;
            }

            return temp; //must return a value error
            // should return the last node, which is nullptr
            // value was not found 
        }

        Node* append(const T& aValue) {
            Node* newNode = new Node(aValue);// allocated newNode
            newNode->value = aValue;
            newNode->next = nullptr;

            // check if linked list is empty
            if (root == nullptr) {
                root = newNode; // first node, last node, the only node
                return root;

            }
            // if linked list is not empty
            // find the last node first
            Node* temp = root;
            while (temp->next != nullptr) {//traverse
                temp = temp->next;
            }
            //why we must do next in the while? we want to find the last node, not the nullptr

            temp->next = newNode; // make that last node a new node
            return newNode;
            delete newNode;

        }

        Node* insertAfter(const T& aValue, Node* anOrigin = nullptr) {
            Node* newNode = new Node(aValue);
            newNode->value = aValue;
            newNode->next = nullptr;

            // if Node *anOrigin = nullptr then insert new item in front of list
            if (anOrigin == nullptr) {
                newNode->next = root;
                root = newNode;
            }

            //insert after
            else {
                newNode->next = anOrigin->next;
                anOrigin->next = newNode;
            }

            return newNode;
            delete newNode;
        }

        Node* remove(const T& aValue) {

            Node* temp = root;
            Node* prev = nullptr;
            Node* holdvalue = find(aValue);

            if (holdvalue == temp) {
                root = temp->next;
                temp->next = nullptr;
                return temp;
            }

            // if item not in list, find should return null
            //by default just search, remember to made connection before unlinking

            while (temp != nullptr && temp != holdvalue)
            {
                prev = temp;
                temp = temp->next; //acooment
            }

            // Unlink the node from linked list
            prev->next = temp->next;

            temp->next = nullptr;
            return temp;
        }

        Node* getLast() {
            Node* thelast = root;

            if (isempty()) {
                std::cout << "no peek is empty" << "\n";
            }

            while (thelast && thelast->next) {
                thelast = thelast->next;
            }

            return thelast;
        }

        void removeLast() {
            if (root == nullptr) {
                std::cout << "stack is empty nothing to delete" << "\n";
            }
            if (root != nullptr) {
                if (root->next == nullptr) {
                    root = nullptr;
                }
                else {
                    Node* temp = root;
                    while (temp->next->next != nullptr) {
                        temp = temp->next;
                    } 
                    Node* lastNode = temp->next;
                    temp->next = nullptr;
                    
                    delete lastNode; 
                }
            }
        }

        void removeFirst() {
            if (isempty()) {
                std::cout << "queue is empty nothing to remove" << "\n";
            }
            Node* temp = root;
            root = root->next;

            delete temp;  
        }

      //put INodeVisitor here...
        class INodeVisitor {
        public:
            virtual void visit(const Node& aNode) = 0;
            virtual ~INodeVisitor() = default;

        }; // end of class INodeVisitor


        //add LinkedList::visitWith method here...
        LinkedList<T>& visitWith(INodeVisitor& aVisitor) {
            Node* theCurrent{ root };
            while (theCurrent) {
                (*theCurrent)(aVisitor);
                theCurrent = theCurrent->next;

            }
            return *this;
           
            
        }//end of visitwith
      
    };//end of class linked list

}// outside of linked list in namespace

#endif /* linkedlist_h */
