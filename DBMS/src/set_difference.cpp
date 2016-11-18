/*
 * set_difference.cpp
 *
 *  Created on: 14-Oct-2016
 *      Author: vivek10p14
 */

#include "header.h"

using namespace std;

struct table* set_difference(string s){
	if(!check_db()){
		cout << "Select Database !!!" << endl; // check if database is selected
		return NULL;
	}

	vector<string> v = string_to_vector(s); // convert string to vector of strings
	if(!proper_diff(v)){
		cout << "Check Syntax !!!" << endl; // check for proper syntax
	}
	vector<string> project1,project2; // get both the project queries separately
	int pivot = 0;
	for(int i=0;i<v.size();i++){
		if(v[i]=="difference"){
			pivot = 1;
		}
		else{
			if(pivot==0){
				project1.push_back(v[i]);
			}
			else{
				project2.push_back(v[i]);
			}
		}
	}
	table* table1 = project(vector_to_string(project1)); // load both the tables required for union
	table* table2 = project(vector_to_string(project2));

	vector<string> attr1,attr2; // get attribute list of both tables
	attr1 = (table1->tot_index);
	attr2 = (table2->tot_index);

	if(attr1.size()!=attr2.size()){ // check if the tables have similar arity (check size)
		cout << "Problem in Arity !!!" << endl;
		return NULL;
	}
	for(int i=0;i<attr1.size();i++){ // the corresponding attributes must have same datatype
		if((table1->mint).count(attr1[i])!=(table2->mint).count(attr2[i])){
			cout << "Problem in Arity !!!" << endl;
			return NULL;
		}
	}

	map<vector<string>, int> map1; // map all tuples of table1
	map<vector<string>, int> map2; // map all tuples of table2

	table* ans = new table(); // make structure of table similar to table1
	ans->mint = table1->mint;
	ans->mstring = table1->mstring;
	ans->attr_index = table1->attr_index;
	ans->tot_index = table1->tot_index;

	vector<string> aux_string;
	vector<int> aux_int;
	for(int i=0;i<(table1->mint).size();i++){
		(ans->vint).push_back(aux_int);
	}
	for(int i=0;i<(table1->mstring).size();i++){
		(ans->vstring).push_back(aux_string);
	}

	vector<string> attr_list1 = table1->tot_index;
	vector<string> attr_list2 = table2->tot_index;


	int tuples1 = 0; // get tuple size for both tables
	if((table1->mint).size()!=0){
		tuples1 = (table1->vint)[0].size();
	}
	else if((table1->mstring).size()!=0){
		tuples1 = (table1->vstring)[0].size();
	}
	else{
		cout << "Empty Table" << endl;
		return NULL;
	}

	vector<string> v1;

	for(int i=0;i<tuples1;i++){ // insert tuples form table1 in map
		for(int j=0;j<attr_list1.size();j++){
			if((table1->mint)[attr_list1[j]]!=0){
				v1.push_back(int_to_string((table1->vint)[(table1->mint)[attr_list1[j]]-1][i]));
			}
			else{
				v1.push_back((table1->vstring)[(table1->mstring)[attr_list1[j]]-1][i]);
			}
		}
		map1[v1] = 1;
		v1.clear();
	}

	v1.clear();

	int tuples2 = 0;
	if((table2->mint).size()!=0){
		tuples2 = (table2->vint)[0].size();
	}
	else if((table2->mstring).size()!=0){
		tuples2 = (table2->vstring)[0].size();
	}
	else{
		cout << "Empty Table" << endl;
		return NULL;
	}

	for(int i=0;i<tuples2;i++){ // insert tuples from table2 in map
		for(int j=0;j<attr_list2.size();j++){
			if((table2->mint)[attr_list2[j]]!=0){
				v1.push_back(int_to_string((table2->vint)[(table2->mint)[attr_list2[j]]-1][i]));
			}
			else{
				v1.push_back((table2->vstring)[(table2->mstring)[attr_list2[j]]-1][i]);
			}
		}
		map2[v1] = 1;
		v1.clear();
	}

	for(map<vector<string>, int>::iterator it=map1.begin();it!=map1.end();++it){
		if(map2[it->first]==0){ // select queries that exist in table1 uniquely
			for(int i=0;i<attr_list1.size();i++){
				if((table1->mint)[attr_list1[i]]!=0){
					int push_index = (table1->mint)[attr_list1[i]]-1;
					(ans->vint)[push_index].push_back(string_to_int((it->first)[i]));
				}
				else{
					int push_index = (table1->mstring)[attr_list1[i]]-1;
					(ans->vstring)[push_index].push_back((it->first)[i]);

				}
			}
		}
	}

	delete table1; // free extra memory
	delete table2;

	return ans; // return final answer

}


struct table* set_difference(struct table* table1, struct table* table2){
	// similar above implementation just both tables are provided as input
	vector<string> attr1,attr2;
	attr1 = (table1->tot_index);
	attr2 = (table2->tot_index);

	if(attr1.size()!=attr2.size()){
		cout << "Problem in Arity !!!" << endl;
		return NULL;
	}
	for(int i=0;i<attr1.size();i++){
		if((table1->mint).count(attr1[i])!=(table2->mint).count(attr2[i])){
			cout << "Problem in Arity !!!" << endl;
			return NULL;
		}
	}

	map<vector<string>, int> map1;
	map<vector<string>, int> map2;

	table* ans = new table();
	ans->mint = table1->mint;
	ans->mstring = table1->mstring;
	ans->attr_index = table1->attr_index;
	ans->tot_index = table1->tot_index;

	vector<string> aux_string;
	vector<int> aux_int;
	for(int i=0;i<(table1->mint).size();i++){
		(ans->vint).push_back(aux_int);
	}
	for(int i=0;i<(table1->mstring).size();i++){
		(ans->vstring).push_back(aux_string);
	}

	vector<string> attr_list1 = table1->tot_index;
	vector<string> attr_list2 = table2->tot_index;


	int tuples1 = 0;
	if((table1->mint).size()!=0){
		tuples1 = (table1->vint)[0].size();
	}
	else if((table1->mstring).size()!=0){
		tuples1 = (table1->vstring)[0].size();
	}
	else{
		cout << "Empty Table" << endl;
		return NULL;
	}

	vector<string> v1;

	for(int i=0;i<tuples1;i++){
		for(int j=0;j<attr_list1.size();j++){
			if((table1->mint)[attr_list1[j]]!=0){
				v1.push_back(int_to_string((table1->vint)[(table1->mint)[attr_list1[j]]-1][i]));
			}
			else{
				v1.push_back((table1->vstring)[(table1->mstring)[attr_list1[j]]-1][i]);
			}
		}
		map1[v1] = 1;
		v1.clear();
	}

	v1.clear();

	int tuples2 = 0;
	if((table2->mint).size()!=0){
		tuples2 = (table2->vint)[0].size();
	}
	else if((table2->mstring).size()!=0){
		tuples2 = (table2->vstring)[0].size();
	}
	else{
		cout << "Empty Table" << endl;
		return NULL;
	}

	for(int i=0;i<tuples2;i++){
		for(int j=0;j<attr_list2.size();j++){
			if((table2->mint)[attr_list2[j]]!=0){
				v1.push_back(int_to_string((table2->vint)[(table2->mint)[attr_list2[j]]-1][i]));
			}
			else{
				v1.push_back((table2->vstring)[(table2->mstring)[attr_list2[j]]-1][i]);
			}
		}
		map2[v1] = 1;
		v1.clear();
	}

	for(map<vector<string>, int>::iterator it=map1.begin();it!=map1.end();++it){
		if(map2[it->first]==0){
			for(int i=0;i<attr_list1.size();i++){
				if((table1->mint)[attr_list1[i]]!=0){
					int push_index = (table1->mint)[attr_list1[i]]-1;
					(ans->vint)[push_index].push_back(string_to_int((it->first)[i]));
				}
				else{
					int push_index = (table1->mstring)[attr_list1[i]]-1;
					(ans->vstring)[push_index].push_back((it->first)[i]);

				}
			}
		}
	}


	delete table1;
	delete table2;

	return ans;

}





