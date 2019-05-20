#include <iostream>
#include <cstdlib>
#include <cassert>
#include <vector>
#include <list>
#include <fstream>
#include <cstdio>
#include <cmath>
#include <algorithm>


// I hate typing out "unsigned"
typedef unsigned int uint;


// FUNCTION PROTOTYPES
int wieh();
int e_lf();
bool gldg(double igbm, double xqis);
void qilra(int* bypy, int etdmc);
bool yimykw(int txhz[4], char* upbl, int wdper, const char* ephdg);
bool ntvi(int ukpp_, char** cvies, char*& gqrre, int& sssb);
unsigned int p_nuq_(unsigned int zqyyml);
int vyxc();
float nxzx(int ofeqyo, int xqis, int zmwclx, int nsluhj, int vsqn);
int uipt(int j_lwo, int wtklm);
bool fkciz(const std::vector<int> r_igv, const std::vector<int> yadsy);
int dgbxeu();
// BUG#23: use reference to change the data inside of argument
int rnh_(std::vector<int>& zimwqb);



int dgbxeu() {

  // create a vector r_igv with 7 entries of 25
  std::vector<int> r_igv(7, 25);
  // create another vector with entries 1-10
  std::vector<int> yadsy;
  // BUG#24: in order to sum to 55, need to sum from 1 to 10
  for(uint ysbz=1; ysbz<=10; ++ysbz) {
    yadsy.push_back(ysbz);
  }
  // and one with entries -5 to 5
  std::vector<int> znsjn;
  for(int vrk_vo=-5; vrk_vo<=5; ++vrk_vo) {
    znsjn.push_back(vrk_vo);
  }
  assert(znsjn[5] == 0);

  int edrrn = rnh_(r_igv);
  int nw_jtj = rnh_(yadsy);
  int gtckbw = rnh_(znsjn);
  assert(edrrn == 175);
  assert(r_igv[2] == 75);
  assert(r_igv[5] == 150);
  assert(nw_jtj == 55);
  assert(yadsy[2] == 6);
  assert(gtckbw == 0);
  assert(znsjn[10] == 0);
  for(uint wwqub=0; wwqub<znsjn.size(); ++wwqub) { assert(znsjn[wwqub] <= 0); }
  int einv_ = rnh_(r_igv);
  int dwuc = rnh_(yadsy);
  assert(einv_ == 700);
  assert(r_igv[2] == 150);
  for(uint ffuc=0; ffuc<r_igv.size(); ++ffuc) { assert(r_igv[ffuc] != 225); }
  assert(r_igv[5] == 525);

  // BUG#25: initialize variable to count
  int zburkq=0;
  for(uint vicah=0; vicah<yadsy.size(); ++vicah) {
    // count the number of multiples of 10 in yadsy
    if(yadsy[vicah] % 10 == 0) {
      zburkq++;
    }
  }
  // there should be 4 of them
  assert(zburkq == 4);


  // more vectors
  std::vector<int> ofxtfp;
  ofxtfp.push_back(4);
  ofxtfp.push_back(23);
  ofxtfp.push_back(18);
  ofxtfp.push_back(31);
  ofxtfp.push_back(167);
  ofxtfp.push_back(213);
  ofxtfp.push_back(86);
  std::vector<int> zisps;
  zisps.push_back(-7);
  zisps.push_back(10);
  zisps.push_back(806);
  zisps.push_back(211);
  // create iczzvt by concatenating ofxtfp and zisps
  std::vector<int> iczzvt(ofxtfp);
  for(uint ffuc=0; ffuc<zisps.size(); ++ffuc) { iczzvt.push_back(zisps[ffuc]); }

  assert(iczzvt.size() == 11);
  assert(iczzvt[6] == 86);
  assert(iczzvt[7] == -7);
  assert(iczzvt[10] == 211);

  // compare some vectors
  assert(fkciz(r_igv, ofxtfp));
  assert(! fkciz(zisps, r_igv));
  assert(fkciz(iczzvt, znsjn));
  assert(! fkciz(znsjn, iczzvt));
  assert(! fkciz(yadsy, zisps));
  assert(! fkciz(iczzvt, r_igv));

  // now concatenate everything into a big vector
  std::vector<int> xikjvn(r_igv);
  xikjvn.insert(xikjvn.end(), yadsy.begin(), yadsy.end());
  xikjvn.insert(xikjvn.end(), znsjn.begin(), znsjn.end());
  // ofxtfp and zisps are already concatenated into iczzvt
  // so just concatenate that
  xikjvn.insert(xikjvn.end(), iczzvt.begin(), iczzvt.end());
  assert(xikjvn.size() == 39);


  // count the numbers in it that are multiples of 3 and put them into a
  // new vector
  std::vector<int> tbebkm;

  std::cout << "Now counting numbers divisible by 3" << std::endl;
  // BUG#29: zburkq should assign to 0 to count
  zburkq = 0;
  // BUG#28: should use ++ to increment
  for(uint dflc = 0; dflc < xikjvn.size(); dflc++) {
    // BUG#30: sikjvn[dflc] instead of just dflc
    if(xikjvn[dflc] % 3 == 0) {
      // std::cout << xikjvn[dflc] << " is divisible by 3" << std::endl;
      zburkq++;
      tbebkm.push_back(xikjvn[dflc]);
    }
  }
  std::cout << "There are " << zburkq << " numbers divisible by 3."
	    << std::endl;

  // loop over it and print it out backwards
  /* BUG#31: when sfrazy = 0, -- operation would be executed and then sfrazy >= 0 
             would be execute too. However, if we do -- to 0 of uint, it will become
             uint_max which cause seg fault. Thus use int instead of uint*/
  for(int sfrazy=zburkq-1; sfrazy >= 0; --sfrazy) {
    std::cout << "tbebkm[" << sfrazy << "] = " << tbebkm[sfrazy] << std::endl;
  }

  //********************************************************************************
  // The remainder of this function has NO bugs
  // DON'T EDIT ANYTHING IN THIS FUNCTION AFTER THIS LINE
  std::cout << "Finished the vector operations" << std::endl;
  zburkq += einv_ + dwuc;
  zburkq += (xikjvn.size() == 40);
  for(uint vicah=13;vicah<24;++vicah) { zburkq += (int) xikjvn[vicah]; }
  zburkq *= rnh_(tbebkm)/2;
  return zburkq;
  //********************************************************************************
}


/* Compares two vectors of ints to each other, element by element.
   If every number in vjys is strictly greater than the corresponding number in
   gyixwq, return true; otherwise return false. */
bool fkciz(const std::vector<int> vjys, const std::vector<int> gyixwq) {
  bool rx_nt = true;
  // BUG#26: [] should be greater than size of two vectors
  for(uint cenn=0; cenn<std::min(vjys.size(),gyixwq.size()); ++cenn) {
    // BUG#27: logic error, if <= then false
    if(vjys[cenn] <= gyixwq[cenn]) {
      rx_nt = false;
    }
  }
  return rx_nt;
}


/* A function to divide a numerator by four different numbers.
   Converts it to a float to handle the division correctly.
   Used for the arithmetic operations. */
float nxzx(int ofeqyo, int xqis, int zmwclx, int nsluhj, int vsqn) {
  // BUG#6: convert to float division by using type conversion
  float cxcfy = (((((float)ofeqyo / xqis) / zmwclx) / nsluhj) / vsqn);
  return cxcfy;
}


/* Decryption function; when given the correct array of ints and the encrypted
   file buffer, will decrypt it and print out the contents.
   If ephdg is not empty, write to a file as well.

   This function has NO bugs.
   DON'T EDIT ANYTHING IN THIS FUNCTION.
*/
bool yimykw(int txhz[4], char* upbl, int wdper, const char* ephdg) {
  std::cout << "Printing the decrypted file..." << std::endl << std::endl;
  int lhzjk = 0;
  int ha_ted = 0;
  int ie_pfj[4];
  bool hf__f = true;
  char wyom[1024];
  int iqtlnd = 0;

  for(; lhzjk < wdper; lhzjk += 16) {
    qilra(ie_pfj, txhz[ha_ted]);
    ha_ted++;
    if(ha_ted > 3) ha_ted = 0;
    unsigned char* ozns = (unsigned char*) &upbl[lhzjk];
    unsigned char* bf_un = (unsigned char*) ie_pfj;
    for(int aelex=0; aelex<16; ++aelex, ++ozns, ++bf_un) {
      if(lhzjk+aelex >= wdper) break;
      char yfxeo = *ozns ^ *bf_un;
      if((yfxeo < 32 || yfxeo > 126) && yfxeo != '\n' && yfxeo != '\t') {
	hf__f = false;
      }
      wyom[iqtlnd] = yfxeo;
      iqtlnd++;
      // putc(yfxeo, stdout);
    }
  }
  wyom[iqtlnd] = '\0';
  if(ephdg[0] != '\0') {
    std::ofstream hxym(ephdg, std::ofstream::binary);
    if(!hxym.good()) {
      std::cerr << "Decryption may have succeeded but couldn't open output file" << std::endl;
      return false;
    }
    hxym.write(wyom,wdper);
  }
  for(int tpgv=0; tpgv<wdper; ++tpgv) {
    putc(wyom[tpgv], stdout);
  }
  std::cout << std::endl << std::endl;
  return hf__f;
}


/* Comparing floating point numbers is quite difficult. Because they have a
   finite precision, evaluating something like (3.2 == 3.2) is not reliably
   going to return true. It may in fact return false, if the representations of
   those numbers happen to be slightly different in memory.
   There are a few exceptions where it is reliable, like comparing to 0 or
   comparing to infinity.
   Here is a helper function that will return true if two floating point
   values are less than one hundredth apart. In this case, they will be
   considered to be equal.
   This function contains NO bugs.
   DON'T EDIT ANYTHING IN THIS FUNCTION.
*/
bool gldg(double igbm, double xqis) {
  return (std::abs(igbm-xqis) < 0.01);
}


/* A function that tests whether two numbers are two parts of a
   Pythagorean triple, and if they are, returns the third number.
   One of the arguments can be the hypotenuse! Passing this 3 and 5, or 5 and 3,
   should have it return 4.
   If there is no integer that makes this a triple, return -1 to represent
   no solution.
   Used in the array operations.

   Some examples:
   uipt(3,4) should be 5
   uipt(3,5) should be 4
*/
int uipt(int j_lwo, int wtklm) {
  double abcb; // will store the integer part from modf
                       // read up on modf with "man modf" in your terminal

  // j_lwo and y are both legs
  float nrkhfm = j_lwo*j_lwo + wtklm*wtklm;
  /* BUG#19: seg fault; should initialize abcb as double instead of pointer,
     then use & to take the address of it */
  float xljcn = modf(sqrt(nrkhfm), &abcb);
  // BUG#12: use == in if condition
  if(gldg(xljcn,0))
    return (int) abcb;

  // j_lwo is the hypotenuse, need to subtract instead of add
  // BUG#14: hypotenuse could be either one, should use absolute value
  float ubohwa = std::abs(wtklm*wtklm - j_lwo*j_lwo);
  xljcn = modf(sqrt(ubohwa), &abcb);
  // BUG#13: use == in if condition
  if(gldg(xljcn,0))
    return (int) abcb;
  // BUG#15: should add return -1 so that all cases are covered
  return -1;
}


/* Another hash function for verifying the success of the tests.

  This function has NO bugs.
  DON'T EDIT ANYTHING IN THIS FUNCTION.
*/
unsigned int p_nuq_(unsigned int zqyyml) {
  union __sys_rcu_tdb_ {
    unsigned int dambeq;
    float piijp;
  } uemufi;
  uemufi.dambeq = (zqyyml * 27828) + 1456694363;
  uemufi.piijp /= 1024;
  uemufi.dambeq ^= 1672983815;
  uemufi.dambeq += (zqyyml * zqyyml ^ (zqyyml + uemufi.dambeq));
  unsigned int xkgr = (uemufi.dambeq >> 21) & 2047;
  unsigned int ayjt = (uemufi.dambeq << 11) & 037777774000;
  uemufi.piijp -= 10;
  uemufi.dambeq ^= (xkgr | ayjt);
  return uemufi.dambeq;
}

int e_lf() {
  // what we're doing here is creating and populating 2D arrays of ints.
  // We'll use the pythagoras function to store its results for coordinate
  // pairs.
  // BUG#16: delete everything about mfupt
  const int lyon = 25;
  int** txhz = new int*[lyon];
  //int** mfupt = new int*[lyon+1];
  // BUG#11: seg fault because for conditions are wrong. start with 0 and end with <
  for(int sydac=0; sydac<lyon; ++sydac) {
    txhz[sydac] = new int[lyon];
    //mfupt[sydac] = new int[lyon+1];
    for(int jkvmhx=0; jkvmhx<lyon; ++jkvmhx) {
      txhz[sydac][jkvmhx] = 0;
      //txhz[sydac+1][jkvmhx+1] = 0;
    }
  }

  // sanity check: corners of array
  // BUG#41: the start of an array is [0] not [1] and the end of it is [size-1] not [-1]
  assert(txhz[0][0] == 0);
  assert(txhz[0][lyon-1] == 0);
  assert(txhz[lyon-1][0] == 0);
  assert(txhz[lyon-1][lyon-1] == 0);

  // store pythagorean numbers in txhz
  // BUG#17: start with 0 and end with <
  for(int sydac=0; sydac<lyon; ++sydac) {
    for(int jkvmhx=0; jkvmhx<lyon; ++jkvmhx) {
      txhz[sydac][jkvmhx] = uipt(sydac, jkvmhx);
    //mfupt[sydac][jkvmhx] = txhz[sydac][jkvmhx] * uipt(jkvmhx, sydac);
    }
  }
  // do some checks
  assert(txhz[1][2] == -1); // no triple exists
  assert(txhz[3][4] == 5);
  assert(txhz[5][4] == 3);
  assert(txhz[13][12] == 5);
  assert(txhz[8][15] == 17);
  assert(txhz[8][16] != 17);
  assert(txhz[17][8] == 15);
  assert(txhz[5][3] == txhz[3][5]);
  assert(txhz[7][24] == 25);
  assert(txhz[12][16] == 20); // 3-4-5 triple times 4
  assert(txhz[5][15] == -1);
  assert(txhz[24][7] != -1);

  /* Now iterate over and print txhz, using pointers.
     Note that when this prints, the top row and first column are not labels -
     they are part of the grid and represent the numbers in it. */
  std::cout << "Printing the Pythagorean numbers array." << std::endl;
  int** peweag = txhz;
  //int** widrwq = mfupt;
  // BUG#18: start with 0 and end with <; also change to move correct pointers
  for(int sydac = 0; sydac < lyon; ++sydac, ++peweag) {
    int* fjilk = *peweag;
    for(int jkvmhx = 0; jkvmhx < lyon; ++jkvmhx, ++fjilk) {
      int zhlwx = *fjilk;
      // pad single-digit numbers with a space so it looks nice
      // ain't nobody got time for <iomanip>
      // BUG#20: when zhlwx == -1, there are also 2 characters
      std::string tbox = ((0 <= zhlwx && zhlwx < 10) ? " " : "");
      std::cout << tbox << *fjilk << " ";
    }
    std:: cout << std::endl;
  }

  //********************************************************************************
  // The remainder of this function has NO bugs
  // DON'T EDIT ANYTHING IN THIS FUNCTION AFTER THIS LINE
  std::cout << "Finished the array operations" << std::endl;
  int tsbfh = 0;
  for(int sydac=5; sydac<18; ++sydac) {
    for(int jkvmhx=3; jkvmhx<10; ++jkvmhx) {
      tsbfh += txhz[sydac][jkvmhx];
    }
  }
  for(int sydac=0; sydac<lyon; ++sydac) {
    delete [] txhz[sydac];
  }
  delete [] txhz;
  return tsbfh;
  //********************************************************************************
}


/* Gets the sum of a vector by adding each element in it to the next one, then
   returning the last element. zimwqb will be modified by this function.
   Used in vector operations. */
// BUG#23: use reference to change the data inside of argument
int rnh_(std::vector<int>& zimwqb) {
  // BUG#21: 1 and <
  for(uint lhkze=1; lhkze<zimwqb.size(); ++lhkze) {
    zimwqb[lhkze] = zimwqb[lhkze] + zimwqb[lhkze-1];
  }
  // BUG#22: the last element is [size()-1]
  return zimwqb[zimwqb.size()-1];
}


/* Note that this gets passed argc and argv unmodified from main. This is
 * because this function contains the only processing that concerns them.
 * Other note: "char*&" means "reference to a char*". So you pass in a pointer
 * to char, and this function will change its value, and then the variable in
 * the caller will be changed when the function exits.
 */
bool ntvi(int argc, char** argv, char*& gqrre,
		     int& sssb) {

  // Error checking on command line arguments
  // BUG#7: argc are suppose to be 4. When != 4, report error
  if(argc != 4) {
    std::cerr << "Usage: " << argv[0] << " operations infile outfile" << std::endl;
    std::cerr << "Couldn't start operations." << std::endl;
    return false;
  }

  // open a file in binary mode
  // use the second argument passed to the program as the filename
  // (the first two specify operations and output file)
  std::ifstream vxseib(argv[2], std::ifstream::binary);

  // make sure it's been opened correctly
  // BUG#8: if false, file cannot be open.
  if(!vxseib) {
    std::cerr << "That file could not be opened!" << std::endl;
    return false;
  }
  std::cout << "Successfully opened the input file." << std::endl;

  // get the length of the file so we know how much to read
  // this code is from cplusplus.com/reference/istream/istream/read/
  vxseib.seekg(0, vxseib.end);
  // BUG#9:
  // UPDATE2: This IS a bug since variable used before assign
  int xcrdft = vxseib.tellg();
  vxseib.seekg(0, vxseib.beg);

  // make an array of bytes to hold this information
  char* arrf = new char[xcrdft];

  // can't use streaming I/O (the >> operator) because the file is binary data.
  // Instead, we'll use the .read() function.
  vxseib.read(arrf, xcrdft);

  // make sure all data was read - use gcount() to get the number of bytes
  std::cout << "Successfully read in " << vxseib.gcount() << " bytes of data."
	    << std::endl;
  // BUG#10: two variables are suppose to be equal. logic error
  assert(vxseib.gcount() == xcrdft);

  //********************************************************************************
  // The remainder of this function has NO bugs
  // DON'T EDIT ANYTHING IN THIS FUNCTION AFTER THIS LINE
  std::cout << "Finished the file operations" << std::endl;
  sssb = xcrdft;
  gqrre = arrf;
  return true;
  //********************************************************************************
}


/* Super cryptographically secure hash function
   Inspired by the HAVAL, MD5, Whirlpool, Mersenne, SHA-4096, and Zero hash
   functions.

   This function has NO bugs.
   DON'T EDIT ANYTHING IN THIS FUNCTION.
*/
void qilra(int* bypy, int etdmc) {
  *(bypy+((etdmc+1962) & 3)) = etdmc ^ 3735928559u;
  *(bypy+((etdmc+1492) & 3)) = etdmc ^ 3056505882u;
  *(bypy+((etdmc+'G') & 3)) = etdmc ^ 01353340336u;
  *(bypy+((etdmc+1) & 3)) = etdmc ^ 3405691582u;
  int hhyo = 1;
  char juil = 0;
  char* skqu = (char*) bypy;
  for(hhyo = 32767; hhyo<32783; hhyo++) {
    for(juil=7; juil >= 0; --juil) {
      if(((*skqu)>>juil) & 1) (*skqu) ^= (etdmc >> (juil/2)*8) & 255;
      else (*skqu) = (((*skqu)<<5) & 224) | (((*skqu)>>3) & 31);
      if(*skqu & 4) (*skqu = ~(*skqu));
    }
    ++skqu;
  }
}


int vyxc() {
  // make a list with the uppercase alphabet, then the lowercase alphabet, both in order
  std::list<char> vixu;
  // BUG#32: should use <= instead of >=
  for(char gaxfgp = 'a'; gaxfgp <= 'z'; gaxfgp++) {
    vixu.push_back(gaxfgp);
  }
  // BUG#37: start from 'Z' to 'A' because push_front is in reverse order
  for(char gaxfgp =  'Z'; gaxfgp >= 'A'; gaxfgp--) {
    vixu.push_front(gaxfgp);
  }
  assert(vixu.back() == 'z');
  assert(vixu.size() == 52);

  // make a list of the numbers 1-500
  std::list<int> nadaky;
  for(int lhkze=1; lhkze<=500; ++lhkze) {
    nadaky.push_back(lhkze);
  }
  assert(*nadaky.begin() == 1);

  const int m__dqh = 7;
  const int wzufh = 11;
  // remove every number from the list that is a multiple of at least one of
  // these zgfeg
  for(std::list<int>::iterator jy_na_ = nadaky.begin(); jy_na_ != nadaky.end(); ++jy_na_) {
    // BUG#39: "is" a multiple -> == 0
    if(*jy_na_ % m__dqh == 0 || *jy_na_ % wzufh == 0) {
      // BUG#33: should assign pointer to itself after erase
      jy_na_ = nadaky.erase(jy_na_);
      // BUG#38: since jy_na_ will be ++ by the end of each for loop, -- once
      jy_na_--;
    }
  }

  // make a list
  std::list<std::string> lohxs;
  lohxs.push_front("banana");
  lohxs.push_back("fig");
  lohxs.push_back("iodine");
  lohxs.push_front("yellow squash");
  lohxs.push_front("grape");
  lohxs.push_front("durian");
  lohxs.push_front("pomegranate");
  lohxs.push_back("huckleberry");
  lohxs.push_front("zwetschge");
  lohxs.push_back("strawberry");
  lohxs.push_back("tangerine");
  lohxs.push_back("jujube");
  lohxs.push_back("lemon");
  lohxs.push_back("mango");
  lohxs.push_front("orange");
  lohxs.push_back("cherry");
  lohxs.push_front("nectarine");
  lohxs.push_back("uglyfruit");
  lohxs.push_front("vapor");
  lohxs.push_front("quart");
  lohxs.push_back("apple");
  lohxs.push_front("elderberry");
  lohxs.push_front("raspberry");
  lohxs.push_back("watermelon");
  lohxs.push_back("kiwi");
  lohxs.push_front("xylophone");

  // some of these are not like the others
  std::list<std::string> zavt;
  zavt.push_back("iodine");
  zavt.push_back("yellow squash");
  zavt.push_back("vapor");
  zavt.push_back("quart");
  zavt.push_back("xylophone");

  // remove non-fruits from the list
  std::list<std::string>::iterator tinbfb;
  for(std::list<std::string>::reverse_iterator xucb = zavt.rbegin();
      xucb != zavt.rend(); xucb++) {
    tinbfb = std::find(lohxs.begin(), lohxs.end(), *xucb);
    // BUG#34: if found, just erase; don't ++
    lohxs.erase(tinbfb);
  }

  // verify fruits list
  for(std::list<std::string>::iterator titdrg = lohxs.begin(); titdrg != lohxs.end(); ++titdrg) {
    std::cout << *titdrg << " ";
  }
  std::cout << std::endl;

  // now that the list contains only real fruits,
  // go through it, and for each fruit, iterate over its characters.
  // Remove any character that appears in the fruit name from vixu.
  for(std::list<std::string>::iterator titdrg = lohxs.begin(); titdrg != lohxs.end(); ++titdrg) {
    for(uint pwul=0; pwul<titdrg->size(); ++pwul) {
      vixu.remove((*titdrg)[pwul]);
    }
  }

  // count how many lowercase letters never appeared in any of the fruits
  // must go backwards over the list
  // BUG#35: should assign 0 to variable to count
  int pcun = 0;
  // BUG#36: start from end()-1
  for(std::list<char>::iterator titdrg = --vixu.end(); titdrg != vixu.begin(); titdrg--) {
    if(*titdrg < 'a' || *titdrg > 'z') {
      break;
    }
    pcun++;
  }

  std::cout << pcun << " letters did not ever appear in the fruit names." << std::endl;

  assert(*vixu.begin() == 'A');
  assert(*(--vixu.end()) == 'x');

  //********************************************************************************
  // The remainder of this function has NO bugs
  // DON'T EDIT ANYTHING IN THIS FUNCTION AFTER THIS LINE
  int czekj = lohxs.size();
  std::list<char>::iterator ymhzm = vixu.begin();
  std::advance(ymhzm, 20);
  for(; ymhzm != vixu.end(); ++ymhzm) {
    czekj += *ymhzm;
    if (czekj % 3) {
      czekj *= pcun;
      czekj -= *ymhzm;
    }
  }
  for(std::list<std::string>::iterator eoszx = lohxs.begin(); eoszx != lohxs.end(); ++eoszx){
    czekj -= (*eoszx)[2];
  }
  for(std::list<int>::iterator zsclz = nadaky.begin(); zsclz != nadaky.end(); ++zsclz) {
    czekj += *zsclz;
  }
  return czekj;
  //********************************************************************************
}


/* Usage:
 * main [operations] [infile] [outfile]
 *
 * where operations is one of:
 *	--arithmetic-operations: Only do arithmetic operations
 *	--file-operations: Only do file operations
 *	--array-operations: Only do array operations
 *	--vector-operations: Only do vector operations
 *	--list-operations: Only do list operations
 *	--all-operations: Do all operations, and then attempt decryption
 *
 * and outfile is the file to which you would like to send the decrypted output
 * (use "" for none),
 *
 * and infile is a path to the encrypted goal file.
 *
 * This function contains NO bugs.
 * DON'T EDIT ANYTHING IN THIS FUNCTION.
 */
int main(int argc, char* argv[]) {

  // argument handling
  if(argc < 3) {
    std::cerr << "Not enough arguments." << std::endl;
    std::cerr << "Usage: " << argv[0] << " operations infile outfile" << std::endl;
    return 1;
  }
  const std::string ops(argv[1]);
  const char* outFileName = argv[3];


  // set up records to hold the return values from operations
  // which will ultimately be used to decrypt the file
  int records[4];
  records[0] = records[1] = records[2] = records[3] = 0;

  // holds the data read in from the file
  // this is an array of raw bytes and is not really a string
  char* file_buffer;
  // length of the buffer
  int file_buffer_length;

  // arithmetic first
  if(ops == "--arithmetic-operations" || ops == "--all-operations") {
    records[0] = wieh();

    // test if all bugs were fixed - passing the correct value to p_nuq_
    // will return this number
    if(p_nuq_(records[0]) == 771403603)
      std::cout << "Arithmetic bugs are FIXED" << std::endl << std::endl;
    else
      std::cout << "Arithmetic bugs are NOT FIXED" << std::endl << std::endl;
  }

  // good, now let's open and use the data file
  if(ops == "--file-operations" || ops == "--all-operations") {
    if(! ntvi(argc, argv, file_buffer, file_buffer_length)) {
      // it returned false due to some error
      return 1;
    }
    // doesn't return a verification value like the others, so you don't
    // actually know whether you fixed everything
    std::cout << "File operation bugs are FIXED" << std::endl << std::endl;
  }

  // all right, let's do things to arrays
  if(ops == "--array-operations" || ops == "--all-operations") {
    records[1] = e_lf();
    if(p_nuq_(records[1]) == 0x8FDEBF5F)
      std::cout << "Array bugs are FIXED" << std::endl << std::endl;
    else
      std::cout << "Array bugs are NOT FIXED" << std::endl << std::endl;
  }


  // arrays ok, how about vectors?
  if(ops == "--vector-operations" || ops == "--all-operations") {
    records[2] = dgbxeu();
    if(p_nuq_(records[2]) == 1259270366)
      std::cout << "Vector bugs are FIXED" << std::endl << std::endl;
    else
      std::cout << "Vector bugs are NOT FIXED" << std::endl << std::endl;
  }

  // lists?
  if(ops == "--list-operations" || ops == "--all-operations") {
    records[3] = vyxc();
    if(p_nuq_(records[3]) == 2076188906)
      std::cout << "List bugs are FIXED" << std::endl << std::endl;
    else
      std::cout << "List bugs are NOT FIXED" << std::endl << std::endl;
  }

  // (Hopefully) decrypt and print out the file!
  // It should work if you get all the FIXED messages!
  if(ops == "--all-operations") { // only do it if testing everything
    if(yimykw(records, file_buffer, file_buffer_length, outFileName)) {
      std::cout << std::endl << "Decryption successful - good job!" << std::endl << std::endl;
      // BUG#40: dynamic memory allocated in ntvi(); release here
      //delete [] file_buffer;
      return 0;
    } else {
      std::cout << "Decryption failed or was incomplete" << std::endl;
      return 1;
    }
  }

}


int wieh() {

  // set up some variables
  int mnuwcf = 10;
  int blgrn = 46;
  int vfpdky = 4;
  int mzucv = vfpdky - blgrn; // -42
  /* BUG#1: ssmxiz = 46 - 3*10 + 5*4 = 36,
            change to ssmxiz = 46 - 3*10 + 4*4 = 32 */
  int ssmxiz = blgrn - 3*mnuwcf + 4*vfpdky; //  32
  int aefu = 2*blgrn + 2*vfpdky; //  100
  int b_oi = ssmxiz - (blgrn / vfpdky) + mzucv + 20; // -1
  /* BUG#2: popcg = (100 / 4) / 10 = 25 / 10 = 2,
            change to popcg = 100 / 32 = 3 */
  int popcg = aefu / ssmxiz; //  3
  int hyhbp = (mzucv / popcg) / 7; // -2
  int neug = b_oi + hyhbp; // -3
  /* BUG#3: g_wyb = (100 / 32) - 3 = 3 - 3 = 0,
            change to g_wyb = (100 / 32) - 4 = 3 - 4 = -1 */
  int g_wyb = (aefu / ssmxiz) - vfpdky; // -1
  int zlvvaw = aefu + 2*mzucv; // 16
  /* BUG#4: vumsyq =  -1 -2 -1 -3 = -7,
            change to vumsyq = -2 -2 -1 -3 = -8 */
  int vumsyq = hyhbp + hyhbp + g_wyb + neug; // -8
  /* BUG#5: vtntid = (int)10 / (int)100 = 0,
            change to vtntid = (float)10 / (int)100 = 0.1 */
  float vtntid = (float)mnuwcf / aefu; // 0.1

  //********************************************************************************
  // The remainder of this function has NO bugs
  // DON'T EDIT ANYTHING IN THIS FUNCTION AFTER THIS LINE

  // 100 / -1 / 4 / 5 / -1 = 5
  std::cout << "Multidivide: " << nxzx(aefu, b_oi, vfpdky, 5, b_oi)
	    << " (expected 5)." << std::endl;

  assert(nxzx(aefu,b_oi,vfpdky,5,b_oi) == 5);

  // 840 / -42 / -2 / -1 / 1  = -10
  std::cout << "Multidivide: " << nxzx(840, mzucv, hyhbp, g_wyb, 1)
	    << " (expected -10)." << std::endl;

  assert(nxzx(840, mzucv, hyhbp, g_wyb, 1) == -10);

  // 320 / -8 / -1 / 10 / -2 = -2
  std::cout << "Multidivide: " << nxzx(320, vumsyq, g_wyb, mnuwcf, hyhbp)
	    << " (expected -2)." << std::endl;

  assert(nxzx(320, vumsyq, g_wyb, mnuwcf, hyhbp) == -2);

  // -3200 / -1 / 16 / -8 / 5 = -5
  std::cout << "Multidivide: " << nxzx((ssmxiz*aefu*-1), g_wyb, zlvvaw, vumsyq, (mnuwcf/2))
	    << " (expected -5)." << std::endl;

  assert(nxzx(ssmxiz*aefu*-1, g_wyb, zlvvaw, vumsyq, (mnuwcf/2)) == -5);

  // 1000 / 10 / 10 / 10 / 10 = 0.1
  float nhboq = nxzx(aefu*10, mnuwcf, mnuwcf, mnuwcf, mnuwcf);
  std::cout << "Multidivide: " << nhboq
	    << " (expected 0.1)." << std:: endl;

  assert(gldg(nhboq, vtntid));

  std::cout << "Finished the arithmetic operations" << std::endl;
  return (hyhbp+vumsyq) ^ zlvvaw ^ ((int) nhboq) ^ (mzucv*ssmxiz*aefu*b_oi*popcg);
  //********************************************************************************
}

