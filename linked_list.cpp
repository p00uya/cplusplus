#include <iostream>
#include <fstream> 
#include <string>
#include <sstream>
#include <ctime>
#include <iomanip>


using namespace std;

struct node
{
	string id;
    string start_date, end_date;
    string First_name , Last_name ;
    node *next;
    
};

class linked_list
{
private:
    node *head, *tail;

public:
    linked_list()
    {
        head = NULL;
        tail = NULL;
    }
    	void write_to_file(const char* filename)
		{
			 ofstream file(filename, std::ios_base::app); // Open file in append mode
		
		    if (file.is_open())
		    {
		    	// index , ID , end-date
		        node *current = head;
		        while (current != NULL)
		        {
		            file <<"ID: "<< current->id <<", first_name: " << current->First_name << ", last_name: " << current->Last_name 
						 << ", start Date: " << current->start_date <<", end Date: " << current->end_date <<  endl;
					current = current->next;
		        }
		        file.close();
		        cout << "Data written to file successfully." << endl;
		    }
		    else
		    {
		        cout << "Unable to open file." << endl;
		    }
		}
		void add_node(string ID , string first_name, string last_name, const pair<string, string>& times ){
		    node *tmp = new node;
		  	
			tmp->id = ID;
		    tmp->start_date = times.first;
			tmp->end_date   = times.second;
		    tmp->First_name = first_name;
		    tmp->Last_name  = last_name;
		    tmp->next = NULL;
		
		    if (head == NULL)
		    {
		        head = tmp;
		        tail = tmp;
		    }
		    else
		    {
		        tail->next = tmp;
		        tail = tail->next;
		    }
		}

		void delete_customer(const string& input_id) {
		    ifstream inFile("customerlist.txt");
		    ofstream tempFile("temp.txt");
		
		    if (!inFile || !tempFile) {
		        cerr << "Error: Unable to open files." << endl;
		        return;
		    }
		
		    bool found = false;
		    string line;
		
		    while (getline(inFile, line)) {
		        stringstream ss(line);
		        string token;
		        bool match = false;
		        while (getline(ss, token, ',')) {
		            stringstream token_ss(token);
		            string key, value;
		            getline(token_ss, key, ':');
		            getline(token_ss, value);
		            if (key == "ID") {
		                value.erase(0, value.find_first_not_of(" \t"));
		                value.erase(value.find_last_not_of(" \t") + 1);
		                if (value == input_id) {
		                    match = true;
		                    found = true;
		                    break;
		                }
		            }
		        }
		        if (!match) {
		            tempFile << line << endl;
		        }
		    }
		
		    inFile.close();
		    tempFile.close();
		
		    // Remove original file
		    remove("customerlist.txt");
		    // Rename temp file to original file
		    rename("temp.txt", "customerlist.txt");
		
		    if (found) {
		        cout << "Customer with ID " << input_id << " deleted." << endl;
		    } else {
		        cout << "Customer with ID " << input_id << " not found." << endl;
		    }
		}
		
	    void search(const string& input_id, const string& input_fname = "", const string& input_lname = "") {
////		void search(const string& input_id , const string& input_fname , const string& input_lname) {
//		    cout << "Searching for ID: " << input_id << endl;
//		    cout << "Searching for first name: " << input_fname << endl;
//		    cout << "Searching for last name: " << input_lname << endl;
		    ifstream file("customerlist.txt");
		    
		    if (file.is_open()) {
		        string line;
		        while (getline(file, line)) {
		            stringstream ss(line);
		            string token;
		            while (getline(ss, token, ',')) {
		                stringstream token_ss(token);
		                string key, value;
		                getline(token_ss, key, ':');
		                getline(token_ss, value);
		                if (key == "ID") {
		                    // Remove leading and trailing whitespaces from value
		                    f_id = 1;
		                    value.erase(0, value.find_first_not_of(" \t"));
		                    value.erase(value.find_last_not_of(" \t") + 1);
		                    if (value == input_id) {
		                        cout << "Found: " << line << endl;
		                        file.close(); // Close the file after finding the record
		                        return;
		                    }
		                }
		            }
		        }
		        cout << "Customer with ID " << input_id << " not found." << endl;
		        file.close(); // Close the file if the record is not found
		    } else {
		        cout << "Unable to open file." << endl;
		    }
		}




};

pair<string, string> my_time() {
    time_t t = time(0);  
    struct tm *now = localtime(&t);
    ostringstream osDateTime;
    
    osDateTime << (now->tm_year + 1900) << "-" 
               << setw(2) << setfill('0') << (now->tm_mon + 1) << "-" 
               << setw(2) << setfill('0') << now->tm_mday << " "
               << setw(2) << setfill('0') << now->tm_hour << ":" 
               << setw(2) << setfill('0') << now->tm_min << ":" 
               << setw(2) << setfill('0') << now->tm_sec;
    
    string start_time = osDateTime.str(); // Store current time
    
    osDateTime.str(""); // Clear the stringstream
    
    int end_month = now->tm_mon + 2;
    int end_year = now->tm_year + 1900;
    if (end_month > 12) {
        end_month -= 12;
        end_year++;
    }
    osDateTime << end_year << "-" 
               << setw(2) << setfill('0') << end_month << "-" 
               << setw(2) << setfill('0') << now->tm_mday << " "
               << setw(2) << setfill('0') << now->tm_hour << ":" 
               << setw(2) << setfill('0') << now->tm_min << ":" 
               << setw(2) << setfill('0') << now->tm_sec;
    
    string end_time = osDateTime.str(); // Store end time

    return make_pair(start_time, end_time);
} 
void sub()
{
	linked_list a;	
	string name , last_name;
	string ID;
	cout << "enter ID : " << endl;
	cin >> ID;
	cout << "enter first_name : " <<endl;
	cin >> name ;
	cout << "enter last_name : " <<endl;
	cin >> last_name ;
	
	pair<string, string> times = my_time();	
	a.add_node( ID , name , last_name , times);

    a.write_to_file("customerlist.txt");
		
}
my_customerlist()
{
    const char* filename = "customerlist.txt"; 
    ifstream file(filename,std::ios_base::app); 
	int i = 0;
    if (file.is_open()) {
        string line;
        while (getline(file, line)){
			cout << i <<line << endl;
//			i++;			        
		}
		file.close();
    
	} else {
        cout << "Unable to open file." << endl;
    }
    	
}

delete_customer()
{
	linked_list a;
	string ID;
	cout << "enter ID : " << endl;
	cin >> ID;
	a.delete_customer(ID);
}
	
search_account()
{
	linked_list a;
	string input_id , input_fname , input_lname ;
	if(f_edit)
	{
		cout<< "if you wanna search with id input 1 : " <<endl;
		cin>>input;
		cout<< "if you wanna search with first name input 2 : "<<endl;
		cin>>input;
		cout<< "if you wanna search with last name input 3 : " <<endl;
		cin>>input;
		swich input:
			case 1;
			a.search(input_id);
			case 2; 
			a.search(input_fname);
			case 3;
			a.search(input_lname); 
	}
	cout << "enter id :" <<endl;
	cin>>input_id;
	a.search(input_id);	
}

edit_customer()
{
	edit_by_name();
	{
		
	}
	edit_by_Lastname();
	{
		
	}edit_by_Id();
}

int main()
{
	
	string start_date ;
	
//	pair<string, string> times = my_time();
//	start_date = my_time();
//	my_customerlist();
//	sub(); 
//	search_account(); // TO DO by id for identify account charge 
	delete_customer(); // TO DO
//	recharge_account();

    return 0;
}


