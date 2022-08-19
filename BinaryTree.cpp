#include "BinaryTree.h"


using namespace std;

/**
* Function Name: checkCSV
* @params path, the file path
* @returns true if file is valid, false if invlaid
* Description: Check the file for formating errors,
* such as no name or ID. 
**/
bool checkCSV(string path)
{
	// open the file at the path
	fstream fin;
	fin.open(path, ios::in);
	try
	{
		if (!fin.is_open())
		{
			//if the file doesnt open, throw exception
			throw new exception("File path not found.");
		}

		//declare temporary varible to use 
		vector<string> preReqList, courseIds, row;
		string line, element;
		
		
		//while there is another input
		while (fin.peek() != EOF)
		{
			//clear the last row of values
			row.clear();

			//read the line and split it at the commas
			getline(fin, line);
			stringstream s(line);

			//assemble a row vector with the peices
			while (getline(s, element, ','))
			{
				row.push_back(element);
			}

			//if the row contains less than 2 elements, something is missing in our file and we
			//need to throw an error (this checks for elements 0 and 1)
			if (row.size() < 1)
			{
				throw new exception("File format error, check the file and resubmit");
			}

			// add the courseId to the courseId list for comparison later
			courseIds.push_back(row.at(0));

			//logic to add the preReqs to the list of preReqs
			for (int i = 2; i < row.size(); i++)
			{
				preReqList.push_back(row.at(i));
			}
		}

		fin.close();

		//after the file is ran through, we compare courseIds and preReqs in a nested loop
		for (int i = 0; i < preReqList.size(); i++)
		{
			bool match = false;

			for (int j = 0; j < courseIds.size(); j++)
			{
				if (courseIds.at(j) == preReqList.at(i))
				{
					match = true;
				}
			}

			//if the entire inner loop is ran through with no matches, we throw error
			if (match == false)
			{
				throw new exception("Prereq not included in course list.");
			}
		}
		//if all is well 
		return true;
	}
	catch (exception& e)
	{
		cout << e.what() << endl;
		fin.close();
		return false;
	}
}

/*
* Name: LoadCSV
* Desc: Loads a csv into the binary tree in memory
* @params path, the path of the file to open
* @params BST, the tree to load the file into
*/
void BinaryTree::loadCSV(string path)
{
	// open the file at the path
	fstream fin;
	fin.open(path, ios::in);
	try
	{
		if (!fin.is_open())
		{
			//if the file doesnt open, throw exception
			throw new exception("File path not found.");
		}

		//declare temporary varible to use 
		vector<string> preReqList, row;
		string line, element;


		//while there is another input
		while (fin.peek() != EOF)
		{
			//clear the last row of values
			row.clear();
			preReqList.clear();

			//read the line and split it at the commas
			getline(fin, line);
			stringstream s(line);

			//assemble a row vector with the peices
			while (getline(s, element, ','))
			{
				row.push_back(element);
			}

			//logic to add the preReqs to the list of preReqs
			for (int i = 2; i < row.size(); i++)
			{
				preReqList.push_back(row.at(i));
			}

			Course* course = new Course();
			course->courseId = row.at(0);
			course->name = row.at(1);
			course->preReqs = preReqList;

			this->AddNode(*course);
		}

		fin.close();

	}
	catch (exception& e)
	{
		cout << e.what() << endl;
		fin.close();
	}
}
/*
* Name: AddNode
* Desc: adds a node with the desired course to the binary tree.
* @params course, the course object to add
*/
void BinaryTree::AddNode(Course course)
{
	if (root == nullptr)
	{
		root = new Node(course);
	}
	else
	{
		addNode(root, course);
	}
}

/*
* Name: addNode
* desc: private recursive function to add a node to the tree
* @params node, the current node
* @params course, the course to add
*/
void BinaryTree::addNode(Node* node, Course course)  
{
	if (node->course.courseId > course.courseId)
	{
		if (node->left == nullptr)
		{
			node->left = new Node(course);
		}
		else
		{
			addNode(node->left, course);
		}
	}
	else
	{
		if (node->right == nullptr)
		{
			node->right = new Node(course);
		}
		else
		{
			addNode(node->right, course);
		}
	}
}

/*
* Name: PrintAlphaNum
* Access: public
* desc: Prints courses in alphanumeric order
*/
void BinaryTree::PrintAlphaNum()
{
	if (root == nullptr)
	{
		return;
	}
	else
	{
		cout << "CourseId| Course Name\n";
		printAlphaNum(root);
	}
}
/*
* Name: printAlphaNum
* desc: recursive call to print the courses in alphnumeric order
*/
void BinaryTree::printAlphaNum(Node* node)
{
	if (node != nullptr)
	{
		printAlphaNum(node->left);

		cout << node->course.courseId << " | "
			<< node->course.name << endl;

		printAlphaNum(node->right);
	}
}
/*
* Name: AddNode
* Desc: searches the tree for the desired course
* @params courseId, the courseId to search for
* @returns course with matching ID, or empty course
*/
Course BinaryTree::search(string courseId)
{
	Course course;

	if (root == nullptr)
	{
		return course;
	}
	else if (root->course.courseId == courseId)
	{
		return root->course;
	}

	Node* currNode = root;


	while (currNode != nullptr)
		{
		if (currNode->course.courseId == courseId)
		{
			return currNode->course;
		}
		if (courseId < currNode->course.courseId)
		{
			currNode = currNode->left;
			}
		else
		{
			currNode = currNode->right;
		}
	}

	return course;

}
/*
* Name: PrintCourse
* Desc: Prints the course and prerequisite courses
* @params  course, the course to print
*/
void BinaryTree::PrintCourse(Course course)
{
	cout << "\n\n|CourseID| Course Name\n";
	cout <<"|" << course.courseId << " | " << course.name << endl;

	if (course.preReqs.size() > 0)
	{
		cout << "\nPREQUISITE COURSES: \n";
		cout << "|CourseID| Course Name\n";
	}

	for (int i = 0; i < course.preReqs.size(); i++)
	{
		Course tmp = this->search(course.preReqs.at(i));
		if (tmp.name != "")
		{
			cout << "|" << tmp.courseId << " | " << tmp.name << endl;
		}
	}

	cout << endl;
	
}
