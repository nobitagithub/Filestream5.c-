#include<iostream>
#include<cstdio>
#include<fstream>
using namespace std;

struct product{
	
	int id;
	char name[50];
	float price;
};
char file_name[] = "star.bin";
void add_item(){
	product p;
	
	cout << "Enter product id:" ;
	cin >> p.id;
	cin.ignore();
	cout << "Enter the Product Name:";
	cin.getline(p.name,50);
	cout << "Enter the product price:";
	cin >> p.price;
	
	ofstream ofs(file_name, ios::binary | ios::app);
	ofs.write((char*)&p,sizeof(p));
	ofs.close();
}

void Display_Data(){
	
	
	ifstream ifs(file_name , ios::binary);
	if(!ifs.is_open()){
		cout << "File is not Found" << endl;
		return;
	}
	product p;
	while(ifs.read((char*)&p,sizeof(p))){
		
		cout << "Id :" << p.id << endl;
		cout << "Name :" << p.name << endl;
		cout << "Price:" << p.price<<endl;
	}
 	ifs.close();	
}

void delete_item(){
	int id;
	cout << "Enter the id of the product:";
	cin >> id;
	
	char choice;
	cout << "Are you sure you want to delete product id" << id <<"?"<< endl;
	cout << "press y to continue , any other key to cancel:";
	cin >> choice;
	if(choice != 'y' && choice != 'Y'){
return ;
	}
	
	ifstream ifs(file_name , ios::binary);
	if(!ifs.is_open()){
		cout << "Data File not Found:" <<endl;
		return;
	}
	ofstream ofs("temp.bin", ios::binary);
	bool data_found = false;
	product p;
	while(ifs.read((char*)&p,sizeof(p))){
		
		if(p.id != id){
			
			ofs.write((char*)&p,sizeof(p));
		}
		else{
			data_found = true;
		}
	}
	ofs.close();
	ifs.close();
	
	if(data_found == false){
		cout << "no record found"<<id<<endl<<endl;
		remove("temp.bin");
		return;
	}
	
	
	
	ifstream ifs2("temp.bin", ios::binary);
	
	ofstream ofs2(file_name,ios::binary);
	
	while(ifs2.read((char*)&p,sizeof(p))){
		
		
		ofs2.write((char*)&p,sizeof(p));
			}
	
	ifs2.close();
	ofs2.close();
	
	cout << "record delete for id "<<id<<" successfully"<<endl;
	 remove("temp.bin");	
}
void Update_item(){
		int id;
	cout << "Enter product id to update" << endl;
	cin>>id;
		char choice;
	cout << "Are you sure you want to delete product id" << id <<"?"<< endl;
	cout << "press y to continue , any other key to cancel:";
	cin >> choice;
	if(choice != 'y' && choice != 'Y'){
return ;
	}
	
	
	  ifstream ifs(file_name , ios::binary);
	  bool data_found = false;
	  if(!ifs.is_open()){
	  	cout << "file not found"<<endl;
	  	return;
	  }
	  
	  
	  product p;
	  ofstream ofs("temp.bin",ios::binary);
	  
	  while(ifs.read((char*)&p,sizeof(p))){
	  if(p.id = id){
	  	cin.ignore();
	  	cout << "Enter product name:"<<endl;
	  	cin.getline(p.name,50);
	  	cout << "Enter product price:"<< endl;
	  	cin >> p.price;
	  	}
        
		ofs.write((char*)&p,sizeof(p));	  
	}
	ifs.close();
	ofs.close();
	if(data_found){
		cout << "Data updated successfully" << endl;
	}
	else{
		cout << "record not found with id :" << id <<endl;
	}
	remove(file_name);
	rename("temp.bin",file_name);
}

void search_by_id(){
	int id;
	cout << "Enter id to search:";
	cin >> id;
	
	ifstream ifs(file_name,ios::binary);
	product p;
	while(ifs.read((char*)&p,sizeof(p))){
		if(p.id == id){
			cout << "Record found:"<<endl;
			cout << "ID"<<p.id<<endl;
			cout << "Name"<<p.name<<endl;
			cout << "price"<<p.price<<endl;
			cout << endl;
			ifs.close();
			return;
		}
	}
	cout << "Record not found for id :" << id<<endl; 
}


int main(){
	
	int choice;
do{
		cout << "===Menu===" << endl;
	cout << "1.Add items" << endl;
	cout << "2.Display Data item"<< endl;
	cout << "3.Delete item" << endl;
	cout << "4.Update item" << endl;
	cout << "5.Search by id:" <<endl;
	cout << "0. Exit" << endl;
	
	cout << "Choose an option (0-5):";
	cin >> choice; 
	if(choice == 1){
		add_item();
	}
	
	else if(choice == 2){
	 Display_Data();	
	}
	else if(choice == 3){
		delete_item();
	}
	else if(choice == 4){
		Update_item();
	}
	else if(choice == 5){
		search_by_id();
	}
	else if(choice == 0){
		cout << "Good bye" << endl;
	}
	else{
		cout << "Invalid option" << endl;
	}
	
}while(choice != 0) ;


return 0;
}
