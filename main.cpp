// Eng: Saif Hazim
// id: 20210165
// Eng: Karim
// id: 20210298
// Eng: Mostafa Bahy
// id: 20210401
// project: An implementation for BigReal class using the code of BigDecimalInt class
// objectives: Using the code of other programmers in our implementation


#include "BigReal.h"


int main() {
    BigReal n1 ("11.9000000000000000000000000000000001");
    BigReal n2 ("2333333333339.1134322222222292");
    BigReal n3 = n1 + n2;
    cout << n3;
    n3 = n3 + BigReal (0.9);
cout<<n3;

}
