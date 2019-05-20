#include <iostream>
#include <list>
#include <vector>
#include <cassert>



void print(const std::string &label, const std::list<std::string> &data) {
  std::cout << label;
  for (std::list<std::string>::const_iterator itr = data.begin();
       itr != data.end(); itr++) {
    std::cout << " " << *itr;
  }
  std::cout << std::endl;
}


void update(std::list<std::string>& data,
            const std::vector<std::string>& add,
            const std::vector<std::string>& remove) {
  for (unsigned int i = 0; i < add.size(); ++i) {
    for (std::list<std::string>::iterator itr = data.begin(); itr != data.end(); ++itr) {
      if (add[i] == *itr) break;
      else if (add[i] < *itr) {
        data.insert(itr, add[i]);
        break;
      }
    }
    // empty data
    if (data.begin() == data.end()) {
      for (unsigned int i = 0; i < add.size(); ++i) data.push_back(add[i]);
    }
  }
  for (unsigned int i = 0; i < remove.size(); ++i) {
    for (std::list<std::string>::iterator itr = data.begin(); itr != data.end(); ++itr) {
      if (itr->find(remove[i]) != std::string::npos) {
        itr = data.erase(itr);
	    --itr;
      }
    }
  }
}


int main() {


  // Examples demonstrating STL string find:
  // catfish contains the substring fish
  assert (std::string("catfish").find(std::string("fish")) != std::string::npos);
  // fish contains the substring fish
  assert (std::string("fish").find(std::string("fish")) != std::string::npos);
  // fish does not contain the substring catfish
  assert (std::string("fish").find(std::string("catfish")) == std::string::npos);


  // A simple example:
  std::list<std::string> data;
  data.push_back("antelope");
  data.push_back("catfish");
  data.push_back("giraffe");
  data.push_back("llama");
  data.push_back("jellyfish");
  data.push_back("whale_shark");
  data.push_back("zebra");

  std::vector<std::string> add;
  add.push_back("tiger");
  add.push_back("llama");
  add.push_back("elephant");
  
  std::vector<std::string> remove;
  remove.push_back("fish");
  remove.push_back("bear");
  remove.push_back("whale");
  
  print ("before:",data);
  update(data,add,remove);
  print ("after: ",data);
  
  // at the end, data should contain: antelope elephant giraffe llama tiger zebra
  assert (data.size() == 6);

  // example 2: 0 -> 1 -> 0
  std::list<std::string> data1;
  std::vector<std::string> add1;
  add1.push_back("tiger");
  std::vector<std::string> remove1;
  remove1.push_back("tiger");
  std::cout << std::endl;
  print ("before:",data1);
  update(data1,add1,remove1);
  print ("after: ",data1);

  // example 3: 0 -> 0 -> 0
  std::vector<std::string> add2;
  std::cout << std::endl;
  print ("before:",data1);
  update(data1,add2,remove1);
  print ("after: ",data1);

  // example 4: 0 -> 1 -> 1
  std::vector<std::string> remove2;
  std::cout << std::endl;
  print ("before:",data1);
  update(data1,add1,remove2);
  print ("after: ",data1);
    
    //example 5: 1 -> 1 -> 0
    std::cout << std::endl;
    print ("before:",data1);
    update(data1,add1,remove1);
    print ("after: ",data1);
    
    //example 6: 1 -> 1 -> 1
    std::cout << std::endl;
    print ("before:",data1);
    update(data1,add1,remove2);
    print ("after: ",data1);

  return 0;
}

