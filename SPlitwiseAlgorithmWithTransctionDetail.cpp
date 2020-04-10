#include <iostream>
#include <set>
#include <map>
using namespace std;
// Money Splitwise Algorithm

/* 
Output - Should also show transaction
    For ex : 
    Rahul pays 50 to Avinash
    Rahul pays 10 to Abhishek
    2
*/

class person_compare
{
public:
    bool operator()(pair<string, int> p1, pair<string, int> p2)
    {
        return p1.second < p2.second;
    }
};

int main()
{
    int no_of_transactions, friends;
    cout<<"Enter the number of transactions : ";
    cin >> no_of_transactions ;
    cout<<"Enter the number of friends : ";
    cin>>friends;

    map<string, int> net;
    string x, y;
    int amount;
    cout<<"Enter the details of transactions : "<<endl;
    while (no_of_transactions--)
    {
        cin >> x >> y >> amount;
        if (net.count(x) == 0)
        {
            net[x] = 0;
        }
        if (net.count(y) == 0)
        {
            net[y] = 0;
        }
        net[x] -= amount;
        net[y] += amount;
    }

    // Iterate over the persons and add those persons in the multiset who have non zero net

    multiset<pair<string, int>, person_compare> m;

    for (auto p : net)
    {
        string person = p.first;
        int amount = p.second;

        if (net[person] != 0)
        {
            m.insert(make_pair(person, amount));
        }
    }

    // Settlements (start & end)
    int no_of_steps = 0;
    while (!m.empty())
    {
        auto low = m.begin();
        auto high = prev(m.end());

        int debit = low->second;
        string debit_person = low->first;

        int credit = high->second;
        string credit_person = high->first;

        // pop them out
        m.erase(low);
        m.erase(high);

        int settled_amount = min(-debit, credit);
        debit += settled_amount;
        credit -= settled_amount;

        //Print the transaction between people

        cout << debit_person << " will pay " << settled_amount << " to " << credit_person << endl;

        if (debit != 0)
        {
            m.insert(make_pair(debit_person, debit));
        }
        if (credit != 0)
        {
            m.insert(make_pair(credit_person, credit));
        }
        no_of_steps++;
    }
    cout << "No of steps to settle the amount : " << no_of_steps << endl;
    return 0;
}
