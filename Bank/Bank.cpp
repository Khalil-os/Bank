#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

// Important : ( User : Admin / Password : 1234 )

enum enChoose {
    Show_Client_List = 1,
    Add_New_Client = 2,
    Delete_Client = 3,
    Update_Clinet_Info = 4,
    Find_Client = 5,
    Transactions = 6,
    Manage_Users = 7,
    Logout = 8
};

enum enTransactions {
    Deposit = 1,
    Withraw = 2,
    Total_Balances = 3,
    Main_Menue = 4
};

enum enManage_Users {
    List_Users = 1,
    Add_Users = 2,
    Delete_Users = 3,
    Update_Users = 4,
    Find_Users = 5,
    Main_menue = 6
};

enum enPermession {
    eAll = -1,
    eList_Client = 1,
    eAdd_Client = 2,
    eDelete_Client = 4,
    eUpdate_Client = 8,
    eFind_Client = 16,
    eTranaction = 32,
    eManagerUsers = 64
};

struct sClient {
    string Accont_Number;
    string Pincode;
    string Name;
    string Phone;
    double Accont_Balance;
};

struct stUser {
    string UserName;
    string Password;
    int Permissions;
};

bool Invalid_User = false;

stUser User;

bool CheckNumber(short Number ,short from, short to) {
    if (Number >= from && Number <= to) {
        return false;
    }
    return true;
}

bool CheckAccessPermision(enPermession Permission) {

    enPermession User_Permission = (enPermession)User.Permissions;
    if (User_Permission == enPermession::eAll)
        return true;
    if ((User_Permission & Permission) == Permission)
        return true;
    return false;

}

short PrintMenueScreen() {

    short Choose;
    cout << "====================================================\n";
    cout << "\t\t" << "Main Menue Screen" << endl;
    cout << "====================================================\n";
    cout << "\t" << "[1] Show Client List" << endl;
    cout << "\t" << "[2] Add New Client" << endl;
    cout << "\t" << "[3] Delete Client" << endl;
    cout << "\t" << "[4] Update Client Info" << endl;
    cout << "\t" << "[5] Find Client" << endl;
    cout << "\t" << "[6] Transactions" << endl;
    cout << "\t" << "[7] Manage Users" << endl;
    cout << "\t" << "[8] Logout" << endl;
    cout << "====================================================\n";
    cout << "Choose what do you want to do ? [1 ato 8] : ";
    cin >> Choose;
    while (CheckNumber(Choose,1,8))
    {
        cout << "\ninvalid fonction !!!!!\n\n";
        cout << "please choose another number [1 to 8] : ";
        cin >> Choose;

    }
    return Choose;

}

short PrintTransactionsScreen() {

    short Choose;
    cout << "====================================================\n";
    cout << "\t\t" << "Transactions Menue Screen" << endl;
    cout << "====================================================\n";
    cout << "\t" << "[1] Deposit" << endl;
    cout << "\t" << "[2] Withraw" << endl;
    cout << "\t" << "[3] Total Balances" << endl;
    cout << "\t" << "[4] Main Menue" << endl;
    cout << "====================================================\n";
    cout << "Choose what do you want to do ? [1 ato 4] : ";
    cin >> Choose;
    while (CheckNumber(Choose, 1, 4))
    {
        cout << "invalid fonction !!!!!\n\n";
        cout << "please choose another number [1 to 4] : ";
        cin >> Choose;

    }
    return Choose;

}

short PrintMenage_UsersScreen() {

    short Choose;
    cout << "====================================================\n";
    cout << "\t\t" << "Menager User Menue Screen" << endl;
    cout << "====================================================\n";
    cout << "\t" << "[1] List Users" << endl;
    cout << "\t" << "[2] Add Users" << endl;
    cout << "\t" << "[3] Delete Users" << endl;
    cout << "\t" << "[4] Update Users" << endl;
    cout << "\t" << "[5] Find Users" << endl;
    cout << "\t" << "[6] Main Menue" << endl;
    cout << "====================================================\n";
    cout << "Choose what do you want to do ? [1 ato 6] : ";
    cin >> Choose;
    while (CheckNumber(Choose, 1, 6))
    {
        cout << "invalid fonction !!!!!\n\n";
        cout << "please choose another number [1 to 6] : ";
        cin >> Choose;

    }
    return Choose;

}

void ShowChoose(short choose);

void ShowChooseTransactions(short choose);

void ShowChooseManage_Users(short choose);

vector <string> Split(string sentence, string Delim = " ") {

    vector <string> vSentence;
    short pos = 0;
    string s;
    while ((pos = sentence.find(Delim)) != std::string::npos) {
        s = sentence.substr(0, pos);
        if (s != "") {
            vSentence.push_back(s);
        }
        sentence.erase(0, pos + Delim.length());
    }
    if (sentence != "") {
        vSentence.push_back(sentence);
    }
    return vSentence;
}

void ReturnOfHomeScreen() {
    cout << endl << endl;
    system("pause");
    system("cls");
    ShowChoose(PrintMenueScreen());
}

sClient ReadClient(vector <sClient> vClients) {
    sClient Client;
    short num = 0;
    cout << "Enter Accont Number : ";
    getline(cin >> ws, Client.Accont_Number);
    cout << endl;
    for (const sClient& C : vClients) {
        if (C.Accont_Number != Client.Accont_Number) {
            num++;
        }
    }
    if (num != vClients.size()) {
        cout << "This Account Number is ready used please enter another one ! " << endl << endl;
        return ReadClient(vClients);
    }
    cout << "Enter PinCode : ";
    getline(cin >> ws, Client.Pincode);
    cout << endl;
    cout << "Enter Name : ";
    getline(cin, Client.Name);
    cout << endl;
    cout << "Enter Phone : ";
    getline(cin, Client.Phone);
    cout << endl;
    cout << "Enter Accont Balance : ";
    cin >> Client.Accont_Balance;
    cout << endl;
    return Client;
}

stUser ReadUser(vector <stUser> vUser) {

    stUser User;
    short num = 0;
    char Permissions[8];
    cout << "Enter Username : ";
    getline(cin >> ws, User.UserName);
    cout << endl;
    for (const stUser& C : vUser) {
        if (C.UserName != User.UserName) {
            num++;
        }
    }
    if (num != vUser.size()) {
        cout << "This Account Number is ready used please enter another one ! " << endl << endl;
        return ReadUser(vUser);
    }
    cout << "Enter Password : ";
    getline(cin >> ws, User.Password);
    cout << endl;

    cout << "Do you want to give full access ( y / n ) : ";
    cin >> Permissions[7];
    cout << endl;
    if (Permissions[7] == 'n') {
        cout << "Do you want to give access to : " << endl << endl;
        cout << "Show Client List ( y / n ) : ";
        cin >> Permissions[0];
        cout << endl << endl;
        cout << "Add New Client ( y / n ) : ";
        cin >> Permissions[1];
        cout << endl << endl;
        cout << "Delete Client ( y / n ) : ";
        cin >> Permissions[2];
        cout << endl << endl;
        cout << "Update Client ( y / n ) : ";
        cin >> Permissions[3];
        cout << endl << endl;
        cout << "Find Client ( y / n ) : ";
        cin >> Permissions[4];
        cout << endl << endl;
        cout << "Transactions ( y / n ) : ";
        cin >> Permissions[5];
        cout << endl << endl;
        cout << "Maneger Users ( y / n ) : ";
        cin >> Permissions[6];
        cout << endl << endl;
        User.Permissions = 0;
        for (int i = 1; i < 8; i++) {
            if (Permissions[i-1] == 'y') {
                User.Permissions += pow(2, i - 1);
            }
        }
    }
    else
        User.Permissions = -1;

    return User;
   
}

sClient UpClient(sClient Client) {
    cout << "Enter PinCode : ";
    getline(cin >> ws, Client.Pincode);
    cout << endl;
    cout << "Enter Name : ";
    getline(cin, Client.Name);
    cout << endl;
    cout << "Enter Phone : ";
    getline(cin, Client.Phone);
    cout << endl;
    cout << "Enter Accont Balance : ";
    cin >> Client.Accont_Balance;
    cout << endl;
    return Client;
}

stUser UpUser(stUser User) {
    char Permissions[8];

    cout << "Enter Password : ";
    getline(cin >> ws, User.Password);
    cout << endl;
    cout << "Do you want to give full access ( y / n ) : ";
    cin >> Permissions[7];
    cout << endl;
    if (Permissions[7] == 'n') {
        cout << "Do you want to give access to : " << endl << endl;
        cout << "Show Client List ( y / n ) : ";
        cin >> Permissions[0];
        cout << endl << endl;
        cout << "Add New Client ( y / n ) : ";
        cin >> Permissions[1];
        cout << endl << endl;
        cout << "Delete Client ( y / n ) : ";
        cin >> Permissions[2];
        cout << endl << endl;
        cout << "Update Client ( y / n ) : ";
        cin >> Permissions[3];
        cout << endl << endl;
        cout << "Find Client ( y / n ) : ";
        cin >> Permissions[4];
        cout << endl << endl;
        cout << "Transactions ( y / n ) : ";
        cin >> Permissions[5];
        cout << endl << endl;
        cout << "Maneger Users ( y / n ) : ";
        cin >> Permissions[6];
        cout << endl << endl;
        User.Permissions = 0;
        for (int i = 1; i < 8; i++) {
            if (Permissions[i - 1] == 'y') {
                User.Permissions += pow(2, i - 1);
            }
        }
    }
    else
        User.Permissions = -1;

    return User;

}

void PrintClientRecord(sClient Client) {
    cout << "\n\nThe following are the extracted client details:\n";
    cout << "----------------------------------------------------";
    cout << "\nAccout Number  : " << Client.Accont_Number;
    cout << "\nPin Code       : " << Client.Pincode;
    cout << "\nName           : " << Client.Name;
    cout << "\nPhone          : " << Client.Phone;
    cout << "\nAccount Balance: " << Client.Accont_Balance;
    cout << "\n----------------------------------------------------\n";

}

void PrintUserRecord(stUser User) {

    cout << "\n\nThe following are the extracted User details:\n";
    cout << "----------------------------------------------------";
    cout << "\nAccout Number  : " << User.UserName;
    cout << "\nPin Code       : " << User.Password;
    cout << "\nName           : " << User.Permissions;
    cout << "\n----------------------------------------------------\n";

}

sClient PrintInformationOfClient(string information, string seperatore = "#//#") {
    sClient Client;
    string s = "";
    vector <string> vClient = Split(information, seperatore);
    Client.Accont_Number = vClient.at(0);
    Client.Pincode = vClient.at(1);
    Client.Name = vClient.at(2);
    Client.Phone = vClient.at(3);
    Client.Accont_Balance = stod(vClient.at(4));
    return Client;
}

stUser PrintInformationOfUser(string information, string seperatore = "#//#") {
    stUser User;
    string s = "";
    vector <string> vClient = Split(information, seperatore);
    User.UserName = vClient.at(0);
    User.Password = vClient.at(1);
    User.Permissions = stoi(vClient.at(2));
    return User;
}

void PrintClientInformation(sClient Client) {

    cout << "| " << setw(15) << left << Client.Accont_Number;
    cout << "| " << setw(10) << left << Client.Pincode;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.Accont_Balance;

}

vector <sClient> GetinformationForFileToVector(string NameFile = "MyFile") {

    fstream MyFile;
    vector <sClient> vInformation;
    MyFile.open(NameFile + ".txt", ios::in);
    if (MyFile.is_open()) {
        string Line;
        sClient Client;
        while (getline(MyFile, Line)) {
            if (!Line.empty()) {

                Client = PrintInformationOfClient(Line);
                vInformation.push_back(Client);

            }
        }
        MyFile.close();
    }
    return vInformation;
}

vector <string> GetinformationForFileToVector_string(string NameFile = "MyFile") {

    fstream MyFile;
    vector <string> vInformation;
    MyFile.open(NameFile + ".txt", ios::in);
    if (MyFile.is_open()) {
        string Line;
        while (getline(MyFile, Line)) {
            if (!Line.empty()) {
                vInformation.push_back(Line);
            }
        }
        MyFile.close();
    }
    return vInformation;
}

string PrintInformationOfClient(sClient Client, string seperatore = "#//#") {
    string s = "";
    s += Client.Accont_Number + seperatore + Client.Pincode + seperatore + Client.Name + seperatore + Client.Phone + seperatore + to_string(Client.Accont_Balance);
    return s;
}

string PrintInformationOfUser(stUser User, string seperatore = "#//#") {
    string s = "";
    s += User.UserName + seperatore + User.Password + seperatore + to_string(User.Permissions);
    return s;
}

vector <sClient> GetinformationFromFileToVector(string NameFile = "MyFile") {

    fstream MyFile;
    vector <sClient> vInformation;
    MyFile.open(NameFile + ".txt", ios::in);
    if (MyFile.is_open()) {
        string Line;
        sClient Client;
        while (getline(MyFile, Line)) {
            if (!Line.empty()) {

                Client = PrintInformationOfClient(Line);
                vInformation.push_back(Client);

            }
        }
        MyFile.close();
    }
    return vInformation;
}

vector <stUser> GetinformationFromFileUsersToVector(string NameFile = "MyFile") {

    fstream MyFile;
    vector <stUser> vInformation;
    MyFile.open(NameFile + ".txt", ios::in);
    if (MyFile.is_open()) {
        string Line;
        stUser User;
        while (getline(MyFile, Line)) {
            if (!Line.empty()) {

                User = PrintInformationOfUser(Line);
                vInformation.push_back(User);

            }
        }
        MyFile.close();
    }
    return vInformation;
}

bool SerchAccountNumber(string AccountNumber , string NameFile , sClient& Client) {

    short num = 0;
    vector <sClient> vClient = GetinformationForFileToVector(NameFile);
    for (sClient C : vClient) {
        if (C.Accont_Number == AccountNumber) {
            Client = C;
            return true;
        }
    }
    return false;
}

bool SerchUserName(string UserName, string NameFile, stUser& User) {

    short num = 0;
    vector <stUser> vUser = GetinformationFromFileUsersToVector(NameFile);
    for (stUser C : vUser) {
        if (C.UserName == UserName) {
            User = C;
            return true;
        }
    }
    return false;
}

void SaveInformationFromvectorInFile(vector <string> vClient, string NameFile = "MyFile") {
    fstream MyFile;
    MyFile.open(NameFile + ".txt", ios::out);
    if (MyFile.is_open()) {
        for (string& i : vClient) {
            if (i != "") {
                MyFile << i << endl;
            }
        }
        MyFile.close();
    }
}

void DeleteClient(vector <string> vClient, sClient Client , string NameFile = "MyFile") {
    string s = PrintInformationOfClient(Client);
    char del;
    cout << "\n\nAre you sure you want delete this client ? ( Y / N ) : ";
    cin >> del;
    cout << endl;
    if (del == 'Y' || del == 'y') {
        for (string& C : vClient) {
            if (C == s) {
                C = "";
            }
        }
        SaveInformationFromvectorInFile(vClient , NameFile);
        cout << "\nClient Deleted Successfully .\n";
    }
}

void DeleteUser(vector <string> vUser, stUser User, string NameFile = "MyFile") {

        string s = PrintInformationOfUser(User);
        char del;
        cout << "\n\nAre you sure you want delete this User ? ( Y / N ) : ";
        cin >> del;
        cout << endl;
        if (del == 'Y' || del == 'y') {
            for (string& C : vUser) {
                if (C == s) {
                    C = "";
                }
            }
            SaveInformationFromvectorInFile(vUser, NameFile);
            cout << "\nUser Deleted Successfully .\n";
        }
}

void UpdateClient(vector <string> vClient, sClient Client , string NameFile = "MyFile") {
    string s = PrintInformationOfClient(Client);
    char Up;
    cout << "\n\nAre you sure you want Update this client ? ( Y / N ) : ";
    cin >> Up;
    cout << endl;
    if (Up == 'Y' || Up == 'y') {
        for (string& C : vClient) {
            if (C == s) {
                Client = UpClient(Client);
                s = PrintInformationOfClient(Client);
                C = s;
            }
        }
        SaveInformationFromvectorInFile(vClient,NameFile);
        cout << "\nClient Updated Successfully .\n";
    }
}

void UpdateUser(vector <string> vUser, stUser User, string NameFile = "MyFile") {
    string s = PrintInformationOfUser(User);
    char Up;
    cout << "\n\nAre you sure you want Update this User ? ( Y / N ) : ";
    cin >> Up;
    cout << endl;
    if (Up == 'Y' || Up == 'y') {
        for (string& C : vUser) {
            if (C == s) {
                User = UpUser(User);
                s = PrintInformationOfUser(User);
                C = s;
            }
        }
        SaveInformationFromvectorInFile(vUser, NameFile);
        cout << "\nUser Updated Successfully .\n";
    }
}

void PrintInformationFromFile(vector <sClient> vInformation) {
    cout << "\n\t\t\t\t\tClient List (" << vInformation.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    for (sClient Client : vInformation) {
        PrintClientInformation(Client);
        cout << endl;
    }
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}

string ReadAccountNumber() {
    string AccountNumber;
    cout << "Please enter AccountNumber : ";
    cin >> AccountNumber;
    cout << endl;
    return AccountNumber;
}

string ReadUserName() {
    string UserName;
    cout << "Please enter UserName : ";
    cin >> UserName;
    cout << endl;
    return UserName;
}

void SaveInformationInFile(string NameFile = "MyFile") {

    fstream MyFile;
    char ret;
    string s;
    sClient Client;
    do
    {
        cout << "Adding New Client : \n\n";
        Client = ReadClient(GetinformationForFileToVector("Client"));
        s = PrintInformationOfClient(Client);
        MyFile.open(NameFile + ".txt", ios::app | ios::out);
        if (MyFile.is_open()) {
            MyFile << s << endl;
            MyFile.close();
        }
        cout << endl << "Client Added Successfully, do you want to add more clients ( Y / N ) :  ";
        cin >> ret;
        cout << endl ;
    } while (ret == 'y' || ret == 'Y');
}

void AddNewUser(string NameFile = "MyFile") {

    fstream MyFile;
    char ret;
    string s;
    stUser User;
    do
    {
        cout << "Adding New User : \n\n";
        User = ReadUser(GetinformationFromFileUsersToVector("Users"));
        s = PrintInformationOfUser(User);
        MyFile.open(NameFile + ".txt", ios::app | ios::out);
        if (MyFile.is_open()) {
            MyFile << s << endl;
            MyFile.close();
        }
        cout << endl << "User Added Successfully, do you want to add more Users ( Y / N ) :  ";
        cin >> ret;
        cout << endl;
    } while (ret == 'y' || ret == 'Y');
}

void DepositMany(vector <string> vClient, sClient Client, string NameFile = "MyFile") {

    string s = PrintInformationOfClient(Client);
    int Number;
    char tr;
    cout << "\n\nPlease enter deposit amount : ";
    cin >> Number;
    cout << "\n\nAre you sure you want perfrom this transaction ? ( Y / N ) : ";
    cin >> tr;
    cout << endl;
    if (tr == 'Y' || tr == 'y') {
        for (string& C : vClient) {
            if (C == s) {
                Client.Accont_Balance += Number;
                s = PrintInformationOfClient(Client);
                C = s;
            }
        }
        SaveInformationFromvectorInFile(vClient, NameFile);
        cout << "\nDone Successfully new Balance (" << Client.Accont_Balance << ") .\n";
    }

}

void WithdrawMany(vector <string> vClient, sClient Client, string NameFile = "MyFile") {

    string s = PrintInformationOfClient(Client);
    int Number;
    char tr;
    cout << "\n\nPlease enter deposit amount : ";
    cin >> Number;
    cout << endl;
    while (Number > Client.Accont_Balance) {
        cout << "\nAmount Exceeds the balance, you can withdraw up to : " << Client.Accont_Balance << endl;
        cout << "Please enter another amount : ";
        cin >> Number;
    }
    cout << "\n\nAre you sure you want perfrom this transaction ? ( Y / N ) : ";
    cin >> tr;
    cout << endl;
    if (tr == 'Y' || tr == 'y') {
        for (string& C : vClient) {
            if (C == s) {
                Client.Accont_Balance -= Number;
                s = PrintInformationOfClient(Client);
                C = s;
            }
        }
        SaveInformationFromvectorInFile(vClient, NameFile);
        cout << "\nDone Successfully new Balance (" << Client.Accont_Balance << ") .\n";
    }

}

void PrintClientInformationBalance(sClient Client , int& Number) {

    cout << "| " << setw(15) << left << Client.Accont_Number;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Accont_Balance;
    Number += Client.Accont_Balance;

}

void PrintUserInformationBalance(stUser User) {

    cout << "| " << setw(15) << left << User.UserName;
    cout << "| " << setw(40) << left << User.Password;
    cout << "| " << setw(12) << left << User.Permissions;

}

void ReturnOfTransactionsScreen() {
    cout << endl << endl;
    system("pause");
    system("cls");
    ShowChooseTransactions(PrintTransactionsScreen());
}

void ReturnOfManage_UersScreen() {
    cout << endl << endl;
    system("pause");
    system("cls");
    ShowChooseManage_Users(PrintMenage_UsersScreen());
}

void PrintTotal_Balance(vector <sClient> vInformation) {

    int Total = 0;
    cout << "\n\t\t\t\t\tBalances List (" << vInformation.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    for (sClient Client : vInformation) {
        PrintClientInformationBalance(Client , Total);
        cout << endl;
    }
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "\t\t\t\t\tTotal Balances = " << Total << endl;

}

void PrintUserList(vector <stUser> vInformation) {

    cout << "\n\t\t\t\t\tUsers List (" << vInformation.size() << ") Users(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "UserName";
    cout << "| " << left << setw(40) << "Password";
    cout << "| " << left << setw(12) << "Permission";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    for (stUser User : vInformation) {
        PrintUserInformationBalance(User);
        cout << endl;
    }
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

}

void SerchAccountNumber(string AccountNumber, string NameFile = "MyFile", short num = 0) {

    sClient Client;
    fstream MyFile;
    vector <string> vClient = GetinformationForFileToVector_string(NameFile);
    if (SerchAccountNumber(AccountNumber, NameFile , Client)) {
        PrintClientRecord(Client);
        if (num == 1) {
            DeleteClient(vClient, Client , NameFile);
        }
        else if (num == 2) {
            UpdateClient(vClient, Client, NameFile);
        }
        else if (num == 3) {
            DepositMany(vClient, Client, NameFile);
        }
        else if (num == 4) {
            WithdrawMany(vClient, Client, NameFile);
        }
    }
    else
    {
        cout << "Client with Account Number (" << AccountNumber << ") Not Found !\n";
    }
}

void SerchUserName(string UserName, string NameFile = "MyFile", short num = 0) {

    stUser User;
    fstream MyFile;
    vector <string> vUser = GetinformationForFileToVector_string(NameFile);
    if (UserName != "Admin" || num == 0){
        if (SerchUserName(UserName, NameFile, User)) {
            PrintUserRecord(User);
            if (num == 1) {
                DeleteUser(vUser, User, NameFile);
            }
            else if (num == 2) {
                UpdateUser(vUser, User, NameFile);
            }
        }
        else
        {
            cout << "Client with User Name (" << UserName << ") Not Found !\n";
        }
    }
    else {
        if(num == 1)
            cout << "You can't Delete this User" << endl;
        else if(num == 2)
            cout << "You can't Update this User" << endl;
    }

}

void ShowChooseTransactions(short choose) {

    enTransactions Transactions;
    Transactions = (enTransactions)choose;
    switch (Transactions)
    {
    case Deposit:

        system("cls");
        cout << "----------------------------------------------------\n";
        cout << "\t\t" << "Deposit Screen" << endl;
        cout << "----------------------------------------------------\n";
        SerchAccountNumber(ReadAccountNumber(), "Client", 3);
        ReturnOfTransactionsScreen();
        break;


    case Withraw:

        system("cls");
        cout << "----------------------------------------------------\n";
        cout << "\t\t" << "Withdraw Screen" << endl;
        cout << "----------------------------------------------------\n";
        SerchAccountNumber(ReadAccountNumber(), "Client", 4);
        ReturnOfTransactionsScreen();
        break;
        
    case Total_Balances:

        system("cls");
        PrintTotal_Balance(GetinformationFromFileToVector("Client"));
        ReturnOfTransactionsScreen();
        break;

    case Main_Menue:

        system("cls");
        ShowChoose(PrintMenueScreen());
        break;

    default:

        break;
    }

}

void ShowChooseManage_Users(short choose) {

    enManage_Users Manage_Users;
    Manage_Users = (enManage_Users)choose;
    switch (Manage_Users)
    {
    case List_Users:

        system("cls");
        PrintUserList(GetinformationFromFileUsersToVector("Users"));
        ReturnOfManage_UersScreen();
        break;

    case Add_Users:

        system("cls");
        cout << "----------------------------------------------------\n";
        cout << "\t\t" << "Add New Users Screen" << endl;
        cout << "----------------------------------------------------\n";
        AddNewUser("Users");
        ReturnOfManage_UersScreen();
        break;

    case Delete_Users:

        system("cls");
        cout << "----------------------------------------------------\n";
        cout << "\t\t" << "Delete Users Screen" << endl;
        cout << "----------------------------------------------------\n";
        SerchUserName(ReadUserName(), "Users", 1);
        ReturnOfManage_UersScreen();
        break;

    case Update_Users:

        system("cls");
        cout << "----------------------------------------------------\n";
        cout << "\t      " << "Update User Info Screen" << endl;
        cout << "----------------------------------------------------\n";
        SerchUserName(ReadUserName(), "Users", 2);
        ReturnOfManage_UersScreen();
        break;

    case Find_Users:

        system("cls");
        cout << "----------------------------------------------------\n";
        cout << "\t\t" << "Find User Screen" << endl;
        cout << "----------------------------------------------------\n";
        SerchUserName(ReadUserName(), "Users");
        ReturnOfManage_UersScreen();
        break;

    case Main_menue:
        system("cls");
        ShowChoose(PrintMenueScreen());
        break;
    default:
        break;
    }

}

void Access_Denied() {
    system("cls");
    cout << "----------------------------------------------------\n";
    cout << "Access Denied," << endl;
    cout << "You don't have Permission to do this," << endl;
    cout << "Please Contact Your Admin" << endl;
    cout << "----------------------------------------------------\n";
}

void LogIn(vector <stUser> vUser) {

    cout << "----------------------------------------------------\n";
    cout << "\t\t" << "Login Screen" << endl;
    cout << "----------------------------------------------------\n";
    short num = 0;
    if(Invalid_User)
        cout << "\nInvalid UserName/Password !\n" << endl;
    cout << "Enter Username : ";
    cin >> User.UserName;
    cout << endl;
    cout << "Enter Password : ";
    cin >> User.Password;
    cout << endl;
    for (const stUser& U : vUser) {
        if(U.UserName == User.UserName){
            if (U.Password == User.Password) {
                User.Permissions = U.Permissions;
                system("cls");
                Invalid_User = false;
                ShowChoose(PrintMenueScreen());
                break;
            }
            
        }
    }
    Invalid_User = true;
    system("cls");
    LogIn(vUser);

}

void ShowChoose(short choose) {

    enChoose Choose;
    Choose = (enChoose)choose;
    switch (Choose)
    {
    case Show_Client_List:

        if (!CheckAccessPermision(enPermession::eList_Client)) {

            system("cls");
            Access_Denied();
            cout << endl;
            system("pause");
            system("cls");
            ShowChoose(PrintMenueScreen());

        }
        system("cls");
        PrintInformationFromFile(GetinformationFromFileToVector("Client"));
        ReturnOfHomeScreen();
        break;

    case Add_New_Client:

        if (!CheckAccessPermision(enPermession::eAdd_Client)) {

            system("cls");
            Access_Denied();
            cout << endl;
            system("pause");
            system("cls");
            ShowChoose(PrintMenueScreen());

        }
        system("cls");
        cout << "----------------------------------------------------\n";
        cout << "\t\t" << "Add New Clients Screen" << endl;
        cout << "----------------------------------------------------\n";
        SaveInformationInFile("Client");
        ReturnOfHomeScreen();
        break;

    case Delete_Client:

        if (!CheckAccessPermision(enPermession::eDelete_Client)) {

            system("cls");
            Access_Denied();
            cout << endl;
            system("pause");
            system("cls");
            ShowChoose(PrintMenueScreen());

        }
        system("cls");
        cout << "----------------------------------------------------\n";
        cout << "\t\t" << "Delete Client Screen" << endl;
        cout << "----------------------------------------------------\n";
        SerchAccountNumber(ReadAccountNumber(), "Client", 1);
        ReturnOfHomeScreen();
        break;

    case Update_Clinet_Info:

        if (!CheckAccessPermision(enPermession::eUpdate_Client)) {

            system("cls");
            Access_Denied();
            cout << endl;
            system("pause");
            system("cls");
            ShowChoose(PrintMenueScreen());

        }
        system("cls");
        cout << "----------------------------------------------------\n";
        cout << "\t      " << "Update Client Info Screen" << endl;
        cout << "----------------------------------------------------\n";
        SerchAccountNumber(ReadAccountNumber(), "Client", 2);
        ReturnOfHomeScreen();
        break;

    case Find_Client:

        if (!CheckAccessPermision(enPermession::eFind_Client)) {

            system("cls");
            Access_Denied();
            cout << endl;
            system("pause");
            system("cls");
            ShowChoose(PrintMenueScreen());

        }
        system("cls");
        cout << "----------------------------------------------------\n";
        cout << "\t\t" << "Find Client Screen" << endl;
        cout << "----------------------------------------------------\n";
        SerchAccountNumber(ReadAccountNumber(), "Client");
        ReturnOfHomeScreen();
        break;

    case Transactions:

        if (!CheckAccessPermision(enPermession::eTranaction)) {

            system("cls");
            Access_Denied();
            cout << endl;
            system("pause");
            system("cls");
            ShowChoose(PrintMenueScreen());

        }
        system("cls");
        ShowChooseTransactions(PrintTransactionsScreen());
        break;

    case Manage_Users:

        if (!CheckAccessPermision(enPermession::eManagerUsers)) {

            system("cls");
            Access_Denied();
            cout << endl;
            system("pause");
            system("cls");
            ShowChoose(PrintMenueScreen());

        }
        system("cls");
        ShowChooseManage_Users(PrintMenage_UsersScreen());
        break;

    case Logout:

        system("cls");
        LogIn(GetinformationFromFileUsersToVector("Users"));
        break;

    default:
        break;
    }
    
}

int main()
{
   
    LogIn(GetinformationFromFileUsersToVector("Users"));

}