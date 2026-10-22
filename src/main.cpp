#include "custom_string.h"
#include <iostream>
int main() {
String s1;
s1.print(std::cout);
std::cout << " - s1" << std::endl;

String s2("Hello");
s2.print(std::cout);
std::cout << " - s2" << std::endl;

String s3(s2);
s3.print(std::cout);
std::cout << " - s3(s2)" << std::endl;

String s4(std::move(s3));
s3.print(std::cout);
std::cout << " - s3 move" << std::endl;
s4.print(std::cout);
std::cout <<" - s4"<< std::endl;

s1 = s2;
s1.append(", World!");
s1.print(std::cout);
std::cout <<" - append s1"<< std::endl;

size_t pos = s1.find("World");
std::cout<< "Position: " << pos << std::endl;

s3=String("aa bb ccc");
String res = s3.wrap(4);
res.print(std::cout);
std::cout<< " - result of wrap" << std::endl;

s3=String("a  b b c c");
res = s3.wrap(4);
res.print(std::cout);
std::cout<< " - result of wrap" << std::endl;
return 0;
}