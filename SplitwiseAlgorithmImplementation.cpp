#include <iostream>
#include <set>
using namespace std;
int main()
{
    int no_of_transactions, friends;
    cout<<"Enter the number of transactions : ";
    cin >> no_of_transactions ;
    cout<<"Enter the number of friends : ";
    cin>>friends;

    int x, y, amount;

    // make a 1-D array to store the net amount that each person will have to take at the end.
    int net[100000] = {0};
    cout<<"Enter the details of transactions : "<<endl;
    while (no_of_transactions--)
    {
        cin >> x >> y >> amount;
        net[x] -= amount;
        net[y] += amount;
    }

    // initialise a list & sort it => multiset
    multiset<int> m;
    for (int i = 0; i < friends; i++)
    {
        if (net[i] != 0)
        {
            m.insert(net[i]);
        }
    }

    // pop out two persons (left & right) and try to settle them

    int no_of_steps = 0; //no. of steps required to settle the amount

    while (!m.empty())
    {
        auto low = m.begin();
        auto high = prev(m.end());

        int debit = *low;
        int credit = *high;

        // Erase

        m.erase(low);
        m.erase(high);

        // settlement

        int settlement_amount = min(-debit, credit);
        no_of_steps++;

        // settlement_amount from debiter to crediter

        debit += settlement_amount;
        credit -= settlement_amount;

        if(debit!=0){
            m.insert(debit);
        }
        if(credit!=0){
            m.insert(credit);
        }


    }

    cout<<"Number of steps to settle the amount : " <<no_of_steps<<endl;

    return 0;
}
