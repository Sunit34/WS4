#include <iostream>

int arr[3] = {10, 20, 30};
int *tableauDynamique = new int[3];

int main(){
    
    std::cout << "Tableau" << std::endl;
    
    std::cout << arr[0] << std::endl;
    std::cout << arr[1] << std::endl;
    std::cout << arr[2] << std::endl;
    
    std::cout << "Tableau dynamique" << std::endl;

    tableauDynamique[0] = 10;
    tableauDynamique[1] = 20;
    tableauDynamique[2] = 30;

    std::cout << tableauDynamique[0] << std::endl;
    std::cout << tableauDynamique[1] << std::endl;
    std::cout << tableauDynamique[2] << std::endl;

    delete[] tableauDynamique;

    return 0;
}