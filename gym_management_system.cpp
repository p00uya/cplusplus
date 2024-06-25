#include <iostream>
#include <fstream> 
#include <string>
#include <sstream>
#include <ctime>
#include <iomanip>


using namespace std;

// global variable
bool f_edit , f_del , f_search;
struct node
{
	string id;
    string start_date, end_date;
    string First_name , Last_name ;
    node *next;
    
};
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t");
    if (first == string::npos) return ""; // No non-whitespace characters
    size_t last = str.find_last_not_of(" \t");
    return str.substr(first, (last - first + 1));
}


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
		
	    void search(const string& input_id = "", const string& input_fname = "" , const string& input_lname="" ) {
		    ofstream tempFile("temp.txt");

		    ifstream file("customerlist.txt");
		
		    if (!file || !tempFile) {
		        cerr << "Error: Unable to open files." << endl;
		        return;
		    }
		    
	        if (!file.is_open()) {
	        cerr << "Unable to open file" << endl;
	        return;
	    	}

		    string line;
		    bool found = false; 
		    while (getline(file, line)) {
		        istringstream iss(line);
		        string token;
		        bool id_match = false;
		        bool fname_match = false;
		        bool lname_match = false;
		
		        while (getline(iss, token, ',')) {
		            size_t pos = token.find(':');
		            if (pos != string::npos) {
		                string key = trim(token.substr(0, pos));
		                string value = trim(token.substr(pos + 1));
		
		                if (!input_id.empty() && key == "ID" && value == input_id) {
		                    id_match = true;
		                } else if (!input_fname.empty() && key == "first_name" && value == input_fname) {
		                    fname_match = true;
		                } else if (!input_lname.empty() && key == "last_name" && value == input_lname) {
		                    lname_match = true;
		                }
		            }
		        }
		
		        // Ensure the correct field is being matched based on the input
		        if ((id_match && !input_id.empty()) ||
		            (fname_match && !input_fname.empty()) ||
		            (lname_match && !input_lname.empty())) {
		            
		            cout << "Found: " << line << endl;
		            found = true;
		            if (f_edit) {
		                // Implement edit functionality here
		                cout << "Editing functionality not implemented yet." << endl;
		            } else if (f_del) {
		                continue; // Skip adding the line to tempFile to delete the record
		            }
		        } else {
		            tempFile << line << endl; // Write the line to tempFile if it doesn't match the search criteria
		        }
		        }

				if (!found) {
				        cout << "Record not found." << endl;
				    }
				
				    file.close();
				    tempFile.close();
				
				    if (f_del) {
				        // Remove original file and rename temp file
				        remove("customerlist.txt");
				        rename("temp.txt", "customerlist.txt");
				        if (found) {
				            cout << "Customer deleted successfully." << endl;
				        }
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
//int promptForInput(const string& action) {
//    int input;
//    cout << "If you want to " << action << " with ID input 1, first name input 2, or last name input 3: " << endl;
//    cin >> input;
//    search_account();
//    return input;
//}
	
void search_account(bool f_edit, bool f_del)
{
    linked_list a;
    string input_id, input_fname, input_lname;
    int input;

    if (f_edit) {
        cout << "If you want to edit with ID input 1, or first name input 2, or last name input 3: " << endl;
    } else if (f_del) {
        cout << "If you want to delete with ID input 1, or first name input 2, or last name input 3: " << endl;
    } else {
        cout << "If you want to search with ID input 1, or first name input 2, or last name input 3: " << endl;
    }
    cin >> input;

    switch (input) {
        case 1:
            cout << "Enter ID :" << endl;
            cin >> input_id;
            a.search(input_id);
            break;
        case 2:
            cout << "First name:" << endl;
            cin >> input_fname;
            a.search("", input_fname);
            break;
        case 3:
            cout << "Last name :" << endl;
            cin >> input_lname;
            a.search("", "", input_lname);
            break;
        default:
            cout << "Invalid choice." << endl;
            break;
    }
}
void delete_customer()
{
    f_del = true;
    search_account(false, true);
    f_del = false; // Reset flag after operation
}

void edit_customer()
{
    f_edit = true;
    search_account(true, false);
    f_edit = false; // Reset flag after operation
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
//	edit_customer();
//	recharge_account();

    return 0;
}

