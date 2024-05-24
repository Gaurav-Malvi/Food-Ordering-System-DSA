#include <bits/stdc++.h>
using namespace std;

class customer {
public:
    int age;
    string name;
    string pizzaName;
    int quantity;
    double bill;

    customer() {}

    customer(int age, string name, int quantity, string pizzaName, double bill) {
        this->age = age;
        this->name = name;
        this->pizzaName = pizzaName;
        this->quantity = quantity;
        this->bill = bill;
    }
};

// Take Away Customer

class takeAwayCustomer{
public:
    customer c;
    takeAwayCustomer *next = NULL;

    takeAwayCustomer(int age, string name, int quantity, string pizzaName, double bill){
        this->c = customer(age, name, quantity, pizzaName, bill);
    }
};


// Dine IN Customer

class dineInCustomer{
public:
    customer c;
    dineInCustomer *next = NULL;

    dineInCustomer(int age, string name, int quantity, string pizzaName, double bill){
        this->c = customer(age, name, quantity, pizzaName, bill);
    }
};


// Home Delivery Customer

class homeDeliveryCustomer{
public:
    customer c;
    string address;
    double deliveryCharges;
    int distanceDelivery;
    homeDeliveryCustomer *next = NULL;

    homeDeliveryCustomer(int age, string name, int quantity, string pizzaName, double bill, string address, double deliveryCharges, int distanceDelivery){
        this->c = customer(age, name, quantity, pizzaName, bill);
        this->address = address;
        this->deliveryCharges = deliveryCharges;
        this->distanceDelivery = distanceDelivery;
    }
};


// Pizza Shop

class pizzaShop{
public:
    string shopName;
    string *menu;
    int *price;
    string address;
    takeAwayCustomer *nextTakeAwayCustomer = NULL;
    dineInCustomer *nextDineInCustomer = NULL;
    homeDeliveryCustomer *nextHomeDeliveryCustomer = NULL;
};

pizzaShop *myPizzaShop = NULL;

takeAwayCustomer *currentTakeAwayCustomer = NULL;
dineInCustomer *currentDineInCustomer = NULL;
homeDeliveryCustomer *currentHomeDeliveryCustomer = NULL;

double total, takeAway, dineIn, homeDelivery;

double servedTotal;


// Serve Customer

class servedCustomer{
public:
    int age;
    string name;
    int quantity;
    string pizzaName;
    double bill;
    string customerType;
    servedCustomer *left;
    servedCustomer *right;

    servedCustomer(int age, string name, int quantity, string pizzaName, double bill, string customerType)
    {
        // setting customers details

        this->age = age;
        this->name = name;
        this->quantity = quantity;
        this->pizzaName = pizzaName;
        this->bill = bill;
        this->customerType = customerType;

        // child to NULL
        this->left = NULL;
        this->right = NULL;
    }
};

servedCustomer *root = NULL; // Global pointer for the root of AVL tree

// isEmpty or not
bool isEmpty(servedCustomer *root) {
    return root == NULL;
}


void display(servedCustomer *root){
    cout << "Name :" << root->name << endl;
    cout << "Age  :" << root->age << endl;
    cout << "Pizza :" << root->pizzaName << endl;
    cout << "Quantity : " << root->quantity << endl;
    cout << "Bill : " << root->bill << endl;
    cout << "Customer Type: " << root->customerType << endl;
}


// Traversal for the served Customers
servedCustomer *displayAllServedOrderes(servedCustomer *root){
    if(root){
        displayAllServedOrderes(root->left);
        display(root);
        displayAllServedOrderes(root->right);
    }
    return root;
}

// Height of servedCustomer tree
int height(servedCustomer *root){
    if(!root)
        return 0;

    return 1 + max(height(root->left), height(root->right));
}

// Balance Factor for each ServedCustomer node
int balanceFactor(servedCustomer *root){
    if(!root)
        return 0;

    return height(root->left) - height(root->right);
}

// Max of two integers as a helper functin for height
int max(int a, int b){
    return (a > b) ? a : b;
}


// Searching in servedCustomer tree 
servedCustomer *search(servedCustomer *root, string keyName){
    if(!root)
        return NULL;

    else if(root->name == keyName)
        return root;

    else if(root->name < keyName)
        return search(root->right, keyName);

    else if(root->name > keyName)
        return search(root->left, keyName);

    return root;
}

// Finding max node of served customer tree
servedCustomer *maxservedCustomer(servedCustomer *root){
    servedCustomer *p = root;
    servedCustomer *temp = NULL;

    while(p != NULL){
        temp = p;
        p = p->right;
    }

    return temp;
}

// Balancing the ServedCustomer's Tree throght AVL Rotations

// LL Rotation
servedCustomer *LLRotation(servedCustomer *root){
    servedCustomer *x = root->left;
    servedCustomer *temp = x->right;

    x->right = root;
    root->left = temp;

    root = x;
    
    return x;
}

// RR Rotation
servedCustomer *RRRotation(servedCustomer *root){
    servedCustomer *x = root->right;
    servedCustomer *temp = x->left;

    x->left = root;
    root->right = temp;

    root = x;

    return x;
}

// LR Rotation
servedCustomer *LRRotation(servedCustomer *root){
    root->left = RRRotation(root->left);
    return LLRotation(root);
}

// RL Rotation
servedCustomer *RLRotation(servedCustomer *root){
    root->right = LLRotation(root->right);
    return RRRotation(root);
}


// INSERTION in servedCustomer Tree
servedCustomer *insertion(int age, string name, int quantity, string pizzaName, double bill, string customerType, servedCustomer *root){
    servedCustomer *newNode = new servedCustomer(age, name, quantity, pizzaName, bill, customerType);

    if(root == NULL)
        root = newNode;

    else if(root->name > newNode->name)
        root->left = insertion(age, name, quantity, pizzaName, bill, customerType, root->left);

    else if(root->name < newNode->name)
        root->right = insertion(age, name, quantity, pizzaName, bill, customerType, root->right);

    else{
        cout<<"No duplicates values are allowed "<<endl;
        return root;
    }

    int bf = balanceFactor(root);

    if(bf == 2){
        // LL
        if(root->left->name > newNode->name)
            return LLRotation(root);

        // LR
        if(root->left->name > newNode->name)
            return LRRotation(root);
    }

    else if (bf == -2){
        // RR
        if (root->right->name < newNode->name)
            return RRRotation(root);

        // RL
        if (root->right->name > newNode->name)
            return RLRotation(root);
    }

    return root;
}

// Delete Node
servedCustomer *deleteNode(servedCustomer *root, string key){
    if(!root)
        return root;
    else if(key < root->name)
        root->left = deleteNode(root->left, key);
    else if(key > root->name)
        root->right = deleteNode(root->right, key);
    else{
        if(root->left == NULL || root->right == NULL){
            servedCustomer *temp = root->left ? root->left : root->right;

            if(temp == NULL){
                temp = root;
                root = NULL;
            }
            else    
                *root = *temp;
            delete(temp);
        }

        else{
            servedCustomer *temp = maxservedCustomer(root->right);
            root->name = temp->name;
            root->right = deleteNode(root->right, temp->name);
        }
    }

    if(!root)
        return root;

    if (root == NULL)
        return root;

    // getting the balance factor
    int balance = balanceFactor(root);

    // Rotation Cases
    // LEFT LEFT CASE
    if (balance > 1 && key < root->left->name)
        return LLRotation(root);

    // LEFT RIGHT CASE
    if (balance > 1 && key > root->left->name){
        root->left = LLRotation(root->left);
        return LRRotation(root);
    }

    // RIHGT RIGHT CASE
    if (balance < -1 && key > root->right->name)
        return RRRotation(root);

    // RIGHT LEFT CASE
    if (balance < -1 && key < root->right->name){
        return RLRotation(root);
    }

    return root;
}

// Delete all served node
void deleteAllServedCustomers(servedCustomer *root){
    while(root){
        root = deleteNode(root, root->name);
    }

    cout<<"The Served Customer's List is Cleared"<<endl;
}


// place order for take away customer (Older person high priority)
void placeOrderTakeAwayCustomer(int age, string name, string pizzaName, int quantity, double bill){
    // making new customer
    currentTakeAwayCustomer = new takeAwayCustomer(age, name, quantity, pizzaName, bill);

    if(myPizzaShop->nextTakeAwayCustomer == NULL)
        myPizzaShop->nextTakeAwayCustomer = currentTakeAwayCustomer;

    else{
        // finding the last node
        takeAwayCustomer *temp = myPizzaShop->nextTakeAwayCustomer;
        while(temp->next != NULL){
            temp = temp->next;
        }

        if(temp->c.age < currentTakeAwayCustomer->c.age){
            // insert at front
            takeAwayCustomer *firstCustomer = myPizzaShop->nextTakeAwayCustomer;
            myPizzaShop->nextTakeAwayCustomer = currentTakeAwayCustomer;
            currentTakeAwayCustomer->next = firstCustomer; 
        }

        else{
            // insert at end
            temp->next = currentTakeAwayCustomer;
            currentTakeAwayCustomer->next = NULL;
        }
    }
    cout << "Your Order has been Placed MR/MRS " << name << " and your order is " << pizzaName << " with " << quantity << " quantity and total bill is " << bill << endl;
}


void serveOrderTakeAwayCustomer(){
    if(myPizzaShop->nextTakeAwayCustomer == NULL)
        cout<<"No Take Away Customer to serve"<<endl;

    else{
        takeAwayCustomer *temp = myPizzaShop->nextTakeAwayCustomer;
        // if it has some next element
        if(temp->next != NULL){
            myPizzaShop->nextTakeAwayCustomer = temp->next;
        }
        else{
            myPizzaShop->nextTakeAwayCustomer = NULL;
        }
        
        cout << "Take Away Customer Served : " << temp->c.name << endl;

        string customerType = "Take-Away";
        // Now before deleting the node we need to update the servedCustomer Tree
        root = insertion(temp->c.age, temp->c.name, temp->c.quantity, temp->c.pizzaName, temp->c.bill, customerType, root);

        delete temp; // deleting the customer
    }
}


// For Dine in Customer (FIFO)
void placeOrderDineInCustomer(int age, string name, string pizzaName, int quantity, double bill){
    // making new customer
    currentDineInCustomer = new dineInCustomer(age, name, quantity, pizzaName, bill);

    if(myPizzaShop->nextDineInCustomer == NULL)
        myPizzaShop->nextDineInCustomer = currentDineInCustomer;

    else{
        // finding last node
        dineInCustomer *temp = myPizzaShop->nextDineInCustomer;
        while (temp->next != NULL){
            temp = temp->next;
        }

        temp->next = currentDineInCustomer;
        currentDineInCustomer->next = NULL;
    }
    cout << "Your Order has been Placed MR/MRS " << name << " and your order is " << pizzaName << " with " << quantity << " quantity and total bill is " << bill << endl;

}

void serveOrderDineInCustomer(){
    if(myPizzaShop->nextDineInCustomer == NULL)
        cout<<"No Dine-In Customer to Serve"<<endl;

    else{
        // serving the first customer
        dineInCustomer *temp = myPizzaShop->nextDineInCustomer;
        if(temp->next != NULL){
            myPizzaShop->nextDineInCustomer = temp->next;
        }
        else{
            myPizzaShop->nextDineInCustomer = NULL;
        }

        cout << "Dine-In Customer Served : " << temp->c.name << endl;

        string customerType = "Dine-In";
        // Now before deleting the node we need to update the servedCustomer Tree
        root = insertion(temp->c.age, temp->c.name, temp->c.quantity, temp->c.pizzaName, temp->c.bill, customerType, root);

        delete temp; // deleting the customer
    }
}


// For Home Delivery customer (LIFO)

void placeOrderHomeDeliveryCustomer(int age, string name, string pizzaName, int quantity, double bill, string address, int deliveryCharges, int distanceDelivery){
    currentHomeDeliveryCustomer = new homeDeliveryCustomer(age, name, quantity, pizzaName, bill, address, deliveryCharges, distanceDelivery);

    if(myPizzaShop->nextHomeDeliveryCustomer == NULL)
        myPizzaShop->nextHomeDeliveryCustomer = currentHomeDeliveryCustomer;

    else{
        // finding last node
        homeDeliveryCustomer *temp = myPizzaShop->nextHomeDeliveryCustomer;
        while(temp->next != NULL){
            temp = temp->next;
        }

        temp->next = currentHomeDeliveryCustomer;
        currentHomeDeliveryCustomer->next = NULL;

        cout << "Your Order has been Placed MR/MRS " << name << " and your order is " << pizzaName << " with " << quantity << " quantity and total bill is " << bill << endl;
    }
}

void serveOrderHomeDeliveryCustomer(){
    if(myPizzaShop->nextHomeDeliveryCustomer == NULL)
        cout<<"No Home Delivery Customer to serve"<<endl;

    else{
        // serving the last customer first
        homeDeliveryCustomer *first = myPizzaShop->nextHomeDeliveryCustomer;

        if(first->next == NULL){
            // if it is the only customer

            myPizzaShop->nextHomeDeliveryCustomer = NULL;

            cout << "Home Delivery Customer Served : " << first->c.name << endl;
            string customerType = "Home-Delivery Customer";
            root = insertion(first->c.age, first->c.name, first->c.quantity, first->c.pizzaName, first->c.bill, customerType, root);

            // now deleting the node
            delete (first);
        }

        else{
            homeDeliveryCustomer *s = first->next;
            while(s->next != NULL){
                first = first->next;
                s = s->next;
            }

            first->next = NULL;

            cout << "Home Delivery Customer Served : " << s->c.name << endl;
            string customerType = "Home-Delivery Customer";
            root = insertion(s->c.age, s->c.name, s->c.quantity, s->c.pizzaName, s->c.bill, customerType, root);

            // deleting the node

            delete (s);
        }
    }
}


// Serve all orders

void serveAllOrders(){
    while(myPizzaShop->nextTakeAwayCustomer != NULL)
        serveOrderTakeAwayCustomer();

    while(myPizzaShop->nextDineInCustomer != NULL)
        serveOrderDineInCustomer();

    while(myPizzaShop->nextHomeDeliveryCustomer != NULL)
        serveOrderHomeDeliveryCustomer();
}

void displayAllOrdersTakeAwayCustomers(){
    if (myPizzaShop->nextTakeAwayCustomer == NULL){
        cout << "There is no Order for Walking Customer till yet" << endl;
    }

    else{
        takeAwayCustomer *traversal = myPizzaShop->nextTakeAwayCustomer;
        while (traversal != NULL){

            cout << "-----------------------------------------------------" << endl;
            cout << "Take-Away Customer : " << traversal->c.name << endl;
            cout << "Age : " << traversal->c.age << endl;
            cout << "Pizza Name : " << traversal->c.pizzaName << endl;
            cout << "Quantity : " << traversal->c.quantity << endl;
            cout << "Bill : " << traversal->c.bill << " RS/_" << endl;
            cout << "-----------------------------------------------------" << endl;

            traversal = traversal->next;
        }
    }
}


void displayAllOrdersHomeDeliveryCustomers(){
    if (myPizzaShop->nextHomeDeliveryCustomer == NULL){
        cout << "There is no Order for Home Delivery Customer till yet" << endl;
    }

    else{
        homeDeliveryCustomer *traversal = myPizzaShop->nextHomeDeliveryCustomer;
        while (traversal != NULL){
            cout << "-----------------------------------------------------" << endl;
            cout << "Home Delivery Customer : " << traversal->c.name << endl;
            cout << "Age : " << traversal->c.age << endl;
            cout << "Pizza Name : " << traversal->c.pizzaName << endl;
            cout << "Quantity : " << traversal->c.quantity << endl;
            cout << "Delivery Distance : " << traversal->deliveryCharges << "KM"<<endl;
            cout << "Delivery Charges : " << traversal->distanceDelivery << endl;
            cout << "Bill : " << traversal->c.bill << " RS/_" << endl;
            cout << "Delivery Address : " << traversal->address << endl;
            cout << "-----------------------------------------------------" << endl;

            traversal = traversal->next;
        }
    }
}


void displayAllOrdersDineInCustomers(){
    if (myPizzaShop->nextDineInCustomer == NULL){
        cout << "There is no Order for Dine-In Customer till yet" << endl;
    }

    else{
        dineInCustomer *traversal = myPizzaShop->nextDineInCustomer;
        while (traversal != NULL)
        {
            cout << "-----------------------------------------------------" << endl;
            cout << "Walking Customer : " << traversal->c.name << endl;
            cout << "Age : " << traversal->c.age << endl;
            cout << "Pizza Name : " << traversal->c.pizzaName << endl;
            cout << "Quantity : " << traversal->c.quantity << endl;
            cout << "Bill : " << traversal->c.bill << " RS/_" << endl;
            cout << "-----------------------------------------------------" << endl;

            traversal = traversal->next;
        }
    }
}


void displayAllOrders(){

    cout << "The Take-Away Customers Are :" << endl;
    displayAllOrdersTakeAwayCustomers();

    cout << "The Dine-IN Customers Are :" << endl;
    displayAllOrdersDineInCustomers();

    cout << "The Home Delivery Customers Are :" << endl;
    displayAllOrdersHomeDeliveryCustomers();
}


void totalbillofPendingOrders(){
    takeAwayCustomer *p = myPizzaShop->nextTakeAwayCustomer;
    while(p != NULL){
        takeAway += p->c.bill;
        p = p->next;
    }

    dineInCustomer *q = myPizzaShop->nextDineInCustomer;
    while(q != NULL){
        dineIn += q->c.bill;
        q = q->next;
    }

    homeDeliveryCustomer *r = myPizzaShop->nextHomeDeliveryCustomer;
    while(r != NULL){
        homeDelivery += r->c.bill;
        r = r->next;
    }

    total = takeAway + dineIn + homeDelivery;

    cout << "The total bill of pending orders for Take-Away customers are : " << takeAway << " RS/_" << endl;
    cout << "The total bill of pending orders for Dine-In customers are : " << dineIn << " RS/_" << endl;
    cout << "The total bill of pending orders for Delivery customers are : " << homeDelivery << " RS/_" << endl;
    cout << "The Total orders pending are : " << total << " RS/_" << endl;
}


double totalEarnings(servedCustomer *root){
    if(root){
        totalEarnings(root->left);
        servedTotal += root->bill;
        totalEarnings(root->right);
    }

    return servedTotal;
}


// making a graph for the availabel delivery options

//                           0              1             2        3          4           5
string deliveryPoints[] = {"PizzaSHOP", "Chauburji", "Shadman", "Islampura", "JoharTown", "Anarkali"};

// first value in the pair is vertex and second is the distance (weight) in KM

vector<vector<pair<int, int>>> deliveryMap = {

    // first value in the pair is vertex and second is the distance (weight) in KM
    {{1, 2}, {2, 3}, {3, 5}, {5, 4}}, //  0  (Pizza Shop)
    {{0, 2}, {5, 1}},                 //  1  (Chauburji)
    {{0, 3}, {3, 1}},                 //  2  (Shadman)
    {{0, 5}, {4, 2}, {5, 2}, {2, 1}}, //  3  (Islampura)
    {{3, 2}, {5, 2}},                 //  4  (Johar Town)
    {{0, 4}, {1, 1},{3,2} ,{4, 2}}    //  5  (Anarkali)

};

vector<int> dijkstra(int sourceNode){
    vector<int> distance(6, INT_MAX);
    set<pair<int, int>> s;
    distance[sourceNode] = 0; // Pizza Shop
    s.insert(make_pair(0, sourceNode));

    while (!s.empty()){
        auto top = *(s.begin());
        int u = top.first;  //   current weight
        int v = top.second; //  current vertex

        s.erase(s.begin());

        // traversing the adjacency list of v
        for (auto child : deliveryMap[v]){
            int childVertex = child.first;
            int childWeight = child.second;

            if (u + childWeight < distance[childVertex]){
                distance[childVertex] = u + childWeight;
                s.insert(make_pair(distance[childVertex], childVertex));
            }
        }
    }

    return distance;
}





int main()
{
    // making pizza shop
    myPizzaShop = new pizzaShop;

    // setting the name
    myPizzaShop->shopName = "The Pizza Delight";

    // setting the address
    myPizzaShop->address = "Liberty Chowk, Lahore";

    // Setting the menu
    myPizzaShop->menu = new string[11]{"",
                                       "chickenTikka", "arabicRanch",
                                       "chickenFajita", "cheeseLover",
                                       "chickenSupreme", "allveggie",
                                       "garlicWest", "BeefBold",
                                       "phantom", "mexicanDelight"};

    // setting the price

    myPizzaShop->price = new int[11]{0, 2000, 2500, 2400, 2200, 2700, 2000, 2100, 3000, 3000, 2800};

    int option = -99;

    // now starting the main program
    do
    {

        cout << "-------------------------------------------------------------------------" << endl;
        cout << "---------------------------------" << myPizzaShop->shopName << "-----------------------" << endl;
        cout << "-------------------------------------------------------------------------" << endl;
        cout << "-------------------------------------------------------------------------" << endl;

        cout << "Located at " << myPizzaShop->address << endl;
        cout << "Our Menu is as follows: " << endl;
        for (int i = 1; i <= 10; i++)
        {
            cout << i << ". " << myPizzaShop->menu[i] << " - " << myPizzaShop->price[i] << endl;
        }

        cout << "-------------------------------------------------------------------------" << endl;
        cout << "---------------------------------Operations------------------------------" << endl;
        cout << "-------------------------------------------------------------------------" << endl;
        cout << "-------------------------------------------------------------------------" << endl;

        // Order placing
        cout << "1. Place order for Take-Away Customer" << endl;
        cout << "2. Place order for Home Delivery Customer" << endl;
        cout << "3. Place order for Dine-In Customer" << endl;

        // order serving
        cout << "4. Serve order for Take-Away Customer" << endl;
        cout << "5. Serve order for Home Delivery Customer" << endl;
        cout << "6. Serve order for Dine-In Customer" << endl;
        cout << "7. Serve All Orders " << endl;

        // Displaying orders
        cout << "8. Display all orders of Take-Away Customer" << endl;
        cout << "9. Display all orders of Home Delivery Customers" << endl;
        cout << "10. Display all orders of Dine-In Customers" << endl;
        cout << "11. Display all orders of all Customers" << endl;

        // Served orders
        cout << "12. Display all served Orders" << endl;
        cout << "13. Search Served Orders " << endl;
        cout << "14. Clear the Served Orders List " << endl;
        cout << "15. Display total bill of Pending Orders " << endl;
        cout << "16. Display the total Earnings of Served Orders " << endl;
        cout << "0.  EXIT " << endl;

        cout << "Enter your choice: ";

        cin >> option;

        // for taking input of Customer Details
        int age, quantity, pizzaIndex;
        double bill;
        string address;
        string name;

        switch (option)
        {
        case 1:
        { // placing order for take away customer
            cout << "Enter the name of the customer: ";
            cin >> name;
            cout << "Enter the age of the customer: ";
            cin >> age;
            cout << "Enter the quantity of the pizza: ";
            cin >> quantity;
            cout << "Enter the option for the pizza: ";
            cin >> pizzaIndex;

            bill = quantity * myPizzaShop->price[pizzaIndex];
            placeOrderTakeAwayCustomer(age, name, myPizzaShop->menu[pizzaIndex], quantity, bill);
        }
        break;

        case 2:

        {                                               // placing order for Home Delivery customer
            vector<int> distanceFromShop = dijkstra(0); // As Zero is our Source Node

            int optionDelivery = -999;

            do
            {
                cout << "The delivery is available for following Areas : " << endl;
                for (int i = 1; i <= 5; i++)
                {
                    cout << i << ". " << deliveryPoints[i] << endl;
                }

                cout << "Enter your option :" << endl;
                cin >> optionDelivery;

            } while (!(optionDelivery >= 0 && optionDelivery <= 5));

            // setting the delivery address of the Customer
            address = deliveryPoints[optionDelivery];

            cout << "Enter the name of the customer: ";
            cin >> name;
            cout << "Enter the age of the customer: ";
            cin >> age;
            cout << "Enter the quantity of the pizza: ";
            cin >> quantity;
            cout << "Enter the option for the pizza: ";
            cin >> pizzaIndex;

            int deliveryChargesPerKM = 50;
            int deliveryCharges = deliveryChargesPerKM * distanceFromShop[optionDelivery];
            bill = quantity * myPizzaShop->price[pizzaIndex] + deliveryCharges;

            // distance from the shop
            int distanceFromTheShop = distanceFromShop[optionDelivery];
            placeOrderHomeDeliveryCustomer(age, name, myPizzaShop->menu[pizzaIndex], quantity, bill, address, distanceFromTheShop, deliveryCharges);
        }
        break;

        case 3:
        { // placing order for Dine-in customer

            cout << "Enter the name of the customer: ";
            cin >> name;
            cout << "Enter the age of the customer: ";
            cin >> age;
            cout << "Enter the quantity of the pizza: ";
            cin >> quantity;
            cout << "Enter the option for the pizza: ";
            cin >> pizzaIndex;

            bill = quantity * myPizzaShop->price[pizzaIndex];
            placeOrderDineInCustomer(age, name, myPizzaShop->menu[pizzaIndex], quantity, bill);
        }
        break;

        case 4:
            // serving order for Take Away customer
            serveOrderTakeAwayCustomer();
            break;

        case 5:
            // serving order for Home Delivery customer
            serveOrderHomeDeliveryCustomer();
            break;

        case 6:
            // serving order for Dine-in customer
            serveOrderDineInCustomer();
            break;

        case 7:
            // serving all orders
            serveAllOrders();
            break;

        case 8:
            // displaying all orders of Take-away customers
            displayAllOrdersTakeAwayCustomers();
            break;

        case 9:
            // displaying all orders of Home Delivery customers
            displayAllOrdersHomeDeliveryCustomers();
            break;

        case 10:
            // displaying all orders of Dine-in customers
            displayAllOrdersDineInCustomers();
            break;

        case 11:
            // displaying all orders of all customers
            displayAllOrders();
            break;

        case 12:
        { // displaying all served orders
            servedCustomer *r = displayAllServedOrderes6(root);
            if (!r)
                cout << "No Served Customer yet " << endl;
        }
        break;

        case 13:
        { // searching served orders
            cout << "Enter the name of the customer you want to search: " << endl;
            cin >> name;
            servedCustomer *searchedCustomer = search(root, name);
            if (searchedCustomer == NULL)
                cout << "No such Customer was Served " << endl;
            else
                display(searchedCustomer);
        }
        break;

        case 14:
        { // clearing the served Orders

            deleteAllServedCustomers(root);
            root = NULL;
        }
        break;

        case 15:
        { // pending orders bill in queue for all!

            // resetting the state of total orders
            takeAway = 0, dineIn = 0, homeDelivery = 0, total = 0; 
            totalbillofPendingOrders();
        }
        break;

        case 16:
        { // total earnings from served orders!

        // resetting thr state of total served orders
        servedTotal = 0;
        double totalx = totalEarnings(root);
        cout << "The Total Earnings are : " << totalx << endl;
        }
        break;
        }

    } while (option != 0);

    cout << "Pizza Order Management System -- Terminated" << endl;
    cout << "Thank you for Using our Services " << endl;

    return 0;
}
