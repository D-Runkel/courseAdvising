#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

struct Course
{
	string courseId;
	string name = "";
	vector<string> preReqs;
};

struct Node
{
	Course course;
	Node* right;
	Node* left;

	Node()
	{
		left = nullptr;
		right = nullptr;
	}

	Node(Course aCourse) : Node()
	{
		course = aCourse;
	}
};

class BinaryTree
{
private:
	Node* root;
	void printAlphaNum(Node* node);
	void addNode(Node* node, Course course);

	public:
		void PrintAlphaNum();
		Course search(string courseId);
		void PrintCourse(Course course);
		void AddNode(Course course);
		void loadCSV(string path);

		BinaryTree()
		{
			root = nullptr;
		}
};

//I just included this into this file for simplicity reasons
// I ended up passing the tree to the load CSV function, because
// I was getting a weird bug keeping it in the class
bool checkCSV(string path);
