#include<iostream>
#include<stdlib.h>
using namespace std;

class Bullet {
    public:
    string name;
    int number;
    Bullet():name("bullet"), number(0){}
    Bullet(int number){
        this->number = number;
    }
};

class Magazine {
    private:
    int count = 0;
    
    public:
    Bullet* array;
    Magazine() {
        count = 0;
    }

    Bullet* get_array() {return array;}

    void add(Bullet bullet) {
        Bullet* temp = new Bullet[count+1];
        temp[count] = bullet;
        for (int i = 0;i < count;i++) {
            temp[i] = array[i];
        }
        if (count > 0) {delete[] array;}
        array = temp;
        count++;
        return;
    }

    void rmBullet(int number) {
        Bullet* temp = new Bullet[count-1];
        int j = 0;
        for (int i = 0;i < count;i++) {
            if (i != number-1) {
                temp[j] = array[i];
                j++;
            }
        }
        if (count > 0) {delete[] array;}
        array = temp;
        count--;
        return;
    }

    int get_count(void) {
        return count;
    }
};

int main() {
    /* Magazine mag;
    int count = 0;
    while (true) {
        int number;
        cout << "Enter 0 to add bullet to end of array, enter i (i > 0) to remove ith bullet from array, enter -1 to leave: ";
        cin >> number;

        if (number < 0) {
            break;
        }
        if (number == 0) {
            count++;
            Bullet bullet(count);
            mag.add(bullet);
        } else {
            mag.rmBullet(number);
        }
        
        for (int i = 0;i < mag.get_count();i++) {
            cout << mag.array[i].number << " ";
        }
        cout << endl;
    }
    */
    while (true) {
    int number = rand() % 8 - 2;
    cout << number << endl;
    }

    return 0;
}