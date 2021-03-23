/*
 * untitled.c
 * 
 * Copyright 2021 zacha <zacha@DESKTOP-DN5CCAS>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <stdio.h>
#include <iostream> 
#include <fstream> 
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <cstdlib>
#include <ctime>
#include <random>
#include <algorithm>
//#include <math>
//#include <double>

using namespace std;


 
void feature_search_demo(vector<vector<double>> features); 
int feature_counter(string dataset); //counts the columns to determine how long we should search in each line 
vector<double>object_packager(string object_features, int num_features); //packages a string of words taken from a string stream into a  vector<double> to access indexes easily
string object_grabber(string dataset, int line_input); //grabs a specific line of the dataset
bool already_added(vector<int> current_set_of_features, int feature_number); 
vector<vector<double>> organize_file(string file_name, int num_features);
void forward_selection(vector<vector<double>> features);

void backward_elim(vector<vector<double>> features);
double leave_one_out_cross_validation(vector<vector<double>> data, vector<int> current_set, int feature_to_add);
//double accuracy(vector<vector<double>> data, int num_features);


/*
bool not_included(vector<int> cur_set, int feature_number);

bool not_included(vector<int> cur_set, int feature_number){
	bool included =  false;
	for(int i = 0; i < cur_set.size(); i++){
		if(
	
}

*/



int main(int argc, char **argv)
{
	string file_name;
	int num_columns = 0;
	int which_set;
	cout << "Would you like small data set or big data set?" << endl << "Press 1 for small and 2 for big: ";
	cin >> which_set;
	cin.clear();
	cout << endl;
	
	
	if(which_set == 1){  //SMALL DATA SET
		file_name = "CS170_SMALLtestdata__19.txt";
	}else if(which_set == 2){//feature_search_demo("CS170_largetestdata__81.txt");
		file_name = "CS170_largetestdata__81.txt";
	}else if(which_set == 3){
		cout << "Test mode: " << endl;
		//file_name = "CS170_SMALLtestdata__19.txt";
		//file_name = "CS170_small_special_testdata__95.txt";
		//file_name = "CS170_small_special_testdata__96.txt";
		//file_name = "CS170_small_special_testdata__98.txt";
		
		//num_columns = feature_counter(file_name);
		//vector<vector<double>> text_data;
		//text_data = organize_file(file_name, num_columns);
		//feature_search_demo(text_data);
		//forward_selection(text_data);
		//backward_elim(text_data);
		//ifstream f(file_name);
		//int line_to_grab;
		//cout << "Which line would you like to create tree for? " << endl;
		//cin >> line_to_grab;
		//line_to_grab--;
		//cin.clear();
		//string object_grabbed = object_grabber(file_name, line_to_grab);
		//cout << "Number of columns is: " << num_columns << endl;
		//vector<double> basket(num_columns);
		//basket = object_packager(object_grabbed , num_columns);
		
		//cout << "Displaying entire second line of text: " << endl;
		//for(int i = 0; i < text_data.size(); i++){
			//cout << "Looping over i, at the " <<  i  + 1 << " location " << endl << "The " << i + 1<< "th object is in class " << text_data[i][0] << endl;
		//}
		//accuracy(text_data, num_columns);
		
	}

	num_columns = feature_counter(file_name);
	int search_choice;
		vector<vector<double>> text_data;
		text_data = organize_file(file_name, num_columns);
		cout << "Which search function would you like to  use? " << endl;
		cout << "Forward Selection: 1" << endl;
		cout << "Backward Elimination: 2"  << endl;
		cin >> search_choice;
		if(search_choice == 1){
			forward_selection(text_data);
		}else if(search_choice == 2){
			backward_elim(text_data);
		}
			

	return 0;
}
void feature_search_demo(vector<vector<double>> data){
	int num_features = data[0].size() -1;
	cout << "Number of features detected are: " << num_features << endl;
	vector<int> current_set_of_features(num_features);
	//double best_so_far_accuracy = 
	
	//cout << "Class label: " << data[0] << endl;

	for(int i = 1; i <=  num_features; i++){
		cout << "On the " << i << "th level of the search tree : " << endl;
		int feature_to_add_at_this_level = 1;
		double best_so_far_accuracy = 0;
		int level_save = 1;
		
		for(int k = 1; k <= num_features; k++){
			if(!already_added(current_set_of_features, k)){ 
				
	
				double accuracy = leave_one_out_cross_validation(data, current_set_of_features, k); 
				
				
				//cout << "COde reaching this point " << endl;
				if(accuracy > best_so_far_accuracy){

					best_so_far_accuracy = accuracy;
					level_save = k;

					feature_to_add_at_this_level = k;

				}
			}
		}
		
		current_set_of_features[level_save] = feature_to_add_at_this_level;
		cout << "On level " << i << " I added the " << level_save << " feature to current set, making my accuracy: " << best_so_far_accuracy << endl; 
	}
	
	
	
}
void forward_selection(vector<vector<double>> features){
	int num_features = features[0].size() -1;
	cout << "Number of features detected are: " << num_features << endl;
	vector<int> current_set_of_features;
	vector<int> best_set_of_features; //gonna use this for look ahead
	//double best_so_far_accuracy = 
	double best_so_far_accuracy = 0.0;
	int default_rate = 0;
	for(int u = 0; u < features.size(); u++){
		if(features[u][0] == 1.0) {
			default_rate++;
		}
	}
	cout << "Default rate: " << (double)default_rate/features.size() << endl;
		
	int best_level;
	//cout << "Class label: " << data[0] << endl;
	double all_features_acc = leave_one_out_cross_validation(features, current_set_of_features, 0);
	cout << "Accuracy including all features is: " << all_features_acc << endl << endl;

	for(int i = 1; i <=  num_features; i++){ //FOR EVERY LEVEL, OUTPUT THE BEST ACCURACY...BUT SAVE IT.
		cout << "On the " << i << "th level of the search tree : " << endl << endl ;
		int feature_to_add_at_this_level = -1;
		double local_best_acc  = 0.0;
		int level_save = 1;
		
		for(int k = 1; k <= num_features; k++){
			if(!already_added(current_set_of_features, k)){ 
				
				  //Do I want to display the value?
				double accuracy = leave_one_out_cross_validation(features, current_set_of_features, k); //THIS IS STUB, WE EVENTUALLY WANT IT TO actually evaluate accuracy //CHECK FOR OFF BY ONE. FIXED
				//double accuracy = accuracy(
				//cout << "Accuracy is: " << best_so_far_accuracy << endl;
				
				cout << "Set of features with feature " << k << " has accuracy of: " << accuracy * 100.0 << "%" << endl;
				//cout << "COde reaching this point " << endl;
				if(accuracy >= local_best_acc){

					local_best_acc = accuracy;
					//level_save = k;

					feature_to_add_at_this_level = k;

				}
			}
		}
		current_set_of_features.push_back(feature_to_add_at_this_level);
		
		if(local_best_acc > best_so_far_accuracy){
			//best_overall_accuracy_at_level = best_so_far_accuracy;
			best_so_far_accuracy = local_best_acc;
			cout <<endl;
			cout << "On level " << i << " I added the " << feature_to_add_at_this_level << " feature to current set, making my accuracy: " << best_so_far_accuracy * 100 << "%"  << endl; 
			cout<< "More accurate set of features found, this is our current most accurate set! " << endl;
			best_set_of_features = current_set_of_features;

		}else{
			//cout << "Best set at this level is {" << 
			cout << endl;
			cout << "Next level did not find a better set of solutions" << endl; 
		}
		cout << endl << endl;
		cout << "the best features are {";
		
		for(int p = 0; p < best_set_of_features.size(); p++){
			cout << best_set_of_features[p] << " "; 	
		}	
		cout << "} " << "with an accuracy of: " << best_so_far_accuracy * 100 << "%" << endl;
		
		cout << "The best set at this level is {";
		
		for(int o = 0; o < current_set_of_features.size(); o++){
			cout << current_set_of_features[o] << " "; 	
		}	
		cout << "} " << "with an accuracy of: " << local_best_acc* 100 << "%" << endl;
	}
	
	
}
double leave_one_out_cross_validation(vector<vector<double>> data, vector<int> current_set, int feature_to_add){
	//label is data[line# -1][0]
	int num_features = data[0].size() - 1;
	double classification_accuracy = 0.0;
	double correctly_classified = 0.0;
	
	
	if(feature_to_add < 0) {
		feature_to_add *= -1;
		for(int a = 0; a < data.size(); a++){
			for(int b = 1; b <= data[0].size()-1; b++){
				if(!(std::find(current_set.begin(), current_set.end(),b)!= current_set.end())){ //if its in your current set, you want to delete it
					data[a][b] = 0.0; //delete anything not in current set as well
				}
				if(b == feature_to_add){
					data[a][b] = 0.0; //delete b from current set for backward elim
				}
			}
		}
	}else if(feature_to_add == 0){
		//do nothing? Just figuring out the calculation with all things
	
	}else{ //THIS JUST SWITCHES BETWEEN BACKWARDS OR FORWARDS
		for(int a = 0; a < data.size(); a++){ //this nestedgoes through data and changes things not in our current data set to 0
			for(int b = 1; b <= data[0].size()-1; b++){ //go through each line feature by feature, b iterates features
				if(!(std::find(current_set.begin(), current_set.end(),b)!= current_set.end())){  //b not found in current set or the one youre adding, 
					if(b != feature_to_add){
						data[a][b] = 0.0; //made element not in set equal to zero, now need to compare accuracy to set 
						
					}
				}
			}
		}
	}
	
	
	
	for(int i = 0; i < data.size(); i++){ //CHANGE BACK TO DATA.SIZE(), MAKING SMALLER FOR TEST PURPOSES
		
		
		double calculate = 0;
		  
		  
		  
		  
		//cout << "Code functioning at this level in accuracy function: " << i << endl;  
		double label_object_to_classify = data[i][0];
		double nearest_neighbor_distance = 100;
		int nearest_neighbor_location =   1000; //infinite values(not really but it works)
		double nearest_neighbor_label = 3; //IF IT DISPLAYS 3.0, ERROR THIS IS NOT A CLASS
		for(int k = 0; k < data.size(); k++){    //SHOULD ALSO BE DATA.SIZE
			
			if(k != i){	
				double sum = 0;
				for(int j = 1; j <= num_features; j++){
					double block = data[i][j] - data[k][j]; //distance between two objects in one dimension(or only one feature), notice that j = 1 because feature starts at second index of vertex, object index starts at 0
					calculate = pow(block, 2.0); //takes power of the differnce for part of Euclidean
					sum += calculate;
					//cout << " Ask if " << i + 1 << " is nearest neighbor with " << k << endl;

				}
				double distance = sqrt(sum);
				if(distance < nearest_neighbor_distance){
					nearest_neighbor_distance = distance; 
					nearest_neighbor_location = k;  //THIS IS NOT THE RIGHT LOCATION, THIS IS THE INTERPRETED LOCATION, REPRESENTED BY +1 OF INDEX//updated to reresent index 
					nearest_neighbor_label = data[nearest_neighbor_location][0];
				}
			}
		}
		
		if(label_object_to_classify == nearest_neighbor_label) {
			correctly_classified = correctly_classified + 1;
		}
		
		
		//cout << "Object " << i + 1 << " is class " << label_object_to_classify << endl;
		//cout << "It's nearest neighbor is " << nearest_neighbor_location + 1 << " which is in class " << (int)nearest_neighbor_label << endl;
	}
	//cout << "number of objects/lines is: " << data.size() << endl;
	classification_accuracy = correctly_classified / (double)data.size();
	//cout << "Calculated accuracy is: " << classification_accuracy << endl;
	return classification_accuracy;
}


void backward_elim(vector<vector<double>> features){
	int num_features = features[0].size()-1;
	cout << "Number of features detected are: " << num_features << endl;
	vector<int> current_set_of_features;
	for(int y = 1; y <= num_features; y++){//CREATING THE FULL SET
		current_set_of_features.push_back(y);
	}
	double all_features_acc = leave_one_out_cross_validation(features, current_set_of_features, 0);
	cout << "Accuracy including all features is: " << all_features_acc << endl << endl;
	vector<int> best_set_of_features; //gonna use this for look ahead
	double best_so_far_accuracy = 0.0;
	int best_level;
	//cout << "Class label: " << data[0] << endl;
	

	for(int i = 1; i <=  num_features; i++){ //FOR EVERY LEVEL, OUTPUT THE BEST ACCURACY...BUT SAVE IT.
		cout << "On the " << i << "th level of the search tree : " << endl << endl ;
		int feature_to_remove_at_this_level = -1;
		double local_best_acc  = 0.0;
		int level_save = 1;
		
		for(int k = 1; k <= num_features; k++){
			if(already_added(current_set_of_features, k)){ //IF ITS STILL IN THE CURRENT SET, ALLOWED TO REMOVE IT
				
				  //Do I want to display the value?
				double accuracy = leave_one_out_cross_validation(features, current_set_of_features, -k); 
				//double accuracy = accuracy(
				//cout << "Accuracy is: " << best_so_far_accuracy << endl;
				
				cout << "Set of features without feature " << k << " has accuracy of: " << accuracy * 100.0 << "%" << endl;
				//cout << "COde reaching this point " << endl;
				if(accuracy >= local_best_acc){

					local_best_acc = accuracy;
					//level_save = k;

					feature_to_remove_at_this_level = k;

				}
			}
		}
		
		current_set_of_features.erase(remove(current_set_of_features.begin(), current_set_of_features.end(), feature_to_remove_at_this_level), current_set_of_features.end());
		
		if(local_best_acc > best_so_far_accuracy){
			//best_overall_accuracy_at_level = best_so_far_accuracy;
			best_so_far_accuracy = local_best_acc;
			cout <<endl;
			cout << "On level " << i << " I  subtracted " << feature_to_remove_at_this_level << " feature to current set, making my accuracy: " << best_so_far_accuracy * 100 << "%"  << endl; 
			cout<< "More accurate set of features found, this is our current most accurate set! " << endl;
			best_set_of_features = current_set_of_features;

		}else{
			//cout << "Best set at this level is {" << 
			cout << endl;
			cout << "Next level did not find a better set of solutions" << endl; 
		}
		cout << endl << endl;
		cout << "the best features are {";
		
		for(int p = 0; p < best_set_of_features.size(); p++){
			cout << best_set_of_features[p] << " "; 	
		}	
		cout << "} " << "with an accuracy of: " << best_so_far_accuracy * 100 << "%" << endl;
	}
	
	
}
//--------------------------------------HELPERS---------------------------
int feature_counter(string dataset){
	
	int columns = 0;
	ifstream file(dataset); 
	string line_reader;
	getline(file, line_reader);
	stringstream  col_stream; //stringstream has the first line, just parse and count how many entries
	col_stream << line_reader; //output to string 
	
	  
	string word_trash_can;
	while(col_stream >> word_trash_can){
		columns++;
	}
	file.close(); //do I need to close before using it again? Don't think I need to because as long as different loops, getline and searches start at beginning? If run into issues, try this as fix.
	columns--; //Don't count ID, first column 
	//cout << "Number of features is: " << columns << endl;
	
	
	return columns;
}


vector<double> object_packager(string object_features, int num_features){
	
	stringstream features(object_features);
	istream_iterator<double> begin(features);
	istream_iterator<double> end;
	
	
	vector<double> object_set(begin, end);
	
	return object_set;
	
}
string object_grabber(string dataset, int line_input){ //UNNECESSARY...NEED TO READ THE WHOLE FILE, NEVER A NEED FOR SPECIFIC LINE READING. 
	//ifstream file("C:/cygwin64/home/zacha/Nearest Neighbor/CS170_SMALLtestdata__19"); 
	ifstream file;
	file.open(dataset);
	if(!file) {
		cerr << "Unable to open file";
    exit(1); 
	}
	string line_reader;
	string save_string;
	
	int i = 0; 
	if(file.is_open()){
		while(getline(file, line_reader)){
			if(i == line_input){
				save_string = line_reader;
				return save_string;
			}
			i++;
		}
		file.close();
	}
	string error = "Error: not found? ";
	return error;
		
		
}




bool already_added(vector<int> current_set_of_features, int feature_number){
	for(int i = 0; i < current_set_of_features.size(); i++){
		if(current_set_of_features[i] == feature_number){
			return true;
		}
	}
	return false;
}

vector<vector<double>> organize_file(string file_name, int num_features){
	//vector<double> line_data(num_features);
	//vector<vector<double>(num_features) > full_dataset;
	vector<vector<double> > full_dataset;
	
	
	
	
	
	
	
	ifstream file;
	file.open(file_name);
	if(!file) {
		cerr << "Unable to open file";
		exit(1); 
	}
	string line_reader;
	string save_string;
	
	if(file.is_open()){
		while(getline(file, line_reader)){
			string object_grabbed =  line_reader;
			vector<double> basket(num_features);
			basket = object_packager(object_grabbed , num_features);
			full_dataset.push_back(basket);
		}
		file.close();
		return full_dataset;
	}
	string error = "Error: not found? ";
	return full_dataset;
		
		
}


