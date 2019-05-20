//Test file - feel free to modify it all you want.
//Submitty will use an instructor copy to test your class, and will not use your .cpp file.

#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include "BPlusTree.h"

void TemplateTest();
void SmallTreeCopyTest();
void EmptyTreeTest(std::ofstream& outfile);
void RealTreeTestNoPrint();
void RealTreeTestPrint(std::ofstream& outfile);
void ExtraCreditTest(std::ofstream& outfile);

int main(int argc, char* argv[]){
	if (argc!=2){
		std::cerr << "Correct usage is " << argv[0] << " [output file]" << std::endl;
		return -1;
	}
	std::ofstream outfile(argv[1]);
	if(!outfile){
		std::cerr << "Failed to open " << argv[1] << " for writing." << std::endl;
		return -1;
	}

	//Comment out whichever tests you don't want to run. Remove one std::endl from your last test.
	TemplateTest();
	outfile << "TemplateTest() complete!" << std::endl << std::endl;

	SmallTreeCopyTest();
	outfile << "SmallTreeCopyTest() complete!" << std::endl << std::endl;

	EmptyTreeTest(outfile);
	outfile << "EmptyTreeTest() complete!" << std::endl << std::endl;

	RealTreeTestNoPrint();
	outfile << "RealTreeTestNoPrint() complete!" << std::endl << std::endl;

	RealTreeTestPrint(outfile);
	outfile << "RealTreeTestPrint() complete!" << std::endl;

	ExtraCreditTest(outfile);
	outfile << "ExtraCreditTest() complete!" << std::endl;

	return 0;
}

void TemplateTest(){
	BPlusTree<int> b1(3);
	BPlusTree<int> b2(4);
	BPlusTree<std::string> b3(3);
	BPlusTree<std::string> b4(4);

	b1.insert(17);
	b2.insert(12);
	b3.insert("kwyjibo");
	b4.insert("obijywk");

	assert(b1.find(17));
	assert(b1.find(17)->contains(17));
	assert(!b1.find(17)->contains(12));

	assert(b2.find(12));
	assert(b2.find(12)->contains(12));
	assert(!b2.find(12)->contains(17));

	assert(b3.find("kwyjibo"));
	assert(b3.find("kwyjibo")->contains("kwyjibo"));
	assert(!b3.find("kwyjibo")->contains("kwyjib"));

	assert(b4.find("obijywk"));
	assert(b4.find("obijywk")->contains("obijywk"));
	assert(!b4.find("obijywk")->contains("pizza"));
}

void SmallTreeCopyTest(){
	BPlusTree<int> b1(4);
	assert(!b1.find(3));
	b1.insert(3);
	BPlusTree<int> b2(b1);
	b2.insert(4);
	b1.insert(5);

	assert(b1.find(3));
	assert(b1.find(3)->contains(3));
	assert(b1.find(4));
	assert(!b1.find(4)->contains(4));
	assert(b1.find(5));
	assert(b1.find(5)->contains(5));
	assert(b1.find(5)->contains(3));
	assert(b1.find(3)->contains(5));
	assert(!b1.find(3)->get_parent());
	assert(b2.find(4));
	assert(b2.find(4)->contains(4));
	assert(b2.find(4)->contains(3));
	assert(!b2.find(4)->contains(5));
	assert(!b2.find(4)->get_parent());

	BPlusTree<int> b4(3);
	BPlusTree<int> b5(3);
	b5 = b4;
	b5.insert(11);
	b4.insert(10);
	assert(b5.find(11));
	assert(b5.find(11)->contains(11));
	assert(!b5.find(11)->contains(10));
	assert(b4.find(10));
	assert(b4.find(10)->contains(10));
	assert(!b4.find(10)->contains(11));
}

void EmptyTreeTest(std::ofstream& outfile){
	BPlusTree<std::string> b(127);
	b.print_sideways(outfile);
	b.print_BFS(outfile);
	assert(!b.find("a"));
}

void RealTreeTestNoPrint(){
	BPlusTree<int> b1(3);
	BPlusTree<int> b2(3);
	for(int i=1; i<=6; i++){
		b1.insert(i);
		b2.insert(7-i);
	}

	assert(b1.find(3));
	for(int i=1; i<=6; i++){
		assert(b1.find(i));
		for(int j=1; j<=6; j++){
			if(i!=j){
				if(i<5 || j<5){
					assert(!b1.find(i)->contains(j));
				}
				else{
					assert(b1.find(i)->contains(j));
				}
			}
			else{
				assert(b1.find(i)->contains(j));				
			}
		}
		assert(b1.find(i)->get_parent());
		assert(b1.find(i)->get_parent()->get_parent());
		assert(!b1.find(i)->get_parent()->get_parent()->get_parent());
		assert(b2.find(i));
		assert(b2.find(i)->contains(i));
		if(i%2){
			assert(b2.find(i)->contains(i+1));
		}
		assert(b2.find(i)->get_parent());
		assert(!b2.find(i)->get_parent()->get_parent());

	}
}

void RealTreeTestPrint(std::ofstream& outfile){
	BPlusTree<int> b1(3);
	BPlusTree<int> b2(3);
	for(int i=1; i<=6; i++){
		b1.insert(i);
		b2.insert(7-i);
	}

	b1.print_sideways(outfile);
	outfile << std::endl;
	b1.print_BFS(outfile);
	outfile << std::endl;
	b2.print_sideways(outfile);
	outfile << std::endl;
	b2.print_BFS(outfile);
	outfile << std::endl;
}

void ExtraCreditTest(std::ofstream& outfile){
	BPlusTree<int> b(3);
	b.insert(10);
	b.insert(32);
	b.insert(43);
	b.insert(40);
	b.insert(37);
	b.insert(16);
	b.insert(25);
	b.insert(23);
	b.insert(7);
	b.insert(1);
	b.insert(39);
	b.insert(28);
	b.insert(45);
	outfile << "=============" << std::endl;
	b.print_sideways(outfile);
	outfile << "=============";
	outfile << std::endl;
	b.print_BFS_pretty(outfile);
	outfile << std::endl;
}
