// -----------------------------------------------  START ------------------------------------------------ //
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

#include <bits/stdc++.h>
#define ll long long int

using namespace std;

// ORDERDETAILS CLASS ---------------------------------------------------------------------------------------

class orderdetails{
public:

// Attributes

    ll id;
    string name;
    double price;
    ll quantity;

// Display function

    void display() const{
        cout << "Product ID: " << id << endl;
        cout << "Product name: " << name << endl;
        cout << "Price: " << price << endl;
        cout << "Quantity: " << quantity << endl;
        cout << endl;
    }

// Conversion in string for file writing

    string toString() const {
        stringstream ss;
        ss << id << "," << name << "," << price << "," << quantity;
        return ss.str();
    }

};


// PRODUCT CLASS --------------------------------------------------------------------------------------------

class Product {
public:

// Attributes

    ll id;
    string name;
    double price;
    ll stock;

// Display function

    void display() const {
        cout << "Product ID: " << id << endl;
        cout << "Product Name: " << name << endl;
        cout << "Price: " << price << endl;
        cout << "Stock: " << stock << endl;
        cout << endl;
    }

// Conversion in string for file writing

    string toString() const {
        stringstream ss;
        ss << id << "," << name << "," << price << "," << stock;
        return ss.str();
    }
};

// ORDER CLASS ----------------------------------------------------------------------------------------------
class Order {
public:

// Attributes
    ll orderId;
    ll customerId;
    vector<orderdetails> orderdet;

// Display function

    void display() const {
        cout << "Order ID: " << orderId << ", Customer ID: " << customerId << "" << endl;
        cout << endl;
        for (const auto& orderdt : orderdet) {
            orderdt.display();
        }
    }

// Conversion in string for file writing

    string toString() const {
        stringstream ss;
        ss << orderId << "," << customerId << ",";
        for (const auto& orderdt : orderdet) {
            ss << orderdt.id << "," << orderdt.name << ","
               << orderdt.price << "," << orderdt.quantity << "|";
        }
        return ss.str();
    }
};

// function to make sure that you are entering long long 
// in input if u enter any other datatype it's not valid.

ll getValidInteger() {
    ll value;
    while (true) {
        cin >> value;
        if (cin.fail()) {
            cout << "Invalid input. Please try again." << endl;
            cin.clear(); // Clear the error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the input
        } else {
            break;
        }
    }
    return value;
}

// Function for read products from file llo a vector

vector<Product> readProductsFromFile(const string& filename) {

    vector<Product> products;

    ifstream inFile(filename);

    if (!inFile) {
        cerr << "Error in opening file: " << filename << endl;
        return products;
    }

    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        Product product;
        string temp;
        getline(ss, temp, ',');
        product.id = stoi(temp);
        getline(ss, product.name, ',');
        getline(ss, temp, ',');
        product.price = stod(temp);
        getline(ss, temp, ',');
        product.stock = stoi(temp);
        products.push_back(product);
    }
    inFile.close();
    return products;
}

// Function for write product details to file

void writeProductsToFile(const vector<Product>& products, const string& filename) {

    ofstream outFile(filename);

    if (!outFile) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    for (const auto& product : products) {
        outFile << product.toString() << "" << endl;
    }

    outFile.close();
}

// Function to ADD a new product 

void addProduct(vector<Product>& products, const string& filename) {
    Product newProduct;
    cout << "Enter Product ID: ";
    newProduct.id = getValidInteger();
    cin.ignore(); // ignore newline left in stream
    cout << "Enter Product Name: ";
    getline(cin, newProduct.name);
    cout << "Enter Product Price: ";
    newProduct.price = getValidInteger();
    cout << "Enter Product Stock: ";
    newProduct.stock = getValidInteger();

    products.push_back(newProduct);
    writeProductsToFile(products, filename);

    cout << endl;
    cout << "PRODUCT ADDED SUCCESFULLY !!!!" << endl;
    cout << endl;
}

// Function to REMOVE a product by ID

void removeProduct(vector<Product>& products, const string& filename, ll productId) {

    auto it = find_if(products.begin(), products.end(), [productId](const Product& product) {
        return product.id == productId;
    });

    if (it != products.end()) {
        products.erase(it, it+1);
        writeProductsToFile(products, filename);
        cout << endl;
        cout << "PRODUCT REMOVED SUCCESFULLY !!!!" << endl;
    } else {
        cout << "PRODUCT NOT FOUND !!!!" << endl;
    }

    cout << endl;
}

// Function to UPDATE a product information by ID

void updateProduct(vector<Product>& products, const string& filename, ll productId) {

    auto it = find_if(products.begin(), products.end(), [productId](const Product& product) {
        return product.id == productId;
    });

    if (it != products.end()) {
        cout << "Enter new Product Name: ";
        cin.ignore(); // ignore newline left in stream
        getline(cin, it->name);
        cout << "Enter new Product Price: ";
        it -> price = getValidInteger();
        cout << "Enter new Product Stock: ";
        it -> stock = getValidInteger();

        writeProductsToFile(products, filename);
        cout << endl;
        cout << "PRODUCT UPDATED SUCCESFULLY !!!!" << endl;
    } else {
        cout << endl;
        cout << "PRODUCT NOT FOUND !!!!" << endl;
    }

    cout << endl;
}

// Function to view all products in store

void viewProducts(const vector<Product>& products) {
    cout << "Product List:" << endl;
    cout << endl;
    for (const auto& product : products) {
        product.display();
        cout << endl;
    }
}

// Function for read orders from file llo a vector

vector<Order> readOrdersFromFile(const string& filename) {

    vector<Order> orders;

    ifstream inFile(filename);

    if (!inFile) {
        cerr << "Error opening file: " << filename << endl;
        return orders;
    }

    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        Order order;
        string temp;
        getline(ss, temp, ',');
        order.orderId = stoi(temp);
        getline(ss, temp, ',');
        order.customerId = stoi(temp);
        while (getline(ss, temp, '|')) {
            stringstream productStream(temp);
            orderdetails orderdt;
            getline(productStream, temp, ',');
            orderdt.id = stoi(temp);
            getline(productStream, orderdt.name, ',');
            getline(productStream, temp, ',');
            orderdt.price = stod(temp);
            getline(productStream, temp, ',');
            orderdt.quantity = stoi(temp);
            order.orderdet.push_back(orderdt);
        }
        orders.push_back(order);
    }

    inFile.close();
    return orders;
}

//write orders to file

void writeOrdersToFile(const vector<Order>& orders, const string& filename) {

    ofstream outFile(filename);

    if (!outFile) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    for (const auto& order : orders) {
        outFile << order.toString() << "" << endl;
    }

    outFile.close();
}

// Function to display all orders

void viewOrders(const vector<Order>& orders) {
    cout << "Order List:" << endl;
    cout << endl; cout << endl;
    for (const auto& order : orders) {
        order.display();
        cout << endl;
    }
    cout << endl;
}

// Function to calculate sell amount and sell quantity

void checkAmounts(const vector<Order>& orders, const vector<Product>& products) {
    double totalAmount = 0.0;
    ll quant = 0;
    
    for (const auto& order : orders) {
        for (const auto& orderdt : order.orderdet) {
                totalAmount += (orderdt.price * orderdt.quantity); // Assuming Amount calculation based on product price and remaining stock
                quant += (orderdt.quantity);
            }
    }
    cout << "Quantity Sold : ---- > " << quant << endl;
    cout << "Amount : ----------- > " << totalAmount << endl;
    cout << endl;
}

// Function to handle online shopping Process

void onlineShopping(ll cid, vector<Product>& products, vector<Order>& orders) {

    Order newOrder;
    const string ordersFile = "orders.txt";
    const string productsFile = "products.txt";

    srand(time(0));
    ll orderIdCounter = rand(); // Static variable to track order IDs

    // Assigning new order ID
    newOrder.orderId = orderIdCounter;
    
    newOrder.customerId = cid;

    string productName;
    ll quantity;
    char choice;

    do {
        cout << "Enter Product Name: ";
        getline(cin, productName);

        auto product = find_if(products.begin(), products.end(), [&productName](const Product& p) {
            return p.name == productName;
        });

        if (product != products.end()) {
            cout << "Enter Quantity: ";
            quantity = getValidInteger();

            if (quantity <= product->stock) {
                // Update product stock
                product->stock -= quantity;

                // Add product to order
                orderdetails ordertemp;
                ordertemp.quantity = quantity; 
                ordertemp.id = product -> id; 
                ordertemp.name = product -> name;
                ordertemp.price = product -> price;  
                newOrder.orderdet.push_back(ordertemp);

                cout << "PRODUCT ADDED TO CART !!! CONTINUE SHOPPING !!" << endl;
                cout << endl;
            } else {
                cout << "INSUFFICIENT STOCK !!!" << endl;
                cout << endl;
            }
        } else {
            cout << "PRODUCT NOT FOUND !!!!" << endl;
            cout << endl;
        }

        cout << "Want to add another product? (y/n (anything other than y or Y is counted as n)): ";
        cin >> choice;
        cin.ignore(); // ignore newline left in stream
    } while (choice == 'y' || choice == 'Y');

    // Prll the bill 
     cout << endl;
     cout << " -------------  BILL  ------------------- " <<  endl;
     cout << endl; cout << endl;

     cout << "ORDER ID ----------> " << newOrder.orderId <<  endl;
     cout << "CUSTOMER ID -------> " << newOrder.customerId <<  endl;
     cout << endl; cout << endl;

    double totalamount = 0.0;

    for(const auto& orderd : newOrder.orderdet){
         cout << "Product ID: " << orderd.id << endl;
         cout << "Product Name: " << orderd.name << endl;
         cout << "Price: " << orderd.price << endl;
         cout << "Quantity: " << orderd.quantity << endl;
    
        totalamount += (orderd.price * orderd.quantity);
    }

    cout << endl; cout << endl;

    cout << "PAY -------- > " << totalamount << endl; 
    cout << endl; cout << endl;

     cout << " --------------  BILL ------------------- " <<  endl;

    // Add order to orders vector
    orders.push_back(newOrder);

    // update orderfile and productfile
    writeOrdersToFile(orders, ordersFile);
    writeProductsToFile(products, productsFile);

    cout << "ORDER PLACED SUCCESFULLY !!!!" << endl;
    cout << endl;
}

// Function to check product availability

void checkavailability(const vector<Product>& products) {

    string productName;
    cout << "Enter the product name to check availability (type DONE to exit): ";

    while (true) {
        getline(cin, productName);
        if (productName == "DONE") break;

        bool productFound = false;
        for (const auto& product : products) {
            if (product.name == productName) {
                cout << "Product ID: " << product.id << "" << endl;
                cout << "Name: " << product.name << "" << endl;
                cout << "Price: " << product.price << "" << endl;
                cout << "Stock: " << product.stock << "" << endl;
                productFound = true;
                break;
            }
        }
        if (!productFound) {
            cout << "PRODUCT NOT AVAILABLE !!!!" << endl;
        }
        cout << "Enter the product name to check availability (type DONE to exit): ";
    }
}

// function to analyse sale of store

void salesanalysis(const vector<Order> &orderd, 
                   const vector<Product> &products){

    unordered_map<string, ll> m;

    for(const auto& order:orderd){
        for(const auto& o:order.orderdet){
        if(m.find(o.name) == m.end()){
            m[o.name] = o.quantity;
        }
        else{
            m[o.name] += o.quantity;
        }
    }
    }

    priority_queue<pair<ll, string>> pq;

    for(auto i:m){
        pq.push({i.second, i.first});
    }

    while(!pq.empty()){
        pair<ll, string> p = pq.top();
        pq.pop();

        string productName = p.second;

        for (const auto& product : products) {
            if (product.name == productName) {
                cout << "Product ID: " << product.id << "" << endl;
                cout << "Name: " << product.name << "" << endl;
                cout << "Price: " << product.price << "" << endl;
                cout << "Stock: " << product.stock << "" << endl;
                cout << "Quantity sold: " << p.first << "" << endl;
                cout << endl;
                break;
            }
        }
        
    }

}

// function to cancel the order

void cancelorder(vector<Order>& orders, const string& filename1, ll orderid,
                vector<Product>& products, const string& filename2){

    auto it = find_if(orders.begin(), orders.end(), [&orderid](const Order& order) {
        return order.orderId == orderid;
    });

    if (it != orders.end()) {
        // Update product stock
        for (const auto& orderDetail : it->orderdet) {
            ll pid = orderDetail.id;
            ll quantity = orderDetail.quantity;

            auto productIt = find_if(products.begin(), products.end(), [&pid](const Product& product) {
                return product.id == pid;
            });

            if (productIt != products.end()) {
                productIt->stock += quantity;
            }
    }

        // Remove the order from the vector
        orders.erase(it);

        writeOrdersToFile(orders, filename1);
        writeProductsToFile(products, filename2);
        cout << "Order cancelled !!" << endl;
    }

    else{
        cout << "Order not found !!" << endl;
    }

    cout << endl;

}

// function to find order histoty of particular customer

void orderhistory(ll cid, vector<Order> &orders){

    cout << endl;
    bool flag = 0;
    for(const auto& o:orders){
        if(o.customerId == cid){
            flag = 1;
            cout << "Order Id: " << o.orderId << "  - - - - - - - - - - - - - -" << endl;
            cout << endl;
            
            for(auto& i:o.orderdet){
                cout << "Product Id: " << i.id << endl;
                cout << "Product Name: " << i.name << endl;
                cout << "Price: " << i.price << endl;
                cout << "Quantity: " << i.quantity << endl;
                cout << endl;
            }
        }
    }
    if(!flag){
        cout << "NO RECORDS AVAILABLE WITH CUSTOMER ID = " << cid << endl;
        cout << endl;
    }

}

vector<pair<ll, string>> readrecords(const string& filename){

    ifstream inFile(filename);
    vector<pair<ll, string>> ans;

    if (!inFile) {
        cerr << "Error in opening file: " << filename << endl;
        return ans;
    }

    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        pair<ll, string> temp2;
        string temp;
        getline(ss, temp, ',');
        temp2.first = stoi(temp);
        getline(ss, temp2.second, ',');
        ans.push_back(temp2);
    }
    inFile.close();
    return ans;
}

ll login(){

    ll id;
    string pass;
    cout << "Enter customer ID: ";
    id = getValidInteger();
    cin.ignore();
    cout << endl;
    
    cout << "Enter Password: ";
    getline(cin, pass);

    vector<pair<ll, string>> vec = readrecords("records.txt");
    
    for(auto i:vec){
        if((i.first == id) && (i.second == pass)){
            return id;
        }
    }
    
    cout << "WRONG ID OR PASSWORD !! TRY AGIAN !!" << endl;
    cout << endl;
    return -1;

}

ll reg(){

    srand(time(0));
    ll id;
    id = rand();
    cout << "Your id for registration is -> " << id << endl;

    string pass;
    cout << "Enter password: ";
    cin >> pass;
    cin.ignore();

    ofstream out("records.txt", ios::app);

    if(!out){
        cerr << "Error in opening file records.txt" << endl;
        return -1;
    }

    out << to_string(id) << "," << pass << endl;
    //system("cls");
    out.close();

    cout << endl;
    cout << "Registration Done !!!" << endl;
    cout << "ID : " << id << endl;
    cout << "Password: " << pass << endl;
    cout << endl;

    return id;

}


// Main function for Customer section

int customerMain() {

    string in;
    ll id = -1;
    cout << "1. Login " << endl;
    cout << "2. Register" << endl;
    cout << endl;
    cout << "Enter your choice: ";
    cin >> in;
    cout << endl;

    if(in == "1") id = login();
    else if(in == "2") id = reg();
    else {
        cout << "Choose 1 for login OR 2 for registration !!" << endl;
        cout << endl;
    }

    if(id != -1){

    const string productsFile = "products.txt";
    const string ordersFile = "orders.txt";

    vector<Product> products = readProductsFromFile(productsFile);
    vector<Order> orders = readOrdersFromFile(ordersFile);

    ll choice;
    do {
        cout << endl;
        cout << "------------------ "<< "Customer Menu" << " ------------------" << endl;
        cout << endl;
        cout << "1. Shopping" << endl;
        cout << "2. check product availability" << endl;
        cout << "3. cancel order" << endl;
        cout << "4. view orders" << endl;
        cout << "5. Exit" << endl;
        cout << endl;
        cout << "Enter your choice: ";
        choice = getValidInteger();
        cin.ignore();
        cout << endl;

        switch (choice) {

            case 1:
                    
                    onlineShopping(id, products, orders);

                break;
            case 2:
                
                    checkavailability(products);
            
                break;
            case 3:

                    ll orderid;
                    cout << "Enter order ID to REMOVE: "; 
                    orderid = getValidInteger();
                    cancelorder(orders, ordersFile, orderid, products, productsFile);
                
                break;

            case 4:
                
                    orderhistory(id, orders);

                break;

            case 5:
                cout << "Exiting Customer section." << endl;
                cout << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                cout << endl;
                break;
        }
    } while (choice != 5);
    }

    else{
        cout << "LOGIN OR REGISTER FIRST !!!!" << endl;
        cout << endl;
        return customerMain();
    }

    return 0;
}

// Main function for admin section

int adminMain() {
    const string productsFile = "products.txt";
    const string ordersFile = "orders.txt";

    vector<Product> products = readProductsFromFile(productsFile);
    vector<Order> orders = readOrdersFromFile(ordersFile);

    ll choice;
    do {
        cout << "------------------ "<< "Admin Menu" << " ------------------" << endl;
        cout << "1. Add Products" << endl;
        cout << "2. Remove Products" << endl;
        cout << "3. Update Products" << endl;
        cout << "4. View Products" << endl;
        cout << "5. View Orders" << endl;
        cout << "6. Check Amounts" << endl;
        cout << "7. SalesAnalysis" << endl;
        cout << "8. Exit" << endl;
        cout << endl;
        cout << "Enter your choice: ";
        choice = getValidInteger();
        cout << endl;

        switch (choice) {
            case 1: {
                addProduct(products, productsFile);
                break;
            }
            case 2: {
                ll productId;
                cout << "Enter Product ID to REMOVE: ";
                productId = getValidInteger();
                removeProduct(products, productsFile, productId);
                break;
            }
            case 3: {
                ll productId;
                cout << "Enter Product ID to UPDATE: ";
                productId = getValidInteger();
                updateProduct(products, productsFile, productId);
                break;
            }
            case 4: {
                viewProducts(products);
                break;
            }

            case 5: {
                viewOrders(orders);
                break;
            }

            case 6: {
                checkAmounts(orders, products);
                break;
            }

            case 7: {
                salesanalysis(orders, products);
                break;
            }

            case 8: {
                cout << "Exiting Admin section." << endl;
                cout << endl;
                break;
            }
            default: {
                cout << "Invalid choice. Please try again." << endl;
                break;
            }
        }
    } while (choice != 8);

    return 0;
}

// Main function to start the program

int main() {
    cout << endl;
    cout << "WELCOME TO STORE MANAGEMENT AND SHOPPING SYSTEM !!!" << endl;
    cout << endl;
    cout << "1. Admin Section" << endl;
    cout << "2. Customer Section" << endl;
    cout << "3. Exit" << endl;
    cout << endl;
    ll choice;
    cout << "Enter your choice: ";
    choice = getValidInteger();
    cout << endl;

    switch (choice) {
        case 1:
            cout << "Entering Admin Section" << endl;
            cout << endl;
            return adminMain();
        case 2:
            cout << "Entering Customer Section" << endl;
            cout << endl;
            return customerMain();
        case 3:
            cout << "Exiting Program" << endl;
            cout << endl;
            return 0;
        default:
            cout << "Invalid choice. Exiting Program" << endl;
            cout << endl;
            return 1;
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //
// -----------------------------------------------  END -------------------------------------------------- //