#include "solution.h"

int main() {
    std::cout << "======== Constructor Test ========\n";
    SpeedCircularLinkedList<int, 97> constructors({10,20,30,40,50,60,70,80,90,97});
    constructors.print();
    std::cout << "============ Size Test ============\n";
    SpeedCircularLinkedList<int, 53> sizes({10,30,40,50,53});
    std::cout << "size = " << sizes.size() << '\n';
    std::cout << "============ Put Test ============\n";
    SpeedCircularLinkedList<int, 197> puts({10,30,50,70,90,110,130,150,170,197});
    puts.put("19260817", 0);
    puts.put("What a pity!", 1);
    puts.put("ACM2025", 6);
    puts.print();
    std::cout << "=========== Get Test =============\n";
    SpeedCircularLinkedList<std::string, 2017> gets({50,250,450,800,1000,1300,1350,1600,1850,2017});
    gets.put("Butterworth", "07:50");
    gets.put("Ipoh", "09:37");
    gets.put("KL Sentral", "12:15");
    gets.put("Seremban", "13:38");
    gets.put("Gemas", "14:42");
    gets.put("Segamat", "14:57");
    std::cout << gets.get("KL Sentral") << '\n'
              << gets.get("Gemas") << '\n'
              << gets.get("Butterworth") << '\n';
}
